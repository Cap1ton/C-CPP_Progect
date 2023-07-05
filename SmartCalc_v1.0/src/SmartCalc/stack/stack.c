#include "stack.h"

s21_Stack *create_stack(s21_Stack *res) {
    res = (s21_Stack*)malloc(sizeof(s21_Stack));
    if (res != NULL) {
        res->back = NULL;
        res->begin = res;
        res->next = NULL;
        res->value = 0;
        res->op = END;
    }
    return res;
}

void destroy_stack(s21_Stack *stack) {
    while (stack->op != END) {
        s21_Stack *p = stack;
        stack = stack->back;
        free(p);
    }
    free(stack);
}

s21_Stack* push_stack(double value, enum OP op, s21_Stack *last) {
    s21_Stack *res = (s21_Stack*)malloc(sizeof(s21_Stack));
    if (res != NULL) {
        res->back = last;
        res->next = NULL;
        last->next = res;
        res->begin = last->begin;
        res->value = value;
        res->op = op;
    }
    return res;
}

s21_Stack* pop_stack(s21_Stack *stack) {
    if (stack->op != END) {
        s21_Stack *p = stack;
        stack = stack->back;
        stack->next = NULL;
        free(p);
    }
    return stack;
}
