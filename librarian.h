#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#define MAX_LIBRARIANS 20

struct Librarian {
    int id;
    char name[50];
    char email[50];
    char phone[15];
};

// Function prototypes
void loadLibrarians();
void saveLibrarians();

void addLibrarian();
void viewLibrarians();
void searchLibrarian();
void updateLibrarian();
void deleteLibrarian();

#endif

