#include <stdio.h>
#include <string.h>

struct Book {
    char title[100];
    char author[50];
    int publication_year;
    float price;
};

int main() {
    int c;
    struct Book b1 = {"", "Sabahattin Ali", 1937, 0};
    struct Book b2;
    
    snprintf(b1.title, sizeof(b1.title), "%s", "Kuyucakli Yusuf");
    b1.price = 16.30;

    printf("Enter Book 2 Details\n");

    printf("Title: ");
    fgets(b2.title, sizeof(b2.title), stdin);

    printf("Author: ");
    fgets(b2.author, sizeof(b2.author), stdin);

    printf("Publication year: ");
    scanf("%d", &b2.publication_year);
    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("Price: ");
    scanf("%f", &b2.price);
    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("\n--- Book 1 Information ---\n");
    printf("Title: %s\n", b1.title); 
    printf("Author: %s\n", b1.author);
    printf("Publication year: %d\n", b1.publication_year);
    printf("Price: %.2f TL\n\n", b1.price);

    printf("--- Book 2 Information ---\n");
    printf("Title: %s", b2.title); 
    printf("Author: %s", b2.author);
    printf("Publication year: %d\n", b2.publication_year);
    printf("Price: %.2f TL\n", b2.price);

    return 0;
}