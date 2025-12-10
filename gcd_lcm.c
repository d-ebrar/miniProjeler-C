#include <stdio.h>

void get_positive_int(int *number);
int calculate_gcd(int a, int b);

int main() {
    int num1, num2;
    int gcd_value, lcm_value;

    printf("Enter the first positive number:\n");
    get_positive_int(&num1);

    printf("Enter the second positive number:\n");
    get_positive_int(&num2);

    gcd_value = calculate_gcd(num1, num2);
    lcm_value = (num1 * num2) / gcd_value;

    printf("gcd is %d\n", calculate_gcd(num1, num2));
    printf("lcm is %d\n", lcm_value);

    printf("First Number:  %d\n", num1);
    printf("Second Number: %d\n", num2);
    printf("\tGCD: %d\n", gcd_value);
    printf("\tLCM: %d\n", lcm_value);

    return 0;
}

void get_positive_int(int *number) {

    int input;
    scanf("%d", &input);

    while (input <= 0) {

        while (input <= 0) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
        }

        printf("Invalid input! Please enter a positive integer:\n");
        scanf("%d", &input);
    }

    *number = input; 
}

int calculate_gcd(int number1, int number2) {
    int remainder;

    while (1) {
        remainder = number1 % number2;

        if (remainder == 0) {
            return number2;
        }

        number1 = number2;
        number2 = remainder;
    }
}