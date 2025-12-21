#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char phone[15];
} Person;

Person *directory = NULL;
int count = 0;
int capacity = 2;

void load_data();
void save_data();
void add_person();
void print_directory();
void get_safe_string(char *buffer, int size);

int main() {
    load_data();

    int choice;
    while (1) {
        printf("\nBINARY PHONEBOOK (%d records)\n", count);
        printf("1. Add Person\n");
        printf("2. List Directory\n");
        printf("3. Save & Exit\n");
        printf("Select an option: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); continue;
        }
        while(getchar() != '\n');

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
        printf("No existing database found. Creating new one.\n");
        directory = (Person *)calloc(capacity, sizeof(Person));

        if (directory == NULL) {
            exit(1);
        }
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    count = file_size / sizeof(Person);
    if (count > 0) {
        capacity = 2 * count;
    }
    else {
        capacity = 2;
    }

    directory = (Person *)malloc(capacity * sizeof(Person));

    if (directory == NULL) {
        printf("Critical Error: Could not allocate memory during load!\n");
        fclose(file);
        exit(1);
    }

    if (count > 0) {
        size_t read_count = fread(directory, sizeof(Person), count, file);
        if (read_count != (size_t)count) {
            printf("Warning: File might be corrupted. Expected %d records, read %zu.\n", count, read_count);
            count = (int)read_count;
            }
            printf("%d records loaded from binary file.\n", count);
        }

    fclose(file);
}

void save_data() {
    FILE *file = fopen("phonebook.bin", "wb");
    
    if (file == NULL) {
        printf("Error: Could not save data!\n");
        return;
    }

    size_t written = fwrite(directory, sizeof(Person), count, file);

    if (written != (size_t)count) {
        printf("Error: Only %zu of %d records were saved!\n", written, count);
    } else {
        printf("Data saved successfully to phonebook.bin (Total: %d records)\n", count);
    }


    fclose(file);
}

void add_person() {
    if (count == capacity) {
        
        Person *temp = (Person *)realloc(directory, capacity * 2 * sizeof(Person));

        if (temp == NULL) {
            printf("Error: Memory expansion failed! Cannot add more people.\n");
            return;
        }
        
        directory = temp;
        capacity *= 2;

        printf("Memory expanded to %d\n", capacity);
    }

    printf("Name: ");
    get_safe_string(directory[count].name, 50);

    printf("Phone: ");
    get_safe_string(directory[count].phone, 15);

    count++;
    printf("Record added.\n");
}

void print_directory() {
    if (count == 0) {
        printf("Directory is empty.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("#%d: %s - %s\n", i+1, directory[i].name, directory[i].phone);
    }
}

void get_safe_string(char *buffer, int size) {
    fgets(buffer, size, stdin);
    char *p = strchr(buffer, '\n');
    if (p) *p = 0;
}