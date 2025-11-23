#include <stdio.h>
#include <string.h>
#include "book.h"

Book books[MAX_BOOKS];
int bookCount = 0;

// Load books from file
void loadBooks() {
    FILE *fp = fopen("books.txt", "r");
    if (!fp) return;

    bookCount = 0;
    while (!feof(fp)) {
        Book b;
        int ret = fscanf(fp, "%d, %[^,], %[^,], %d\n",
                         &b.id,
                         b.title,
                         b.author,
                         &b.available);
        if (ret != 4) break;

        b.title[strcspn(b.title, "\n")] = 0;
        b.author[strcspn(b.author, "\n")] = 0;

        books[bookCount++] = b;
    }
    fclose(fp);
}


// Save books to file
void saveBooks() {
    FILE *fp = fopen("books.txt", "w");
    if (!fp) return;

    for (int i = 0; i < bookCount; i++) {
        fprintf(fp, "%d, %s, %s, %d\n",
                books[i].id,
                books[i].title,
                books[i].author,
                books[i].available);
    }

    fclose(fp);
}


// Generate new unique ID
int generateNewBookID() {
    if (bookCount == 0) return 1;
    return books[bookCount - 1].id + 1;
}

// Find book index by ID
int findBookIndexByID(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id)
            return i;
    }
    return -1;
}

// Add book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Book list is full.\n");
        return;
    }

    Book b;
    b.id = generateNewBookID();

    printf("Enter book title: ");
    getchar();
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = 0;

    printf("Enter author name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    b.available = 1;

    books[bookCount++] = b;

    FILE *fp = fopen("books.txt", "a");
    if (fp) {
        fprintf(fp, "%d, %s, %s, %d\n",
                b.id, b.title, b.author, b.available);
        fclose(fp);
    }

    printf("Book added successfully! ID: %d\n", b.id);
}


// View books
void viewBooks() {
    printf("\n====================================\n");
    printf("             BOOK LIST\n");
    printf("====================================\n");

    if (bookCount == 0) {
        printf("No books found.\n");
        return;
    }

    printf("ID    %-30s %-30s %-10s\n", "Title", "Author", "Available");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < bookCount; i++) {
        printf("%-5d %-30s %-30s %-10d\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].available);
    }
}

// Search book
void searchBook() {
    int id;
    printf("Enter Book ID: ");
    scanf("%d", &id);

    int index = findBookIndexByID(id);
    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    printf("ID: %d\nTitle: %s\nAuthor: %s\nAvailable: %d\n",
           books[index].id,
           books[index].title,
           books[index].author,
           books[index].available);
}

// Update book
void updateBook() {
    int id;
    printf("Enter Book ID to update: ");
    scanf("%d", &id);

    int index = findBookIndexByID(id);
    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    getchar();
    printf("Enter new title: ");
    fgets(books[index].title, sizeof(books[index].title), stdin);
    books[index].title[strcspn(books[index].title, "\n")] = 0;

    printf("Enter new author: ");
    fgets(books[index].author, sizeof(books[index].author), stdin);
    books[index].author[strcspn(books[index].author, "\n")] = 0;

    saveBooks();
    printf("Book updated successfully.\n");
}

// Delete book
void deleteBook() {
    int id;
    printf("Enter Book ID to delete: ");
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
