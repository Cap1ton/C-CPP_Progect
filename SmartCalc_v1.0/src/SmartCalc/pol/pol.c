#include "pol.h"
#include "../stack/stack.c"

double Unary(double a, enum OP op, int *error_target) {
    double res;
    if (op == SIN) {
        res = sinl(a);
    } else if (op == COS) {
        res = cosl(a);
    } else if (op == TAN) {
        res = tanl(a);
    } else if (op == ASIN) {
        res = asinl(a);
    } else if (op == ACOS) {
        res = acosl(a);
    } else if (op == ATAN) {
        res = atanl(a);
    } else if (op == LN) {
        res = logl(a);
    } else if (op == LOG) {
        res = log10l(a);
    } else if (op == SQRT) {
        if (a < 0) {
            *error_target = 1;
        } else {
            res = sqrtl(a);
        }
    } else if (op == U_SUM) {
        res = fabs(a);
    } else if (op == U_SUB) {
        if (a < 0) {
            res = a;
        } else {
            res = a * -1;
        }
    }
    if (isinf(res) || -isinf(res)) {
        *error_target = 3;
    }
    if (isnan(res)) {
        *error_target = 4;
    }
    return res;
}

double Binary(double b, double a, enum OP op, int *error_target) {
    double res;
    if (op == SUM) {
        res = a + b;
    } else if (op == SUB) {
        res = a - b;
    } else if (op == MULT) {
        res = a * b;
    } else if (op == DEL) {
        if (b == 0) {
            *error_target = 2;
        } else {
            res = a / b;
        }
    } else if (op == EXP) {
        res = pow(a, b);
    } else if (op == MOD) {
        res = fmodl(a, b);
    }
    if (isinf(res)) {
        *error_target = 3;
    }
    if (isnan(res)) {
        *error_target = 4;
    }
    return res;
}

double Calculate(s21_Stack *stack, double X, int *error_target) {
    double res;
    s21_Stack *buf_stack = NULL;
    buf_stack = create_stack(buf_stack);
    while (stack != NULL && !*error_target) {
        double a = 0, b = 0;
        if (stack->op == AGA) {
            buf_stack = push_stack(stack->value, AGA, buf_stack);
        } else {
            if (UNARY_OP) {
                a = buf_stack->value;
                buf_stack = pop_stack(buf_stack);
                buf_stack = push_stack(Unary(a, stack->op, error_target), AGA, buf_stack);
            } else if (BINARY_OP) {
                a = buf_stack->value;
                buf_stack = pop_stack(buf_stack);
                b = buf_stack->value;
                buf_stack = pop_stack(buf_stack);
                buf_stack = push_stack(Binary(a, b, stack->op, error_target), AGA, buf_stack);
            } else {
                buf_stack = push_stack(X, AGA, buf_stack);
            }
        }
        stack = stack->next;
    }
    res = buf_stack->value;
    destroy_stack(buf_stack);
    return res;
}

enum OP CheckOneSim(const char* buf) {
    enum OP res = AGA;
    if (*buf == '+') {
        if (*(buf - 1) == ' ' || *(buf - 1) == '(') {
            res = U_SUM;
        } else {
            res = SUM;
        }
    } else if (*buf == '-') {
        if (*(buf - 1) == ' ' || *(buf - 1) == '(') {
            res = U_SUB;
        } else {
            res = SUB;
        }
    } else if (*buf == '/') {
        res = DEL;
    } else if (*buf == '*') {
        res = MULT;
    } else if (*buf == '^') {
        res = EXP;
    } else if (*buf =='(') {
        res = OPEN_B;
    } else if (*buf == ')') {
        res = CLOSE_B;
    }
    return res;
}

enum OP CheckFourSim(const char* buf) {
    enum OP res = AGA;
    if (!strncmp(buf, "asin", 4)) {
        res = ASIN;
    } else if (!strncmp(buf, "acos", 4)) {
        res = ACOS;
    } else if (!strncmp(buf, "atan", 4)) {
        res = ATAN;
    } else if (!strncmp(buf, "sqrt", 4)) {
        res = SQRT;
    }
    return res;
}

