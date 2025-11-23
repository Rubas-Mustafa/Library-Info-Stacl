#ifndef BORROW_H
#define BORROW_H

#define MAX_BORROW 50
#define DATE_SIZE 15

typedef struct {
    int borrowID;
    int studentID;
    int bookID;
    char borrowDate[DATE_SIZE];
    char returnDate[DATE_SIZE];
    int isReturned;
} BorrowRecord;

extern BorrowRecord borrowRecords[MAX_BORROW];
extern int borrowCount;

void loadBorrowRecords();
void saveBorrowRecords();

void borrowBook();
void returnBook();
void updateBorrowRecord();
void removeBorrowRecord();
void viewBorrowRecords();
#endif
