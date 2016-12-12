#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC_FAILED -1
#define EMPTY_STACK -2
#define OPR_ERROR -3
#define DIVIDE_BY_ZERO -4
#define SUCCEEDED 0

#define CHAR_MAX_LEN 200

typedef struct node {
    double data;
    struct node *next;
} myNode, *pNode;

typedef struct stack {
    myNode *top;
    myNode *bottom;
    int size;
} myStack, *pStack;

int initStack(pStack s);
void clearStack(pStack s);
int push(pStack s, double data);
int pop(pStack s, double *data);  // data points to s->top->data

int elemCount(pStack s);
int isNumber(char c);
void midfixToSuffix(char midfix[], char suffix[]);
int suffixToResult(char suffix[], char s[]);

pStack stkNum, stkOpr; // stacks for numbers and operators
char midfix[CHAR_MAX_LEN], suffix[CHAR_MAX_LEN];

int initStack(pStack s) {
    s->top = (pNode)malloc(sizeof(myNode));
    if (NULL == s->top) return MALLOC_FAILED;
    s->top->next = NULL;
    s->bottom = s->top;
    s->size = 0;
    return SUCCEEDED;
}

int push(pStack s, double data) {
    pNode pNew = (pNode)malloc(sizeof(myNode));
    if (NULL == pNew) return MALLOC_FAILED;
    pNew->data = data;
    pNew->next = s->top;
    s->top = pNew;
    ++s->size;
    return SUCCEEDED;
}

int pop(pStack s, double *data) {
    pNode pTop;
    if (!elemCount(s)) return EMPTY_STACK;
    pTop = s->top;
    if (NULL != data) *data = pTop->data;
    s->top = pTop->next;
    free(pTop);
    --s->size;
    return SUCCEEDED;
}

void clearStack(pStack s) {
    int m = 0;
    if (!elemCount(s)) return;
    while (!m) {
        m = pop(s, NULL);
    }
    s->size = 0;
}

int elemCount(pStack s) {
    return s->size;
}

int isNumber(char c) {
    return ((c >= '0' && c <= '9') || c == '.');
}

void midfixToSuffix(char midfix[], char suffix[]) {
    int i, j = 0, isNum, isNeg, isPos = isNeg = isNum = 0; // +3 and -4 are both legal, check it!
    char c;
    double pc;
    for (i = 0; i < strlen(midfix); ++i) {
        c = midfix[i];
        if (isNumber(c)) {
            isNum = 1;
            suffix[j++] = c;
            // 3+3 => plus
            // 3++3 || +3 || (+3) => plus positive, negative is alike
            // 3+++3 || 3+ || ++3 is illegal
            // but, )+3 still means plus
        } else if (((c == '-' || c == '+') &&
                    (i > 0 && i < strlen(midfix) - 1 &&
                     (!isNumber(midfix[i - 1]) && midfix[i - 1] != ')') &&
                        isNumber(midfix[i + 1]))) ||
                        (!i && strlen(midfix) > 1 && isNumber(midfix[1]))) {
            if (c == '-') isNeg = 1; else isPos = 1;
            isNum = 1;
            suffix[j++] = c;
        } else {
            if (isNum) suffix[j++] = ' ';
            isNum = 0; isNeg = 0; isPos = 0;
        }
        // while (the priority of stkOpr->top->data >= c) pop, then push c
        // the priority of '(' is -inf
        // when c == ')', keep popping until meet a '('
        if (c == '+') {
            if (isPos) continue;
            while (stkOpr->size && (char)stkOpr->top->data != '(') {
                suffix[j++] = ' ';
                pop(stkOpr, &pc);
                suffix[j++] = (char)pc;
                suffix[j++] = ' ';
            }
            push(stkOpr, (double)c);
        } else if (c == '-') {
            if (isNeg) continue; // a negative number
            while (stkOpr->size && (char)stkOpr->top->data != '(') {
                suffix[j++] = ' ';
                pop(stkOpr, &pc);
                suffix[j++] = (char)pc;
                suffix[j++] = ' ';
            }
            push(stkOpr, (double)c);
        } else if (c == '*' || c == '/') {
            while (stkOpr->size &&
                   ((char)stkOpr->top->data == '*' || (char)stkOpr->top->data == '/')) {
                suffix[j++] = ' ';
                pop(stkOpr, &pc);
                suffix[j++] = (char)pc;
                suffix[j++] = ' ';
            }
            push(stkOpr, (double)c);
        } else if (c == '(') {
            push(stkOpr, (double)c);
        } else if (c == ')') {
            while (stkOpr->size && (char)stkOpr->top->data != '(') {
                suffix[j++] = ' ';
                pop(stkOpr, &pc);
                suffix[j++] = (char)pc;
                suffix[j++] = ' ';
            }
            pop(stkOpr, NULL); // pop the '('
        } else { // not (0~9 or +-*/.()), ignore
            continue;
        }
    }
    // pop everything in stkOpr, this time one space is enough
    while (stkOpr->size) {
        suffix[j++] = ' ';
        pop(stkOpr, &pc);
        suffix[j++] = (char)pc;
    }
    suffix[j++] = ' ';
}

