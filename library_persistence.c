#include <stdio.h>
#include <string.h>

#define MAX_BOOK 100

struct Book {
    char title[75];
    char author[50];
    int page;
    float price;
};

void add_book_information(struct Book *b, int i);
int load_books_from_file(struct Book *b_file);
void save_library_to_file(struct Book *b_file, int count);
void clear_input_buffer();
void clean_new_line(char *str);

int main() {
    struct Book library_list[MAX_BOOK];
    int book_count = 0;
    
    book_count = load_books_from_file(library_list);
    printf("%d books loaded from file.\n", book_count);

    while (book_count < MAX_BOOK) {
        int add_count, i;

        printf("How many books you want to add? (Max %d number)\n", MAX_BOOK - book_count);
        scanf("%d", &add_count);
        clear_input_buffer();

        if ((book_count + add_count) <= MAX_BOOK) {

            for (i = 0; i < add_count; i++) {
                struct Book *ptr_book = &library_list[book_count];
                add_book_information(ptr_book, book_count);
                book_count ++;
            }

            break;
        }
        else {
            printf("You have exceeded the limit! Please enter a valid number.\n");
        }
    }

    save_library_to_file(library_list, book_count);
    printf("Library successfully saved.\n");

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

void save_library_to_file(struct Book *b_file, int count) {
    FILE *fptr = fopen("library.txt", "w");

    if (fptr == NULL) {
        printf("Error: Could not save to file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fptr, "%s\n%s\n%d\n%.2f\n", 
            (b_file + i)->title, 
            (b_file + i)->author, 
            (b_file + i)->page, 
            (b_file + i)->price);
    }
    fclose(fptr);
}

int load_books_from_file(struct Book *b_file) {
    FILE *fptr;
    int count = 0;

    fptr = fopen("library.txt", "r");

    if (fptr == NULL) {
        return 0;
    }

    while (count < MAX_BOOK) {

        if (fscanf(fptr, " %[^\n]", (b_file + count)->title) == EOF) break;

        fscanf(fptr, " %[^\n]", (b_file + count)->author);
        fscanf(fptr, "%d", &(b_file + count)->page);
        fscanf(fptr, "%f", &(b_file + count)->price);

        count++;
    }

    fclose(fptr);

    return count;
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