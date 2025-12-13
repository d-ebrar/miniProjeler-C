#include <stdio.h>

unsigned long long factorial(int n);
int get_non_negative_int();
    
int main() {
    int num;
    unsigned long long result;

    num = get_non_negative_int();

    result = factorial(num);
    printf("%d! = %llu\n", num, result);

    return 0;
}

unsigned long long factorial(int n) {

    if (n <= 1) {
        return 1;
    }
    else {
        return n * factorial(n-1);
    }
}

int get_non_negative_int() {
    int n;
    int valid = 0;
    
    do {
        printf("Enter a number to calculate factorial (must be non-negative): ");
        if (scanf("%d", &n) == 1 && n >= 0) {
            if (n <= 20) {
                valid = 1;
            }
            else {
                printf("Please enter a number up to a maximum of 20.\n");
            }
        } else {
            printf("Invalid input! Please enter a positive number or 0.\n");

            int c;
            while((c = getchar()) != '\n' && c != EOF) {}
        }
    } while (!valid);
    
    return n;
}