#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void get_valid_guess(int *number);
void check_guess(int *number, int *sec_num);

int main() {
    srand(time(NULL)); 

    int secret_number = (rand() % 100) + 1;
    int guess, attempt_count = 0;

    printf("-----Welcome To The Number Guessing Game-----\n");
    printf("-I picked a number from 1 to 100. Try to guess!\n\n");

    do {
        get_valid_guess(&guess);
        check_guess(&guess, &secret_number);

        attempt_count += 1;

    } while (guess != secret_number);

    printf("You found it in %d attempts. Congratulations.\n", attempt_count);

    return 0;
}

void get_valid_guess(int *number) {
    int valid_input = 0;

    do {
        printf("Enter your guess (1-100): ");

        if (scanf("%d", number) == 1) {
            
            if (*number >= 1 && *number <= 100) {
                valid_input = 1;
            } 
            else {
                printf("Please enter a number between 1 and 100!\n");
            }
        }
        else {
            printf("Invalid input! Please enter a number.\n");
        }

        int c;
        while((c = getchar()) != '\n' && c != EOF) {}

    } while (!valid_input);
    
}

void check_guess(int *number, int *sec_num) {
    if (*number < *sec_num) {
        printf("-> Go HIGHER.\n");
    }
    else if (*number > *sec_num) {
        printf("-> Go LOWER.\n");
    }
    else {
        printf("\nCorrect!\n");
    }
}