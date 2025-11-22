#include <stdio.h>
#include <string.h>
#include "book.h"

#define MAX_BOOKS 100

Book books[MAX_BOOKS];
int bookCount = 0;

// ---------------------------
// Load Books from file
// ---------------------------
void loadBooks() {
    FILE *fp = fopen("books.txt", "r");
    if (!fp) return;

    bookCount = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        Book b;
        sscanf(line, "%d, %[^,], %[^,], %d",
               &b.id,
               b.title,
               b.author,
               &b.available);

        books[bookCount++] = b;
    }

    fclose(fp);
}

// ---------------------------
// Save Books to file
// ---------------------------
void saveBooks() {
    FILE *fp = fopen("books.txt", "w");
    if (!fp) {
        printf("Error saving books.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(fp, "%d, %s, %s, %d\n",
                books[i].id,
                books[i].title,
                books[i].author,
                books[i].available);
    }

    fclose(fp);
}

// ---------------------------
// Generate New Book ID
// ---------------------------
int generateNewBookID() {
    if (bookCount == 0) return 1;
    return books[bookCount - 1].id + 1;
}

// ---------------------------
// Find Book Index by ID
// ---------------------------
int findBookIndexByID(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id)
            return i;
    }
    return -1;
}

// ---------------------------
// Add Book
// ---------------------------
void addBook() {
    printf("\n====================================\n");
    printf("           ADD BOOK\n");
    printf("====================================\n");

    if (bookCount >= MAX_BOOKS) {
        printf("Book list is full.\n");
        return;
    }

    Book b;
    b.id = generateNewBookID();

    getchar(); // clear input buffer
    printf("Enter book title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = 0;

    printf("Enter author name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    b.available = 1;

    books[bookCount++] = b;
    saveBooks();

    printf("Book added successfully.\n");
    printf("Assigned Book ID: %d\n", b.id);
    printf("====================================\n");
}

// ---------------------------
// View Books
// ---------------------------
void viewBooks() {
    printf("\n============================================================\n");
    printf("                        BOOK LIST\n");
    printf("============================================================\n");

    if (bookCount == 0) {
        printf("No books found.\n");
        printf("============================================================\n");
        return;
    }

    printf("ID    %-30s %-30s %-10s\n", "Title", "Author", "Available");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < bookCount; i++) {
        printf("%-5d %-30s %-30s %-10s\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].available ? "Yes" : "No");
    }

    printf("------------------------------------------------------------\n");
    printf("Total Books: %d\n", bookCount);
    printf("============================================================\n");
}

// ---------------------------
// Update Book
// ---------------------------
void updateBook() {
    printf("\n====================================\n");
    printf("           UPDATE BOOK\n");
    printf("====================================\n");

    int id;
    printf("Enter Book ID: ");
    scanf("%d", &id);

    int index = findBookIndexByID(id);
    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    getchar(); // clear input buffer
    printf("Enter new title: ");
    fgets(books[index].title, sizeof(books[index].title), stdin);
    books[index].title[strcspn(books[index].title, "\n")] = 0;

    printf("Enter new author: ");
    fgets(books[index].author, sizeof(books[index].author), stdin);
    books[index].author[strcspn(books[index].author, "\n")] = 0;

    saveBooks();
    printf("Book updated successfully.\n");
}

// ---------------------------
// Delete Book
// ---------------------------
void deleteBook() {
    printf("\n====================================\n");
    printf("           DELETE BOOK\n");
    printf("====================================\n");

    int id;
    printf("Enter Book ID: ");
    scanf("%d", &id);

    int index = findBookIndexByID(id);
    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    for (int i = index; i < bookCount - 1; i++)
        books[i] = books[i + 1];

    bookCount--;
    saveBooks();

    printf("Book deleted successfully.\n");
}
