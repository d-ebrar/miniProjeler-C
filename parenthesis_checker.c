#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

struct Stack {
    char items[MAX_SIZE];
    int top;
};

void init_stack(struct Stack *s);
bool is_full(struct Stack *s);
bool is_empty(struct Stack *s);
void push(struct Stack *s, char c);
char pop(struct Stack *s);
int is_balanced(char *expression);
void clean_newLine(char *s);
void clear_input_buffer();

int main() {
    char expr[100];
    
    printf("Enter an expression to check: ");
    fgets(expr, sizeof(expr), stdin);
    clean_newLine(expr);

    if (is_balanced(expr)) {
        printf("Valid Expression (Balanced).\n");
    } else {
        printf("Invalid Expression (Not Balanced).\n");
    }

    return 0;
}

int is_balanced(char *expression) {
    struct Stack stack;
    init_stack(&stack);
    int i;

    for (i = 0; i < strlen(expression); i++) {
        char value = *(expression + i);
        switch (value){
            case '(':
            case '{':
            case '[':
                push(&stack, value);
                break;

            case ')':
                if (is_empty(&stack)) 
                return 0;

                value = pop(&stack);
                if (value != '(' ) {
                    return 0;
                }
                break;

            case '}':
                if (is_empty(&stack)) 
                return 0;

                value = pop(&stack);
                if (value != '{' ) {
                    return 0;
                }
                break;

            case ']':
                if (is_empty(&stack)) 
                return 0;

                value = pop(&stack);
                if (value != '[' ) {
                    return 0;
                }
                break;    
        }
    }

    if (is_empty(&stack)) {
        return 1; 
    }
    else {
        return 0;
    }
}

void init_stack(struct Stack *s) {
    s->top = -1;
}

bool is_full(struct Stack *s) {
    return s->top == MAX_SIZE - 1;
}

bool is_empty(struct Stack *s) {
    return s->top == -1;
}

void push(struct Stack *s, char c) {
    if (is_full(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->top++;
    s->items[s->top] = c;
}

char pop(struct Stack *s) {
    char popped;

    if (is_empty(s)) {
        return '\0';
    }
    popped = s->items[s->top];
    s->top--;
    return popped;
}

void clean_newLine(char *s) {
    char *c = strchr(s, '\n');

    if (c != NULL) {
        *c = '\0';
    }
    else {
        clear_input_buffer();
    }
}

void clear_input_buffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {}
}