#include <stdio.h>
#include <string.h>

struct Date {
    int day;
    char month[10];
    int year;
};

struct Book {
    char title[100];
    char author[50];
    struct Date pub_date;
    float price;
};

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void clean_new_line(char *str) {
    char *p = strchr(str, '\n');
    if (p != NULL) {
        *p = '\0';
    } else {
        clear_input_buffer();
    }
}

int main() {
    int c;
    struct Book b1 = {"", "Sabahattin Ali", {19, "July", 1937}, 0};
    struct Book b2;
    
    snprintf(b1.title, sizeof(b1.title), "%s", "Kuyucakli Yusuf");
    b1.price = 1.30;

    printf("Enter Book 2 Details\n");

    printf("Title: ");
    fgets(b2.title, sizeof(b2.title), stdin);
    clean_new_line(b2.title);

    printf("Author: ");
    fgets(b2.author, sizeof(b2.author), stdin);
    clean_new_line(b2.author);

    printf("Publication day: ");
    scanf("%d", &b2.pub_date.day);
    clear_input_buffer();

    printf("Publication month: ");
    fgets(b2.pub_date.month, sizeof(b2.pub_date.month), stdin);
    clean_new_line(b2.pub_date.month);

    printf("Publication year: ");
    scanf("%d", &b2.pub_date.year);
    clear_input_buffer();

    printf("Price: ");
    scanf("%f", &b2.price);
    clear_input_buffer();

    printf("\n--- Book 1 Information ---\n");
    printf("Title: %s\n", b1.title); 
    printf("Author: %s\n", b1.author);
    printf("Publication year: %d/%s/%d\n", b1.pub_date.day, b1.pub_date.month, b1.pub_date.year);
    printf("Price: $%.2f\n\n", b1.price);

    printf("--- Book 2 Information ---\n");
    printf("Title: %s", b2.title); 
    printf("Author: %s", b2.author);
    printf("Publication year: %d/%s/%d\n", b2.pub_date.day, b2.pub_date.month, b2.pub_date.year);
    printf("Price: $%.2f\n", b2.price);

    return 0;
}