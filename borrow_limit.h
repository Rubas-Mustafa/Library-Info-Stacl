#ifndef BORROW_LIMIT_H
#define BORROW_LIMIT_H
#define MAX_BORROW_LIMIT 3
#define FINE_PER_7_DAYS 20

int getBorrowCount(int studentID);
int checkBorrowLimit(int studentID);
int hasReachedBorrowLimit(int studentID);
int getTotalBorrowedBooks();
int validateBorrowing(int studentID);

int calculateLateDays(char borrowDate[], char returnDate[]);
float calculateFineAmount(int lateDays);

#endif
