#include "buddy_allocator.h"
#include <string.h>

#define LEVELLING_8(x) (((x) + 7) & ~7)

static size_t block_size(BuddyCtx *ctx, int order) {
  return ctx->min_block * (1 << order);
}
void b_init(BuddyCtx *ctx, void *buffer, size_t size, size_t min_block_size) {
  if (!ctx || !buffer || size == 0) {
    return;
  }
  size_t min = LEVELLING_8(min_block_size);
  if (min < sizeof(Block)) {
    min = LEVELLING_8(sizeof(Block));
  }
  ctx->buffer = (char *)buffer;
  ctx->min_block = min;
  ctx->max_order = 0;
  size_t temp = size / min;
  while (temp > 1) {
    ctx->max_order++;
    temp /= 2;
  }
  for (int i = 0; i <= ctx->max_order; i++) {
    ctx->free_block[i] = NULL;
  }
  Block *initial = (Block *)ctx->buffer;
  initial->order = ctx->max_order;
  initial->is_free = 1;
  initial->next_free = NULL;
  ctx->free_block[ctx->max_order] = initial;
}
void *b_alloc(BuddyCtx *ctx, size_t bytes) {
  if (!ctx || bytes == 0) {
    return NULL;
  }
  size_t total = LEVELLING_8(bytes + sizeof(Block));
  int need_order = 0;
  while (get_size(ctx, need_order) < total && need_order < ctx->max_order) {
    need_order++;
  }
  int order = need_order;
  while (order <= ctx->max_order && ctx->free_block[order] == NULL) {
    order++;
  }
  if (order > ctx->max_order) {
    return NULL;
  }
  Block *block = ctx->free_block[order];
  ctx->free_block[order] = block->next_free;
  while (order > need_order) {
    order--;
    size_t half = get_block_size(ctx, order);
    Block *buddy = (Block *)((char *)block + half);
    buddy->order = order;
    buddy->is_free = 1;
    buddy->next_free = ctx->free_block[order];
    ctx->free_block[order] = buddy;
    block->order = order;
  }
  block->is_free = 0;
  return (void *)((char *)block + sizeof(Block));
}
void b_free(BuddyCtx *ctx, void *address) {
  if (!ctx || !address) {
    return;
  }
  Block *block = (Block *)((char *)address - sizeof(Block));
  if (block->is_free) {
    return;
  }
  block->is_free = 1;
  int order = block->order;
  block->next_free = ctx->free_block[order];
  ctx->free_block[order] = block;
}
void *b_realloc(BuddyCtx *ctx, void *address, size_t new_size) {
  if (!address)
    return buddy_alloc(ctx, new_size);
  if (new_size == 0) {
    free(ctx, address);
    return NULL;
  }
  void *new_ptr = b_alloc(ctx, new_size);
  if (!new_ptr) {
    return NULL;
  }
  memcpy(new_ptr, address, new_size);
  b_free(ctx, address);
  return new_ptr;
}
