#include <stdio.h>

void swap(int *a, int *b);
void selection_sort(int *array, size_t length);

int main() {
    int numbers[] = {67, 34, 25, 12, 24, 13, 91};
    int i;
    
    size_t length = sizeof(numbers) / sizeof(numbers[0]);

    printf("Original array: %d", *numbers);
    for (i = 1; i < length; i++) {
        printf(", %d", *(numbers+i));
    }

    selection_sort(numbers, length);

    printf("\nSorted array: %d", *numbers);
    for (i = 1; i < length; i++) {
        printf(", %d", *(numbers+i));
    }

    printf("\n");

    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;

    *a = *b;
    *b = temp;
}

void selection_sort(int *array, size_t length) {
    int i, j;
    int *min_ptr;

    for (i = 0; i < length - 1; i++) {
        min_ptr = (array + i);

        for (j = i + 1; j < length; j++) {
            if (*min_ptr > *(array+j)) {
                min_ptr = (array+j);
            }
        }

        if (min_ptr != (array + i)) {
            swap(array + i, min_ptr);
        }
    }
}