#include <stdio.h>
#include <string.h>
#include "book.h"

#define MAX_BOOKS 20

struct Book books[MAX_BOOKS]; // memory array for books
int bookCount = 0;            // number of books in memory

// ---------------- Load books from books.txt into memory ----------------
void loadBooks() {
    FILE *file = fopen("books.txt", "r");
    if (!file) return; // no previous data

    bookCount = 0;

    while (fscanf(file, "%d,%[^,],%[^,],%d\n",
                  &books[bookCount].id,
                  books[bookCount].title,
                  books[bookCount].author,
                  &books[bookCount].quantity) == 4) 
    {
        bookCount++;
        if (bookCount >= MAX_BOOKS) break; // prevent overflow
    }

    fclose(file);
}

// ---------------- Save all books in memory to books.txt (write mode) ----------------
void saveBooks() {
    FILE *file = fopen("books.txt", "w");  // overwrite file
    if (!file) {
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

// ---------------- Add a new book (append mode) ----------------
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Book storage is full.\n");
        return;
    }

    struct Book b;

    printf("Enter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Title: ");
    getchar(); // consume leftover newline
    fgets(b.title, 50, stdin);
    b.title[strcspn(b.title, "\n")] = 0;

    printf("Enter Book Author: ");
    fgets(b.author, 50, stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    // Add to memory
    books[bookCount] = b;
    bookCount++;

    // Save to file in append mode
    FILE *file = fopen("books.txt", "a"); // append mode
    if (!file) {
        printf("Error saving book.\n");
        return;
    }
    fprintf(file, "%d,%s,%s,%d\n", b.id, b.title, b.author, b.quantity);
    fclose(file);

    printf("Book added successfully.\n");
}

// ---------------- Show all books ----------------
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

// ---------------- Search a book by ID ----------------
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

// ---------------- Update a book (write mode) ----------------
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

            saveBooks();  // overwrite file with updated memory
            printf("Book updated successfully.\n");
            return;
        }
    }

    printf("Book not found.\n");
}

// ---------------- Delete a book (write mode) ----------------
void deleteBook() {
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            // Shift books down to remove the deleted book
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }

            bookCount--;
            saveBooks();  // overwrite file without deleted book
            printf("Book deleted successfully.\n");
            return;
        }
    }

    printf("Book not found.\n");
}
