#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    double data;
    struct Node *next;
} Node;

Node *top = NULL;

void push(double value);
double pop();
int is_empty();
void print_stack();
void free_stack();
int is_number(const char *str);

int main() {
    char input[50];
    double val1, val2, result;

    printf("RPN Calculator (Type 'e' to exit)\n");
    printf("Examples: '5', '10', '+', '-', '*', '/'\n");

    while (1) {
        printf("> ");

        if (scanf("%49s", input) != 1) break;

        if (strcmp(input, "e") == 0) break;

        if (is_number(input)) {
            double num = atof(input);
            push(num);

            printf("[Stack] Pushed: %.2f\n", num);
        }
        else {
            if (is_empty() || top->next == NULL) {
                printf("Error: Not enough operands!\n");
                continue;
            }

            val2 = pop();
            val1 = pop();

            switch (input[0]) {
                case '+':
                    result = val1 + val2;
                    break;
                case '-':
                    result = val1 - val2;
                    break;
                case '*':
                    result = val1 * val2;
                    break;
                case '/':
                    if (val2 == 0) {
                        printf("Error: Division by zero!\n");
                        free_stack();
                        continue;
                    }

                    result = val1 / val2;
                    break;
                default:
                    printf("Unknown operator: %s\n", input);
                    continue;
            }

            push(result);
            printf("Result: %.2f\n", result);
        }

        print_stack();
    }

    free_stack();
    printf("Calculator closed.\n");
    return 0;
}

void push(double value) {
    Node *temp = (Node *)malloc(sizeof(Node));

    if (temp == NULL) {
        printf("memory allocation failed.\n");
        return;
    }

    temp->data = value;
    temp->next = top;
    top = temp;
}

double pop() {
    if (is_empty()) {
        printf("Stack Underflow!\n");
        return 0.0;
    }
    Node *temp = top;
    double data = temp->data;
    top = top->next;

    free(temp);
    return data;
}

int is_empty() {
    return top == NULL;
}

void print_stack() {
    Node *temp = top;
    printf("Stack: [ ");
    while (temp != NULL) {
        printf("%.2f ", temp->data);
        temp = temp->next;
    }
    printf("]\n");
}

void free_stack() {
    Node *temp;

    while (top != NULL) {
        temp = top;
        top = top->next;
        free(temp);
    }
    /*
    while (!is_empty()) {
        pop();
    }
    */
}

int is_number(const char *str) {
    int i = 0;
    
    if (*(str) == '-' && str[1] == '\0') return 0;

    if (*(str) == '-') {
        i = 1;
    }

    int dot_count = 0;
    for (; *(str + i) != '\0'; i++) {
        if (*(str + i) == '.') {
            dot_count++;
            if (dot_count > 1) return 0;
        }
        else if (!isdigit(*(str + i))) {
            return 0;
        }
    }
    return 1;
}