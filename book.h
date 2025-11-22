#ifndef BOOK_H
#define BOOK_H

struct Book {
    int id;
    char title[50];
    char author[50];
    int available; // 1 = available, 0 = borrowed
    int quantity;
};

void addBook();
void viewBooks();
void searchBook();
void updateBook();
void deleteBook();
int isBookAvailable(int bookID);

#endif

