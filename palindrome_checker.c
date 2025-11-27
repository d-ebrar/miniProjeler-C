#include <stdio.h>
#include <string.h>
#include <ctype.h>

void is_palindrom(char *start_ptr);
void standardize_to_lower(char *s);

int main() {
    char input_text[100];
    char *newline_ptr;
    int len = sizeof(input_text);

    printf("Please enter a text (Max 99 characters):\n");

    while (1) {
        fgets(input_text, len, stdin);
        if (input_text != NULL) {
            newline_ptr = strchr(input_text, '\n');
            if (newline_ptr != NULL) {
                *newline_ptr = '\0';
            }
            break; 
        }
        else {
            printf("You've exceeded the limit! Try again (Max 99 characters):\n");
        }
    }
    
    standardize_to_lower(input_text);

    is_palindrom(input_text);

    return 0;
}

void standardize_to_lower(char *s) {
    int i;

    while (*s != '\0') {
        *s = (char)tolower((unsigned char)*s);
        s++; 
    }
}

void is_palindrom(char *start_ptr) {
    int i;
    char *original_ptr = start_ptr;
    char *end_ptr = start_ptr + strlen(start_ptr) - 1;

    while (start_ptr < end_ptr) {
        if (*start_ptr != *end_ptr) {
            printf("The text \"%s\" is NOT a Palindrome.\n", original_ptr);
            return ;
        }
        start_ptr++;
        end_ptr--;
    }

    printf("The text \"%s\" is a Palindrome.\n", original_ptr);

    return;
}