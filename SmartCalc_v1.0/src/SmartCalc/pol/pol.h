#ifndef POL_POL_H
#define POL_POL_H

#include "../stack/stack.h"

#define LAST_SIM_IS_NUM_BUF *buf >= '0' && *buf <= '9'
#define UNARY_OP (stack->op == U_SUB || stack->op == U_SUM || stack->op == COS \
               || stack->op == SIN || stack->op == TAN || stack->op == ACOS \
               || stack->op == ASIN || stack->op == ATAN || stack->op == SQRT \
               || stack->op == LN || stack->op == LOG)
#define BINARY_OP (stack->op == SUM || stack->op == SUB || stack->op == MULT \
                || stack->op == DEL || stack->op == EXP || stack->op == MOD)

double pol_hendler(const char *buf, double X, int *error_target);
double Calculate(s21_Stack *stack, double X, int *error_target);
void Buf_to_stack(const char *buf, s21_Stack *stack);
int SkipNum(const char *buf);
int GetOp(const char* buf, enum OP *op);
enum OP CheckOneSim(const char* buf);
enum OP CheckFourSim(const char* buf);
enum OP CheckThreeSim(const char* buf);
int What_prior(enum OP op);
double Unary(double a, enum OP op, int *error_target);
double Binary(double a, double b, enum OP op, int *error_target);

double annuity(double percent, double total_amount, double period);
double annuity_total_amount(double credit_result, double period);

#endif // POL_POL_H
