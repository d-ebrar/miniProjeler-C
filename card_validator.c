#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool luhn_check(const char *card_number);

int main() {
    char card_num[50];
    
    printf("--- Credit Card Validator (Luhn Algorithm) ---\n");
    printf("Enter card number (no spaces): ");
    scanf("%s", card_num);

    if (luhn_check(card_num)) {
        printf("VALID! This is a mathematically valid card number.\n");
    } else {
        printf("INVALID! Checksum failed.\n");
    }

    return 0;
}

bool luhn_check(const char *card_number) {
    int len = strlen(card_number);
    int sum = 0;
    bool is_second = false;

    for (int i = len - 1; i >= 0; i--) {
        
        int digit = *(card_number + i) - '0';

        if (digit < 0 || digit > 9) {
            return false;
        }

        if (is_second) {
            digit = digit * 2;
            
            if (digit > 9) {
                digit -= 9; 
            }
        }

        sum += digit;

        is_second = !is_second;
    }

    return (sum % 10 == 0);
}