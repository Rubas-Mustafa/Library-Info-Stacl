#ifndef BORROW_H
#define BORROW_H

struct BorrowRecord {
    int borrowID;
    int studentID;
    int bookID;
    char borrowDate[20];
    char returnDate[20];
    int isReturned; // 0 = not returned, 1 = returned
};

extern struct BorrowRecord borrowRecords[];
extern int borrowCount;

void loadBorrowRecords();
void saveBorrowRecords();

void borrowBook();
void returnBook();
void updateBorrowRecord();
void removeBorrowRecord();

#endif

