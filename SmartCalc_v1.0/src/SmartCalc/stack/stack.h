#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum OP {
    // бинарные
    SUM,
    SUB,
    MULT,
    DEL,
    EXP,
    MOD,
    // унарные
    U_SUB,
    U_SUM,
    COS,
    SIN,
    TAN,
    ACOS,
    ASIN,
    ATAN,
    SQRT,
    LN,
    LOG,
    // другие операторы
    OPEN_B,
    CLOSE_B,
    X_NUM,
    // конец стека
    END,
    // пустой
    AGA
};

typedef struct s21_Stack {
    struct s21_Stack *back;
    struct s21_Stack *next;
    struct s21_Stack *begin;
    double value;
    enum OP op;
} s21_Stack;

s21_Stack *create_stack(s21_Stack *res);
void destroy_stack(s21_Stack *stack);
s21_Stack* push_stack(double value, enum OP op, s21_Stack *last);
s21_Stack* pop_stack(s21_Stack *stack);

#endif // STACK_STACK_H
