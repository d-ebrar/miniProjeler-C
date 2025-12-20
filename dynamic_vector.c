#include <stdio.h>
#include <stdlib.h>

int get_safe_number();
void clear_input_buffer();

int main() {
    int *list;
    int input, capacity = 2, count = 0;
    int choice, i;

    list = (int *)(calloc(2, sizeof(int)));

    if (list == NULL) {
        printf("Initial memory allocation failed!\n");
        return 1;
    }

    printf("Dynamic Vector Implementation\n");

    while (1) {
        printf("\nMENU:\n");
        printf("Select an option: \n");
        printf("1- Add Element\n2- Print Vector\n3- Exit\n");
        choice = get_safe_number();

        if (choice == 1) {
            if (count == capacity) {
                int *temp_ptr = realloc(list, (capacity * 2 * sizeof(int)));

                if (temp_ptr != NULL) {
                    list = temp_ptr;
                    capacity *= 2;
                    printf("Vector resized. New Capacity: %d\n", capacity);
                } else {
                    printf("Error: Memory full! Cannot expand list.\n");
                    continue;
                }
            }
            
            printf("Enter number to add: ");
            input = get_safe_number();

            *(list + count) = input;
            count++;
            printf("--> %d added successfully.\n", input);
        }

        else if (choice == 2) {
            if (count == 0) {
                printf("Vector is empty.\n");
            }
            else {
                printf("Vector Elements (%d/%d):\n[%d", count, capacity, *list);
                for (i = 1; i < count; i++) {
                    printf(", %d", list[i]);
                }
                printf("]\n");
            }
        }

        else if (choice == 3) {
            break;
        }

        else {
            printf("Enter a valid choice!\n"); 
        }
    }

    free(list);

    printf("Memory freed. Exiting safely...\n");

    return 0;
}

int get_safe_number() {
    int num;

    while (scanf("%d", &num) != 1) {
        while(getchar() != '\n');

        printf("Incorrect input! Please enter a valid number:\n");
    }

    clear_input_buffer();
    return num;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}