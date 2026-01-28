#include <stdio.h>
#include <math.h>

void calculateEvenAverage(int array[], int count);
void findMinMax(int array[], int count);
void sortSmallToLarge(int array[], int count);
void findPrimes(int array[], int count);
void printArray(int array[], int count);

int main() {
    int count, inputVal;
    
    printf("How many numbers will you enter? ");
    scanf("%d", &count);
    
    int numbers[count];
    
    for (int i = 0; i < count; i++) {
        printf("Enter number %d: ", i + 1);
        
        while (1) {
            if (scanf("%d", &inputVal) == 1) {
                char c = getchar();
                if (c == '\n' || c == EOF) {
                    break;
                }
            }
            printf("Error: Invalid input!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
        }
        
        numbers[i] = inputVal;
    }
    
    printf("Your Array:\n%d", numbers[0]);
    printArray(numbers, count);
    
    sortSmallToLarge(numbers, count);
    printf("Sorted from smallest to largest:\n%d", numbers[0]);
    printArray(numbers, count);
    
    calculateEvenAverage(numbers, count);
    findMinMax(numbers, count);
    findPrimes(numbers, count);
    
    return 0 ;
}

void calculateEvenAverage(int array[], int count) {
    int counter = 0;
    float total = 0;
    
    for (int i = 0; i < count; i++) {
        if ((array[i] % 2) == 0) {
            total += array[i];
            counter++;
        }
    }
    
    if (counter != 0) {
        printf("Average of even numbers: %.2f\n", total / counter);
        return;
    }
    
    printf("Average: 0 (None of the entered numbers are even.)\n");
}

void findMinMax(int array[], int count) {
    int min = array[0], max = array[0];
    
    for (int i = 1; i < count; i++) {
        if (min > array[i]) {
            min = array[i];
        }
        if (max < array[i]) {
            max = array[i];
        }
    }
    printf("Maximum: %d\n", max);
    printf("Minimum: %d\n", min);
}

void sortSmallToLarge(int array[], int count) {
    int temp;
    
    for (int k = 0; k < count; k++) {
        for(int i = k + 1; i < count; i++) {
            if (array[k] > array[i]) {
                temp = array[k];
                array[k] = array[i];
                array[i] = temp;
            }
        }
    }
}

void findPrimes(int array[], int count){
    int isPrime, primeExists = 0;
    
    printf("Primes: \n");
    for (int i = 0; i < count; i++) {
        isPrime = 0;
        
        if (array[i] <= 1 || (array[i] % 2 == 0 && array[i] != 2)) {
            continue;
        }
        else {
            isPrime = 1;
            int limit = (int)sqrt(array[i]);
            for (int k = 3; k <= limit; k += 2) {
                if ((array[i] % k) == 0) {
                    isPrime = 0;
                    break;
                }
            }
        }
        
        if (isPrime) {
            printf("%d ", array[i]);
            primeExists = 1;
        }
    }
    
    if (!primeExists) {
        printf("(No primes found)");
    }
    printf("\n");
}

void printArray(int array[], int count) {
    for (int i = 1; i < count; i++) {
        printf(", %d", array[i]);
    }
    printf("\n");
}