int suffixToResult(char suffix[], char s[]) {
    int i, j = 0;
    char c;
    double m, n;
    int isNum = 0, isNeg = 0, isPos = 0;
    for(i = 0; i < strlen(suffix); ++i){
        // push the numbers to stkNum
        c = suffix[i];
        if (isNumber(c)) {
            s[j++] = c;
            isNum = 1;
            continue;
        } else if ((c == '-' || c == '+') &&
                   i < strlen(suffix) - 1 && isNumber(suffix[i + 1])) {
            if (c == '-') isNeg = 1; else isPos = 1;
            isNum = 1;
            s[j++] = c;
        } else {
            if(isNum) push(stkNum, atof(s));
            isNum = 0; isNeg = 0; isPos = 0;
            memset(s, 0, sizeof(*s) * CHAR_MAX_LEN); j = 0;
        }
        // if there is an operator, pop two numbers, then operate them and push the result
        // (if there are no enough numbers in stack, return error)
        // notice that when operating, n comes first and then m
        switch (c) {
            case '+':
                if (isPos) continue;
                if (!stkNum->size) return OPR_ERROR;
                pop(stkNum, &m);
                if (!stkNum->size) return OPR_ERROR;
                pop(stkNum, &n);
                push(stkNum, n + m);
                break;
            case '-':
                if (isNeg) continue;
                if (!stkNum->size) return OPR_ERROR;
                pop(stkNum, &m);
                if (!stkNum->size) return OPR_ERROR;
                pop(stkNum, &n);
                push(stkNum, n - m);
                break;
            case '*':
                if (!stkNum->size) return OPR_ERROR;
                pop(stkNum, &m);
                if (!stkNum->size) return OPR_ERROR;
                pop(stkNum, &n);
                push(stkNum, n * m);
                break;
            case '/':
                if (!stkNum->size) return OPR_ERROR;
                pop(stkNum, &m);
                if (!m) return DIVIDE_BY_ZERO;
                if (!stkNum->size) return OPR_ERROR;
                pop(stkNum, &n);
                push(stkNum, n / m);
                break;
            default:break;
        }
    }
    return SUCCEEDED;
}

int main() {
    char s[CHAR_MAX_LEN], g;
    int result, j = 0;
    stkOpr = malloc(sizeof(myStack));
    stkNum = malloc(sizeof(myStack));
    initStack(stkOpr); initStack(stkNum);
    g = getchar();
    while (g != '\n') {
        if (g != ' ') midfix[j++] = g;
        g = getchar();
    } // delete all the space
    midfixToSuffix(midfix, suffix);
    result = suffixToResult(suffix, s);
    
    switch (result) {
        case DIVIDE_BY_ZERO:
            printf("ERROR: Divided by zero.\nError Example: 5/(4.00-4)\n");
            break;
        case EMPTY_STACK:
            printf("ERROR: Attempt to pop when the stack is empty. This error occurs because there are bugs in the program. Please call the programmer and tell him your input.\n");
            break;
        case MALLOC_FAILED:
            printf("ERROR: Malloc failed. This error occurs because there are bugs in the program. Please call the programmer and tell him your input.\n");
            break;
        case OPR_ERROR:
            printf("ERROR: Operator error. Please recheck your input.\nError Example: 5**3\n");
            break;
        case SUCCEEDED:
            printf("%f\n", stkNum->top->data);
            break;
        default:
            printf("ERROR: Unknown error. This error occurs because there are bugs in the program. Please call the programmer and tell him your input.");
            break;
    }
    return 0;
}
