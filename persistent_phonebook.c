#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_VERSION 1
#define DB_SIGNATURE "PHBK"
#define MAX_NAME 50
#define MAX_PHONE 20

typedef struct {
    char signature[5];
    int version;
    int record_count;
} FileHeader;

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
} Person;

Person *directory = NULL;
FileHeader header;
int capacity = 2;

void load_data();
void save_data();
void add_person();
void print_directory();
void get_safe_string(char *buffer, int size);

int main() {
    memset(&header, 0, sizeof(FileHeader));

    strcpy(header.signature, DB_SIGNATURE);
    header.version = DB_VERSION;
    header.record_count = 0;

    load_data();

    int choice;
    while (1) {
        printf("\nPHONEBOOK v%d (%d records)\n", header.version, header.record_count);
        printf("1. Add Person\n2. List Directory\n3. Save & Exit\nSelect an option:");
        
        int c;
        if (scanf("%d", &choice) != 1) {
            while ((c = getchar()) != '\n' && c != EOF); continue;
        }
        while ((c = getchar()) != '\n' && c != EOF);

        if (choice == 1) {
            add_person();
        }
        else if (choice == 2) {
            print_directory();
        }
        else if (choice == 3) {
            save_data();
            break;
        }
    }

    if (directory != NULL) {
        free(directory);
        directory = NULL;
    }
    return 0;
}

void load_data() {
    FILE *file = fopen("phonebook.bin", "rb");
    
    if (file == NULL) {
        printf("No database found. Initializing empty directory.\n");
        directory = (Person *)calloc(capacity, sizeof(Person));

        if (directory == NULL) {
            exit(1);
        }
        return;
    }

    FileHeader temp_header;

    if (fread(&temp_header, sizeof(FileHeader), 1, file) != 1) {
        printf("ERROR: Could not read file header!\n");
        fclose(file);
        exit(1);
    }

    if (memcmp(temp_header.signature, DB_SIGNATURE, 4) != 0) {
        printf("ERROR: File corrupted or invalid format!\n");
        fclose(file);
        exit(1);
    }

    if (temp_header.version != DB_VERSION) {
        printf("ERROR: Version mismatch! File is v%d, App is v%d.\n", temp_header.version, DB_VERSION);
        fclose(file);
        exit(1);
    }

    header = temp_header;

    capacity = (header.record_count > 0) ? header.record_count * 2 : 2;

    directory = (Person *)calloc(capacity, sizeof(Person));

    if (directory == NULL) {
        printf("Critical Error: Could not allocate memory during load!\n");
        fclose(file);
        exit(1);
    }

    if (header.record_count > 0) {
        size_t read_count = fread(directory, sizeof(Person), header.record_count, file);

        if (read_count != (size_t)header.record_count) {
            printf("Warning: File might be corrupted. Expected %d records, read %zu.\n", header.record_count, read_count);
            header.record_count = (int)read_count;
        }

        printf("%d records loaded successfully.\n", header.record_count);
    }

    fclose(file);
}

void save_data() {
    FILE *file = fopen("phonebook.bin", "wb");
    
    if (file == NULL) {
        printf("Error: Could not save data!\n");
        return;
    }

    fwrite(&header, sizeof(FileHeader), 1, file);

    size_t written = fwrite(directory, sizeof(Person), header.record_count, file);

    if (written != (size_t)header.record_count) {
        printf("Error: Only %zu of %d records were saved!\n", written, header.record_count);
    } else {
        printf("Data saved successfully to phonebook.bin (Total: %d records)\n", header.record_count);
    }

    fclose(file);
}

void add_person() {
    if (header.record_count == capacity) {
        
        Person *temp = (Person *)realloc(directory, capacity * 2 * sizeof(Person));

        if (temp == NULL) {
            printf("Error: Memory expansion failed! Cannot add more people.\n");
            return;
        }
        
        directory = temp;

        memset(directory + capacity, 0, capacity * sizeof(Person));
        
        capacity *= 2;

        printf("Memory expanded to %d\n", capacity);
    }

    printf("Name: ");
    get_safe_string(directory[header.record_count].name, MAX_NAME);

    printf("Phone: ");
    get_safe_string(directory[header.record_count].phone, MAX_PHONE);

    header.record_count++;
    printf("Record added.\n");
}

void print_directory() {
    int i;

    if (header.record_count == 0) {
        printf("Directory is empty.\n");
        return;
    }
    for (i = 0; i < header.record_count; i++) {
        printf("#%d: %s - %s\n", i+1, directory[i].name, directory[i].phone);
    }
}

void get_safe_string(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        
        char *p = strchr(buffer, '\n');
        
        if (p != NULL) {
            *p = '\0';
        }
        else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}