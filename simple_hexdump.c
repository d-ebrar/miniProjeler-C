#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define CHUNK_SIZE 16

void print_hex_dump(const char *filename);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    print_hex_dump(argv[1]);
    
    return 0;
}

void print_hex_dump(const char *filename) {
    FILE *file = fopen(filename, "rb");
    
    if (file == NULL) {
        printf("Error: Could not open file '%s'\n", filename);
        return;
    }

    unsigned char buffer[CHUNK_SIZE];
    size_t bytes_read;
    long offset = 0;

    printf("Offset    Hex Representation                 ASCII\n");
    printf("--------  ---------------------------------  ----------------\n");

    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, file)) > 0) {
        
        printf("%08lX  ", offset);

        for (int i = 0; i < CHUNK_SIZE; i++) {
            if (i < bytes_read) {
                printf("%02X ", buffer[i]);
            } else {
                printf("   "); 
            }
        }

        printf(" ");
        for (int i = 0; i < bytes_read; i++) {
            if (isprint(buffer[i])) {
                printf("%c", buffer[i]);
            }
            else {
                printf(".");
            }
        }

        printf("\n");
        offset += bytes_read;
    }

    fclose(file);
}