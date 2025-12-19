#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

int get_safe_int();
void clear_input_buffer();

int main() {
    char **names;
    int number, i;

    printf("How many names will you enter?\n");
    number = get_safe_int();

    names = (char **)malloc(number * sizeof(char *));

    if (names == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (i = 0; i < number; i++) {

        *(names + i) = (char *) malloc(MAX_NAME_LEN * sizeof(char));

        if (*(names + i) == NULL) {
            printf("Memory allocation failed at index %d!\n", i);

            for (i -= 1; i >= 0; i --) {
                free(*(names + i));
            }

            free(names);

            printf("\nMemory cleaned. Exiting...\n");
            return 1;
        }

        printf("Enter name %d:\n", i+1);

        if (fgets(*(names + i), MAX_NAME_LEN, stdin) != NULL) {
            char *p = strchr(*(names + i), '\n');
                if (p != NULL) {
                *p = '\0';
                }
                else {
                    clear_input_buffer();
                }
        }
    }

    printf("\n--- List Of Names ---\n");
    for (i = 0; i < number; i++) {
        printf("%d. %s\n", i + 1, names[i]);
    }

    for (i = 0; i < number; i++) {
        free(*(names + i));
    }

    free(names);

    return 0;
}

int get_safe_int() {
    int num;
    while (scanf("%d", &num) != 1 || num <= 0) {
        while(getchar() != '\n'); 
        printf("Invalid input! Please enter a positive number:");
    }
    clear_input_buffer();
    return num;
}

void clear_input_buffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}