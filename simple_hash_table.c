#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node {
    char key[50];
    int value;
    struct Node *next;
} Node;

Node *hash_table[TABLE_SIZE];

unsigned int hash_function(const char *key) {
    int i = 0, temp, result = 0;

    while (key[i] != '\0') {
        result += key[i];
        i++;
    }
    return (result % TABLE_SIZE);
}

void insert(const char *key, int value) {
    unsigned int index = hash_function(key);

    Node *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    Node *new_node = (Node *)calloc(1, sizeof(Node));

    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    strncpy(new_node->key, key, 49);
    new_node->key[49] = '\0';
    
    new_node->value = value;
    new_node->next = hash_table[index];

    hash_table[index] = new_node;

    printf("Added %s -> Index %d\n", key, index);
}

int search(const char *key) {
    unsigned int index = hash_function(key);
    
    Node *current = hash_table[index];

    while (current != NULL) {
        
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void print_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *temp = hash_table[i];
        printf("Index %d: ", i);
        
        while (temp != NULL) {
            printf("[%s: %d] -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void free_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        
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

int main() {
    
    for (int i = 0; i < TABLE_SIZE; i++) hash_table[i] = NULL;

    printf("--- Simple Hash Table ---\n");

    insert("Ali", 100);
    insert("Mehmet", 200);
    insert("Elif", 300);
    insert("Zehra", 400);
    
    insert("And", 5); 
    insert("Nda", 10);

    print_table();

    printf("\nSearch Results:\n");
    printf("Mehmet's Value: %d\n", search("Mehmet"));
    printf("Nda's Value: %d\n", search("Nda"));
    printf("Ayşe's Value: %d\n", search("Ayşe"));

    free_table();

    return 0;
}