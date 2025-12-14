#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[100], compressed[200];
    char *ptr_text = text, *ptr_compressed = compressed;
    int i = 0, k = 0, has_digit;


    do {
        has_digit = 0;

        printf("Enter data to compress (Letters only): ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = 0; 

        for (i = 0; *(ptr_text + i) != '\0'; i++) {
            
            if (isdigit(*(ptr_text + i))) {
                has_digit = 1;
                printf("Error: Input cannot contain numbers! Try again.\n");
                break; 
            }
        }

    } while (has_digit); 

    int len = strlen(text);
    int counter = 1;

    for (i = 0; i < len; i++) {
        

        if (*(ptr_text + i) == *(ptr_text + i + 1)) {
        counter ++;
        }
        else {
            k += sprintf(ptr_compressed + k, "%d%c", counter, *(ptr_text + i));

            counter = 1;
        }
    }
    *(ptr_compressed + k) = '\0';

    printf("Original text:   %s\n", text);
    printf("Compressed text: %s\n", compressed);
    
    return 0;
}