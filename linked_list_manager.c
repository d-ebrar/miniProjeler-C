#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *add_first(struct Node *head, int value);
struct Node *add_last(struct Node *head, int value);
struct Node *delete_node(struct Node *head, int value);
void print_list(struct Node *head);
void free_list(struct Node *head);
int get_safe_int();

int main() {
    struct Node *head = NULL;
    int choice, value;

    printf("--- Linked List Manager ---\n");

    while (1) {
        printf("\nMENU:\n");
        printf("1. Add Node to Beginning\n");
        printf("2. Add Node to End\n");
        printf("3. Delete a Node\n");
        printf("4. Print List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        choice = get_safe_int();

        if (choice == 5) {
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter integer value to add: ");
                value = get_safe_int();
                head = add_first(head, value);
                printf("--> %d added to the beginning successfully.\n", value);
                break;

            case 2:
                printf("Enter integer value to add: ");
                value = get_safe_int();
                head = add_last(head, value);
                printf("--> %d added to the end successfully.\n", value);
                break;

            case 3:
                printf("Enter integer value to delete: ");
                value = get_safe_int();
                head = delete_node(head, value);
                break;
            case 4:
                printf("\nCurrent List:\n");
                print_list(head);
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    free_list(head);

    printf("Exiting program... Memory cleaned.\n");

    return 0;
}

struct Node *add_first(struct Node *head, int value) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    new_node->data = value;
    new_node->next = head;

    return new_node;
}

struct Node *add_last(struct Node *head, int value) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    new_node->data = value;
    new_node->next = NULL;

    if (head == NULL) {
        return new_node;
    }

    struct Node *temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;

    return head;
}

struct Node *delete_node(struct Node *head, int value){
    struct Node *temp = head;
    struct Node *prev = NULL;

    if (temp == NULL) {
        printf("List is empty, nothing to delete.\n");
        return NULL;
    }

    if (temp != NULL && temp->data == value) {
        head = temp->next;
        free(temp);
        return head;
    }

    while(temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Element %d not found in the list.\n", value);
        return head;
    }

    prev->next = temp->next;
    free(temp);
    printf("--> %d deleted successfully .\n", value);

    return head;
}

void print_list(struct Node *head) {
    struct Node *temp = head;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("-NULL-\n");
}

void free_list(struct Node *head) {
    struct Node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int get_safe_int() {
    int num;

    while (scanf("%d", &num) != 1) {
        printf("Incorrect input! Please enter an integer: ");
        while(getchar() != '\n');
    }

    char c; 
    while((c = getchar()) != '\n' && c != EOF) {}

    return num;
}