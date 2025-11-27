#include <stdio.h>
#include <string.h>
#include <ctype.h>

void is_palindrom(char *string);
void standardize_to_lower(char *s);

int main() {
    char word[100];
    int len = sizeof(word);

    printf("Lütfen bir metin giriniz (Max %d karakter):\n", strlen(word));

    while (1) {
        fgets(word, len, stdin);
        if (len> 0 && word[len - 1] == '\n') {
            word[len - 1] = '\0';
            break;
        } 
        else {
            printf("Siniri astiniz! Tekrar deneyin (Max %d karakter):\n", len);
        }
    }
    
    standardize_to_lower(word);

    is_palindrom(word, len);

    return 0;
}

void standardize_to_lower(char *s) {
    int i;

    for (i = 0; s[i] != '\0'; i++) {
        s[i] = (char)tolower((unsigned char)s[i]); 
    }
}

void is_palindrom(char *string, int length) {
    int i;

    for (i = 0; i < length/2; i++) {

        if (string[i] != string[length-i-1]) {

            printf("%s, kelimeniz Palindrom değilir.\n", string);

            return;
        }
    }

    printf("%s, kelimeniz Palindrom'dur.\n", string);

    return;
}