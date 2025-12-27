#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 5
#define LOAD_FACTOR_THRESHOLD 0.7

typedef struct Node {
    char key[50];
    int value;
    struct Node *next;
} Node;

Node **hash_table = NULL; 
int current_table_size = INITIAL_SIZE;
int element_count = 0;

unsigned int hash_function(const char *key, int size);
void insert(const char *key, int value);
void resize_table();
void print_table();
void free_table();

int main() {
    hash_table = (Node **)calloc(current_table_size, sizeof(Node *));
    if (!hash_table) return 1;

    printf("Dynamic Hash Table (Initial Size: %d)\n", current_table_size);

    insert("Ali", 10);
    insert("Veli", 20);
    insert("Selim", 30);
    
    printf("\n[Check] Adding 4th element (Should trigger resize)...\n");
    insert("Rüya", 40);

    insert("Züleyha", 50);
    insert("Ayşe", 60);

    print_table();
    
    free_table();

    return 0;
}

unsigned int hash_function(const char *key, int size) {
    int i = 0, result = 0;
    while (key[i] != '\0') {
        result += key[i];
        i++;
    }
    return (result % size);
}

void insert(const char *key, int value) {

    float load_factor = (float)(element_count + 1) / current_table_size;
    
    if (load_factor > LOAD_FACTOR_THRESHOLD) {
        printf("[SYSTEM] Load Factor %.2f exceeded. Resizing...\n", load_factor);
        resize_table();
    }

    unsigned int index = hash_function(key, current_table_size);
    
    Node *new_node = (Node *)calloc(1, sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    strcpy(new_node->key, key);
    new_node->value = value;
    
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
    
    element_count++;
    printf("Inserted: %s (Index: %d)\n", key, index);
}

void resize_table() {
    int i, new_size = current_table_size * 2;
    
    Node **new_table = (Node **)calloc(new_size, sizeof(Node *));
    if (new_table == 0) {
        printf("Resize memory allocation failed!\n");
        return;
    }

    for (i = 0; i < current_table_size; i++) {
        Node *current = hash_table[i];
        
        while (current != NULL) {
            Node *next_node = current->next;
            
            unsigned int new_index = hash_function(current->key, new_size);

            current->next = new_table[new_index];
            new_table[new_index] = current;

            current = next_node;
        }
    }

    free(hash_table);

    hash_table = new_table;
    current_table_size = new_size;
    
    printf("[SYSTEM] Resize Complete. New Size: %d\n", current_table_size);
}

void print_table() {
    printf("\n--- Table Status ---\n");
    for (int i = 0; i < current_table_size; i++) {
        printf("[%d]: ", i);
        Node *temp = hash_table[i];

        while (temp) {
            printf("%s -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void free_table() {
    int i;
    for(i = 0; i < current_table_size; i++) {
        Node *current = hash_table[i];

        while (current != NULL) {
            Node *temp = current;
            current = current->next;

            free(temp);
        }

        hash_table[i] = NULL;
    }

    printf("Table cleaned up successfully.\n");
}