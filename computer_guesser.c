#include <stdio.h>

void get_user_response(int *response_ptr);

int main() {
    int min = 1, max = 100;
    int guess;
    int response;
    int attempt_count = 0;

    printf("-----Welcome To The Number Guessing Game-----\n");
    printf("Please hold a number between 1-100 in your mind.\n");
    printf("Press Enter when you are ready...");
    getchar();

    while (1) {
        if (min > (max)) {
            printf("\nHey!\nYou are giving inconsistent answers. You are cheating!\n");
            return 0;
        }

        guess = (min + max) / 2;

        printf("\nMy guess is: %d\n", guess);

        get_user_response(&response);
        attempt_count++;

        if (response == 1) {
            printf("\nI knew it! I found it in %d attempts.\n", attempt_count);

            return 0;
        }
        else if (response == 2) {
            printf("GO HIGHER\n");
            min = guess + 1;
        }
        else if (response == 3) {
            printf("GO LOWER\n");
            max = guess - 1;
        }
    }
}


void get_user_response(int *response_ptr) {
    int valid_input = 0;

    do {
        printf("Is it true? (1: Yes, 2: Higher, 3: Lower)\n");

        if (scanf("%d", response_ptr) == 1) {
            
            if (*response_ptr >= 1 && *response_ptr <= 3) {
                valid_input = 1;
            } 
            else {
                printf("Please enter 1, 2, or 3!\n");
            }
        }
        else {
            printf("Invalid input! Please enter a response.\n");
        }

        int c;
        while((c = getchar()) != '\n' && c != EOF) {}

    } while (!valid_input);
}