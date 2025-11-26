#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool prime_checker(int number);
bool prime_checker_with_sqrt(int number);

int main() {
    int number_to_check;

    printf("Enter a number for primality testing: ");
    scanf("%d", &number_to_check);

    while (number_to_check <= 1) {
        printf("Invalid number entered.\nPlease try again: ");
        scanf("%d", &number_to_check);
    }

    if (prime_checker(number_to_check)) {
        printf("%d is a prime number. (Checked with half of number method)\n", number_to_check);
    }
    else {
        printf("%d is not a prime number.\n", number_to_check);
    }

    if (prime_checker(number_to_check)) {
        printf("%d is a prime number. (Checked with sqrt of number method)\n", number_to_check);
    }
    else {
        printf("%d is not a prime number.\n", number_to_check);
    }


    return 0;
}

bool prime_checker(int number) {
    int i;

    if (number == 2) {
        return true;
    }
    else if (number%2 == 0) {
        return false;
    }
    else {
        for (i = 3; i < number/2; i += 2) {
            if (number%i == 0) {
                return false;
            }
        }
    }
    
    return true;
}

bool prime_checker_with_sqrt(int number) {
    int i;

    if (number == 2) {
        return true;
    }
    else {
        for(i = 3; i < sqrt(number); i+=2)
            if (number%i == 0) {
                return false;
            }
    }
    return true;
}