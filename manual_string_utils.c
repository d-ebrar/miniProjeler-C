#include <stdio.h>

#define MAX_BUFFER_SIZE 100

int take_text_input(char *text);
size_t my_strlen(const char *p);
void my_strcat(char *dest, const char *src);
int my_strcmp(const char *s1, const char *s2);

int main() {
    char greeting[MAX_BUFFER_SIZE] = "Hello, ";
    char name[50];
    char string1[20];
    char string2[20];

    printf("Enter your name: ");
    take_text_input(name);

    printf("Length of greeting: %zu\n", my_strlen(greeting));
    printf("Length of name: %zu\n", my_strlen(name));

    my_strcat(greeting, name);
    printf("%s\n", greeting);
    printf("--------------------------------------\n");

    printf("Please enter the first word to compare:\n");
    take_text_input(string1);
    printf("Please enter the second word to compare:\n");
    take_text_input(string2);

    int result = my_strcmp(string1, string2);

    if (result == 0) {
        printf("Result: The strings are identical.\n");
    }
    else if (result > 0) {
        printf("Result: The first string comes AFTER the second one alphabetically.\n");
    }
    else {
        printf("Result: The first string comes BEFORE the second one alphabetically.\n");
    }

    return 0;
}

int take_text_input(char *text){
    char *temp_ptr;

    while (1) {
        if (fgets(text, 50, stdin) == NULL) {
            printf("Input error. Program terminated.\n");
            return 0; 
        }

        temp_ptr = text;

        while (*temp_ptr != '\0') {

            if (*temp_ptr == '\n') {

                *temp_ptr = '\0';
                return 1;
            }
            temp_ptr++;
        }

        printf("Error: Input too long (exceeded 49 chars). Please try again: \n");
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

size_t my_strlen(const char *p) {
    const char *start_p = p;   

    while (*p != '\0') {
        p++;
    }

    return (size_t)(p - start_p);
}

void my_strcat(char *dest, const char *src) {
    char *dest_ptr = dest;
    const char *src_ptr = src;

    while (*dest_ptr != '\0') {
        dest_ptr++;
    }

    while (*src_ptr != '\0') {
        *dest_ptr = *(src_ptr);

        dest_ptr++;
        src_ptr++;
    }

    *dest_ptr = '\0';

}

int my_strcmp(const char *s1, const char *s2) {

    while (*s1 == *s2 && *s1 != '\0'){
        s1++;
        s2++;
    }
    return (int)(unsigned char)*s1 - (int)(unsigned char)*s2;
}