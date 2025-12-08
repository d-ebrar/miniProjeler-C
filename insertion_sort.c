#include <stdio.h>

void insertion_sort(int *array, size_t length);

int main() {
    int numbers[] = {67, 34, 25, 12, 24, 13, 91, 5};
    int i;
    
    size_t length = sizeof(numbers) / sizeof(numbers[0]);

    printf("Original array: %d", *numbers);
    for (i = 1; i < length; i++) {
        printf(", %d", *(numbers+i));
    }

    insertion_sort(numbers, length);

    printf("\nSorted array: %d", *numbers);
    for (i = 1; i < length; i++) {
        printf(", %d", *(numbers+i));
    }

    printf("\n");

    return 0;
}

void insertion_sort(int *array, size_t length) {
    int i;

    for (i = 1; i < length; i++) {
        int j = i - 1;
        int key = *(array + i);

        while (j >= 0 && *(array + j) > key) {

            *(array + j + 1) = *(array + j);
            j--;
        }

        *(array + j + 1) = key;
    }
}