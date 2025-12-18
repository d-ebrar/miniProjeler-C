#include <stdio.h>
#include <stdlib.h>

int get_safe_int();

int main() {
    int number, i;

    printf("How many numbers do you want to store?\n");
   
    do {
        number = get_safe_int();
        if (number <= 0) {
            printf("Please enter a positive number: ");
        }
    } while (number <= 0);

    int *ptr = (int *)malloc(number * sizeof(int));

    if (ptr == NULL) {
        printf("Unable to allocate memory!");
        return 1;
    }

    for (i = 0; i < number; i++) {
        printf("Enter the %d. number : \n", i+1);
        *(ptr + i) = get_safe_int();
    }

    printf("Numbers:\n%d", *(ptr));
    for (i = 1; i < number; i++) {
        printf(", %d", *(ptr + i));
    }

    free(ptr);
    ptr = NULL;

    return 0;
}

int get_safe_int() {
    int num;

    while (1) {
        int input = scanf("%d", &num);

        if (input != 1) {
            while(getchar() != '\n'); 
            printf("Incorrect input! Please enter an integer: ");
        }
        else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            return num;
        }
    }
}