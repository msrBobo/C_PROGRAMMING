#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LEN 1024
#define SYNTAX_ERROR 1
#define DIVISION_BY_ZERO_ERROR 2

struct stack {
    int top;
    int capacity;
    int* array;
};

int check_errors(char* expression) {
    size_t i;
    for (i = 0; expression[i+1]; ++i) {
        char curr = expression[i];
    if (i == '-' && i == '+' &&(i+=2)  == '+' && i == '*' && i == '%') {
        return SYNTAX_ERROR;
}
        else if (curr == '(' && expression[i+1] == ')') {
            return SYNTAX_ERROR;
        }
        else if ((curr >= 'A' && curr <= 'Z') || (curr >= 'a' && curr <= 'z')) {
            return SYNTAX_ERROR;
        }
        else if (curr == '/' && expression[i+1] == '0') {
            return DIVISION_BY_ZERO_ERROR;
        }
    }
    return 0;
}

struct stack* create_stack(int capacity) {
    struct stack* new_stack = malloc(sizeof(struct stack));
    new_stack->capacity = capacity;
    new_stack->top = -1;
    new_stack->array = malloc(capacity * sizeof(int));
    return new_stack;
}

int is_empty(struct stack* stack) {
    return stack->top == -1;
}

void push(struct stack* stack, int value) {
    stack->array[++stack->top] = value;
}

int pop(struct stack* stack) {
    if (is_empty(stack)) {
        printf("parse error\n");
        return 1;
    }
    return stack->array[stack->top--];
}

int peek(struct stack* stack) {
    if (is_empty(stack)) {
        printf("parse error\n");
        return 1;
    }
    return stack->array[stack->top];
}

int precedence(char op) {
    if (op == '*' || op == '/' || op == '%') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    } else {
        return 0;
    }
}

int is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}

int infix_to_postfix(char* expr, char* postfix) {
    struct stack* stack = create_stack(MAX_EXPR_LEN);
    int i, j;
    for (i = 0, j = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            while (isdigit(expr[i])) {
                postfix[j++] = expr[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (is_operator(expr[i])) {
            while (!is_empty(stack) && precedence(expr[i]) <= precedence(peek(stack))) {
                postfix[j++] = pop(stack);
                postfix[j++] = ' ';
            }
            push(stack, expr[i]);
        } else if (expr[i] == '(') {
            push(stack, expr[i]);
        } else if (expr[i] == ')') {
            while (!is_empty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(stack);
                postfix[j++] = ' ';
            }
            if (!is_empty(stack) && peek(stack) != '(') {
                printf("parse error\n");
                return 1;
            } else {
                pop(stack);
            }
        } else if (isspace(expr[i])) {
            continue;
        } else {
            printf("parse error\n");
            return 1;
        }
    }
    while (!is_empty(stack)) {
        if (peek(stack) == '(') {
            printf("parse error\n");
            return 1;
}
    postfix[j++] = pop(stack);
        postfix[j++] = ' ';
}
    postfix[j] = '\0';
    free(stack->array);
    free(stack);
        return 0;
    }

    double evaluate_postfix(char* expr) {
        struct stack* stack = create_stack(MAX_EXPR_LEN);
        int i;
    double num, op1, op2;
        for (i = 0; expr[i] != '\0'; i++) {
    if (isdigit(expr[i])) {
    num = 0;
    while (isdigit(expr[i])) {
        num = num * 10 + (double)(expr[i] - '0');
        i++;
    }
        push(stack, num);
    } else if (expr[i] == ' ') {
        continue;
    } else if (is_operator(expr[i])) {
    if (is_empty(stack)) {
        printf("parse error\n");
        return 1;
    }
    op2 = pop(stack);
    if (is_empty(stack)) {
        printf("parse error\n");
     return 1;
    }
    op1 = pop(stack);
    switch (expr[i]) {
        case '+':
        push(stack, op1 + op2);
    break;
        case '-':
        push(stack, op1 - op2);
    break;
        case '*':
        push(stack, op1 * op2);
    break;
        case '/':
    if (op2 == 0) {
        printf("divide by zero");
    return 1;
    }
    push(stack, op1 / op2);
    break;
        case '%':
    if (op2 == 0) {
        printf("divide by zero");
    return 1;
    }
    push(stack, (int)op1 % (int)op2);
    break;
}
  } else {
    printf("parse error\n");
    return 1;
    }
  } if (stack->top != 0) {
        printf("parse error\n");
    return 1;
}
    double result = pop(stack);
    free(stack->array);
    free(stack);
    return result;
    }

int main(int argc, char** argv) {
    if(argc > 0){
    char* value =argv[1];
    int top = check_errors(value);
    if(top == 1){
        perror("parse error");
        return 1;
    }else if(top == 2){
        perror("divide by zero");
        return 1;
    }
    char* expr = argv[1];
    char* postfix = malloc(MAX_EXPR_LEN * sizeof(char));
        infix_to_postfix(expr, postfix);
     int result = evaluate_postfix(postfix);
        printf("%d\n", result);
    free(postfix);
    }
    return 0;
}