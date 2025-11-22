#include <stdio.h>
#include <string.h>
#include "student.h"
#include "borrow.h"
#include "book.h"

#define MAX_BORROW_LIMIT 3
#define FINE_PER_7_DAYS 20

// ---------------------------
// Get number of books currently borrowed by a student
// ---------------------------
int getBorrowCount(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == studentID) {
            return students[i].borrow_count;
        }
    }
    return 0; // student not found or none borrowed
}

// ---------------------------
// Check if student can borrow (returns 1 if yes, 0 if limit reached)
// ---------------------------
int checkBorrowLimit(int studentID) {
    int count = getBorrowCount(studentID);
    return count < MAX_BORROW_LIMIT;
}

// ---------------------------
// Check if student has reached the borrow limit (1=yes, 0=no)
// ---------------------------
int hasReachedBorrowLimit(int studentID) {
    return !checkBorrowLimit(studentID);
}

// ---------------------------
// Total books borrowed system-wide
// ---------------------------
int getTotalBorrowedBooks() {
    int total = 0;
    for (int i = 0; i < studentCount; i++) {
        total += students[i].borrow_count;
    }
    return total;
}

// ---------------------------
// Validate borrowing before allowing
// ---------------------------
int validateBorrowing(int studentID) {
    if (hasReachedBorrowLimit(studentID)) {
        printf("Student ID %d has reached the borrow limit (%d books).\n", studentID, MAX_BORROW_LIMIT);
        return 0; // cannot borrow
    }
    return 1; // allowed to borrow
}

// ---------------------------
// Fine calculation based on return date
// ---------------------------
// date format: "dd-mm-yyyy"
int calculateLateDays(char borrowDate[], char returnDate[]) {
    int bd, bm, by, rd, rm, ry;
    sscanf(borrowDate, "%d-%d-%d", &bd, &bm, &by);
    sscanf(returnDate, "%d-%d-%d", &rd, &rm, &ry);

    int daysBorrowed = (ry - by) * 365 + (rm - bm) * 30 + (rd - bd); // simple approximation
    if (daysBorrowed > 7)
        return daysBorrowed - 7;
    return 0;
}

float calculateFineAmount(int lateDays) {
    if (lateDays <= 0)
        return 0;
    return FINE_PER_7_DAYS; // flat 20 Rs for >7 days
}
