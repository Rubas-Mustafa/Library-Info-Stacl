#ifndef BOOK_H
#define BOOK_H

#define MAX_BOOKS 100
#define TITLE_SIZE 100
#define AUTHOR_SIZE 50

typedef struct {
    int id;
    char title[TITLE_SIZE];
    char author[AUTHOR_SIZE];
    int available;
} Book;

extern Book books[MAX_BOOKS];
extern int bookCount;

// Function declarations
void loadBooks();
void saveBooks();

void addBook();
void viewBooks();
void searchBook();
void updateBook();
void deleteBook();

int generateNewBookID();
int findBookIndexByID(int id);

#endif
