#include <stdio.h>

void swap(int *a, int *b);
void bubble_sort(int *numbers, size_t length);

int main() {
    int numbers[] = {67, 34, 25, 12, 24, 13, 91};
    int i;
    
    size_t length = sizeof(numbers) / sizeof(numbers[0]);

    printf("Original array: %d", *numbers);
    for (i = 1; i < length; i++) {
        printf(", %d", *(numbers+i));
    }

    bubble_sort(numbers, length);

    printf("\nSorted array: %d", *numbers);
    for (i = 1; i < length; i++) {
        printf(", %d", *(numbers+i));
    }

    printf("\n");

    return 0;
}

void swap(int *a, int *b) {
    int copy_a = *a;

    *a = *b;
    *b = copy_a;
}

void bubble_sort(int *array, size_t length) {
    int i, j;

    for (i = 0; i < length - 1 ; i++) {

        for (j = 0; j < length - i - 1; j++) {

            if (*(array+j) > *(array + j + 1)) {
                swap(array + j, array + j + 1);
            }
        }
    }
}