enum OP CheckThreeSim(const char* buf) {
    enum OP res = AGA;
    if (!strncmp(buf, "sin", 3)) {
        res = SIN;
    } else if (!strncmp(buf, "cos", 3)) {
        res = COS;
    } else if (!strncmp(buf, "tan", 3)) {
        res = TAN;
    } else if (!strncmp(buf, "log", 3)) {
        res = LOG;
    } else if (!strncmp(buf, "mod", 3)) {
        res = MOD;
    }
    return res;
}

int GetOp(const char* buf, enum OP *op) {
    int i = 0;
    if ((*op = CheckOneSim(buf)) != AGA) {
        i = 1;
    } else if ((*op = CheckThreeSim(buf)) != AGA) {
        i = 3;
    } else if ((*op = CheckFourSim(buf)) != AGA) {
        i = 4;
    } else if (!strncmp(buf, "ln", 2)) {
        *op = LN;
        i = 2;
    } else {
        i = 1;
    }
    return i;
}

int SkipNum(const char* buf) {
    int i = 0;
    for (; (LAST_SIM_IS_NUM_BUF) || *buf == '.'; buf++) {
        i++;
    }
    return i;
}


int What_prior(enum OP op) {
    int prior = 0;
    if (op == SUM || op == SUB) {
        prior = 1;
    } else if (op == MULT || op == DEL || op == MOD) {
        prior = 2;
    } else if (op == EXP) {
        prior = 3;
    } else if (op == COS || op == SIN || op == TAN ||
               op == ACOS || op == ASIN || op == ATAN ||
               op == LN || op == LOG || op == SQRT) {
        prior = 4;
    } else if (op == U_SUB || op == U_SUM)
        prior = 5;
    return prior;
}

void Buf_to_stack(const char* buf, s21_Stack *stack) {
    s21_Stack *shake_stack = NULL;
    double value;
    shake_stack = create_stack(shake_stack);
    while (*buf != '\0') {
        enum OP op;
        if (LAST_SIM_IS_NUM_BUF) {
            value = atof(buf);
            buf += SkipNum(buf);
            stack = push_stack(value, AGA, stack);
        } else if (*buf != 'x') {
            buf += GetOp(buf, &op);
            int prior_op = What_prior(op);
            for (int target_end_cycle = 0; target_end_cycle != 1;) {
                int prior_op_stack = What_prior(shake_stack->op);
                if (prior_op_stack < prior_op || op == OPEN_B || shake_stack->op == END) {
                    shake_stack = push_stack(0,op,shake_stack);
                    target_end_cycle = 1;
                } else if (prior_op_stack == 3 && prior_op == 3) {
                    shake_stack = push_stack(0,op,shake_stack);
                    target_end_cycle = 1;
                } else if (op == CLOSE_B) {
                    if (shake_stack->op == OPEN_B) {
                        shake_stack = pop_stack(shake_stack);
                        target_end_cycle = 1;
                    } else {
                        stack = push_stack(0, shake_stack->op, stack);
                        shake_stack = pop_stack(shake_stack);
                    }
                } else {
                    stack = push_stack(0, shake_stack->op, stack);
                    shake_stack = pop_stack(shake_stack);
                }
            }
        } else {
            stack = push_stack(0, X_NUM, stack);
            buf++;
        }
    }
    while (shake_stack->op != END) {
        stack = push_stack(0, shake_stack->op, stack);
        shake_stack = pop_stack(shake_stack);
    }
    destroy_stack(shake_stack);
    stack = stack->begin;
}

double pol_hendler(const char* buf, double X, int *error_target) {
    double res;
    s21_Stack *pol_stack = NULL;
    pol_stack = create_stack(pol_stack);
    Buf_to_stack(buf+1, pol_stack);
    res = Calculate(pol_stack++, X, error_target);
    return res;
}
