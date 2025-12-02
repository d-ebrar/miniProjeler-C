#include <stdio.h>
#include <string.h>

#define MAX_BOOK 3

struct Book {
    char title[75];
    char author[50];
    int page;
    float price;
};

void add_book_information(struct Book *b, int i);
void list_book_info(struct Book book_info, int i);
void clear_input_buffer();
void clean_new_line(char *str);
void save_library_to_file(struct Book *b_file);

int main() {
    int i;
    struct Book library_list[MAX_BOOK];
    struct Book *ptr_book;

    for (i = 0; i < MAX_BOOK; i++) {
        ptr_book = &library_list[i];
        add_book_information(ptr_book, i);
    }

    for (i = 0; i < MAX_BOOK; i++) {
        list_book_info(library_list[i], i);
    }

    save_library_to_file(library_list);

    return 0;
}

void add_book_information(struct Book *b, int i) {
    printf("Enter Book %d Details\n", i+1);

    printf("Title: ");
    fgets(b->title, sizeof(b->title), stdin);
    clean_new_line(b->title);

    printf("Author: ");
    fgets(b->author, sizeof(b->author), stdin);
    clean_new_line(b->author);

    printf("Page: ");
    scanf("%d", &b->page);
    clear_input_buffer();

    printf("Price: ");
    scanf("%f", &b->price);
    clear_input_buffer();
}

void list_book_info(struct Book book_info, int i) {
    printf("Book %d: %s by %s\n", i+1, book_info.title, book_info.author);
    printf("\tPage: %d\n", book_info.page);
    printf("\tPrice: %.2f\n", book_info.price);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
} 

void clean_new_line(char *str) {
    char *p = strchr(str, '\n'); 

    if (p != NULL) {
        *p = '\0';
    }
    else {
        clear_input_buffer();
    }
}

void save_library_to_file(struct Book *b_file) {
    int c;
    FILE *fptr; 

    fptr = fopen("library_book_list.txt", "w");

    if (fptr != NULL) {
        for (c = 0; c < MAX_BOOK; c++) {
        fprintf(fptr, "Book %d: %s\n -Author: %s\n -Page %d\n -Price: %.2f\n", c+1, (b_file+c)->title, 
                (b_file+c)->author, (b_file+c)->page, (b_file+c)->price);
        }

        fclose(fptr);
    }

    else {
        printf("Not able to write the file!");
    }

}