#include "stack.h"

void stack_init(Stack *s) {
  if (s == NULL)
    return;
  s->t = 0;
}

bool stack_empty(const Stack *s) {
  if (s == NULL)
    return true;
  return s->t == 0;
}
bool stack_append(Stack *s, int a) {
  if (s == NULL || s->t >= SIZE) {
    return false;
  }
  s->data[s->t] = a;
  s->t++;
  return true;
}

bool stack_delete(Stack *s, int *out) {
  if (s == NULL || stack_empty(s)) {
    return false;
  }
  s->t--;
  if (out != NULL) {
    *out = s->data[s->t];
  }
  return true;
}
