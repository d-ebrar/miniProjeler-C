#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <output_file> <key>\n", argv[0]);
        return 1;
    }

    char *input_name = argv[1];
    char *output_name = argv[2];
    int key = atoi(argv[3]);

    FILE *fin = fopen(input_name, "rb");
    FILE *fout = fopen(output_name, "wb");

    if (fin == NULL || fout == NULL) {
        printf("File error!\n");
        return 1;
    }

    printf("Encrypting file '%s' with key %d...\n", input_name, key);

    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        int new_ch = ch + key;
        fputc(new_ch, fout);
    }

    printf("Success! Output saved to '%s'\n", output_name);

    fclose(fin);
    fclose(fout);

    return 0;
}