#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *text, int shift);
void decrypt(char *text, int shift);
void clear_input_buffer();
void clean_newline(char *string);

int main() {
    char text[200];
    int shift;

    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    clean_newline(text);

    printf("Enter shift amount (key): ");
    scanf("%d", &shift);
    clear_input_buffer();

    encrypt(text, shift);
    printf("Encrypted text: %s\n", text);

    decrypt(text, shift); // or encrypt(text, 26-shift);
    printf("Decrypted text: %s\n", text);

    return 0;
}

void encrypt(char *text, int shift) {
    int len = strlen(text);
    char base;
    int i;

    for (i = 0; i < len; i++) {
        if (isalpha(*(text + i))) {
            base = isupper(*(text + i)) ? 'A': 'a';
            *(text + i) = ( ( *(text + i) + shift - base ) % 26 ) + base;

        }
    }
}

void decrypt(char *text, int shift) {
    int len = strlen(text);
    char base;
    int i;

    for (i = 0; i < len; i++) {

        if (isalpha(*(text + i))) {
            base = isupper(*(text + i)) ? 'A': 'a';
              
            *(text + i) = ( ( *(text + i) - shift - base + 26) % 26 ) + base;

            }
        }
}


void clear_input_buffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {

    }
}

void clean_newline(char *string) {
    char *p = strchr(string, '\n');

    if (p != NULL) {
        *p = '\0';
    }
    else {
        clear_input_buffer();
    }
}