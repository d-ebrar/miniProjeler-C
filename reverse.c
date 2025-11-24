#include <stdio.h>
void reverse_array(int *array_ptr, size_t array_size) {
    int i;
    for (i = 0; i < array_size/2; i++) {
        int temp_value = array_ptr[i];

        array_ptr[i] = array_ptr[array_size - 1 - i];
        array_ptr[array_size - 1 - i] = temp_value;
    }
}

int main() {
    int k;
    int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    size_t array_size = sizeof(numbers) / sizeof(numbers[0]);

    reverse_array(numbers, array_size);

    printf("Reverse array: \n%d", numbers[0]);
    for (k = 1; k < array_size; k++) printf(", %d ", numbers[k]);

    return 0;
}