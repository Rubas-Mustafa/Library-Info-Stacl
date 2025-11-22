#include <stdio.h>
#include <string.h>
#include "book.h"

#define MAX_BOOKS 20
struct Book books[MAX_BOOKS];
int bookCount = 0;

// Load books from books.txt into memory
void loadBooks() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        return; // no previous data
    }

    bookCount = 0;

    while (fscanf(file, "%d,%[^,],%[^,],%d\n",
                  &books[bookCount].id,
                  books[bookCount].title,
                  books[bookCount].author,
                  &books[bookCount].quantity) == 4) 
    {
        bookCount++;
    }

    fclose(file);
}

// Save books from memory into books.txt
void saveBooks() {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error saving books.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%d,%s,%s,%d\n",
                books[i].id,
                books[i].title,
                books[i].author,
                books[i].quantity);
    }

    fclose(file);
}

// Adding a new book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Book storage is full.\n");
        return;
    }

    struct Book b;

    printf("Enter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Title: ");
    getchar(); // consume newline
    fgets(b.title, 50, stdin);
    b.title[strcspn(b.title, "\n")] = 0; // remove newline

    printf("Enter Book Author: ");
    fgets(b.author, 50, stdin);
    b.author[strcspn(b.author, "\n")] = 0; // remove newline

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    books[bookCount] = b;
    bookCount++;

    saveBooks();
    printf("Book added successfully.\n");
}

// show all books
void viewBooks() {
    if (bookCount == 0) {
        printf("No books available.\n");
        return;
    }

    printf("\n--- BOOK LIST ---\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d | Title: %s | Author: %s | Quantity: %d\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].quantity);
    }
}

// Searching a book by its ID
void searchBook() {
    int id;
    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            printf("Book Found!\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\n",
                   books[i].id,
                   books[i].title,
                   books[i].author,
                   books[i].quantity);
            return;
        }
    }

    printf("Book not found.\n");
}

// Updating the book using its ID
void updateBook() {
    int id;
    printf("Enter Book ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            printf("Updating Book ID %d\n", id);

            printf("Enter new title: ");
            getchar();
            fgets(books[i].title, 50, stdin);
            books[i].title[strcspn(books[i].title, "\n")] = 0;

            printf("Enter new author: ");
            fgets(books[i].author, 50, stdin);
            books[i].author[strcspn(books[i].author, "\n")] = 0;

            printf("Enter new quantity: ");
            scanf("%d", &books[i].quantity);

            saveBooks();
            printf("Book updated successfully.\n");
            return;
        }
    }

    printf("Book not found.\n");
}

// Deleting book by using book ID
void deleteBook() {
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            // Shifting the book down to fill the gap
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }

            bookCount--;
            saveBooks();
            printf("Book deleted successfully.\n");
            return;
        }
    }

    printf("Book not found.\n");
}

