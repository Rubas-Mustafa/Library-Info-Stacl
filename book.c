#include <stdio.h>
#include <string.h>
#include "borrow.h"
#include "book.h"
#include "student.h"

#define MAX_BORROW 50

struct BorrowRecord borrowRecords[MAX_BORROW];
int borrowCount = 0;

// ---------------------------
// Load Borrow Records
// ---------------------------
void loadBorrowRecords() {
    FILE *fp = fopen("borrow.txt", "r");
    if (!fp) return;

    borrowCount = 0;
    while (fscanf(fp, "%d %d %d %s %s %d",
                  &borrowRecords[borrowCount].borrowID,
                  &borrowRecords[borrowCount].studentID,
                  &borrowRecords[borrowCount].bookID,
                  borrowRecords[borrowCount].borrowDate,
                  borrowRecords[borrowCount].returnDate,
                  &borrowRecords[borrowCount].isReturned) == 6)
    {
        borrowCount++;
    }

    fclose(fp);
}

// ---------------------------
// Save Borrow Records
// ---------------------------
void saveBorrowRecords() {
    FILE *fp = fopen("borrow.txt", "w");
    if (!fp) {
        printf("Error saving borrow records.\n");
        return;
    }

    for (int i = 0; i < borrowCount; i++) {
        fprintf(fp, "%d %d %d %s %s %d\n",
                borrowRecords[i].borrowID,
                borrowRecords[i].studentID,
                borrowRecords[i].bookID,
                borrowRecords[i].borrowDate,
                borrowRecords[i].returnDate,
                borrowRecords[i].isReturned);
    }

    fclose(fp);
}

// ---------------------------
// Borrow a Book
// ---------------------------
void borrowBook() {
    printf("\n====================================\n");
    printf("           BORROW BOOK\n");
    printf("====================================\n");

    int studentID;
    printf("Enter Student ID: ");
    scanf("%d", &studentID);

    int studentIndex = findStudentIndexByID(studentID);
    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    if (students[studentIndex].borrow_count >= 3) {
        printf("Student has reached the borrow limit (3 books).\n");
        return;
    }

    int bookID;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &bookID);

    int bookIndex = findBookIndexByID(bookID);
    if (bookIndex == -1) {
        printf("Book not found.\n");
        return;
    }

    if (books[bookIndex].available == 0) {
        printf("Book is currently borrowed.\n");
        return;
    }

    struct BorrowRecord b;
    b.borrowID = borrowCount + 1;
    b.studentID = studentID;
    b.bookID = bookID;

    printf("Enter Borrow Date (dd-mm-yyyy): ");
    scanf("%s", b.borrowDate);

    strcpy(b.returnDate, "-");
    b.isReturned = 0;

    borrowRecords[borrowCount] = b;
    borrowCount++;

    books[bookIndex].available = 0;
    students[studentIndex].borrow_count++;

    saveBorrowRecords();
    saveBooks();
    saveStudents();

    printf("Book borrowed successfully.\n");
}

// ---------------------------
// Return a Book
// ---------------------------
void returnBook() {
    printf("\n====================================\n");
    printf("           RETURN BOOK\n");
    printf("====================================\n");

    int borrowID;
    printf("Enter Borrow ID: ");
    scanf("%d", &borrowID);

    for (int i = 0; i < borrowCount; i++) {
        if (borrowRecords[i].borrowID == borrowID) {

            if (borrowRecords[i].isReturned == 1) {
                printf("Book is already returned.\n");
                return;
            }

            printf("Enter Return Date (dd-mm-yyyy): ");
            scanf("%s", borrowRecords[i].returnDate);

            borrowRecords[i].isReturned = 1;

            int bookIndex = findBookIndexByID(borrowRecords[i].bookID);
            int studentIndex = findStudentIndexByID(borrowRecords[i].studentID);

            if (bookIndex != -1) books[bookIndex].available = 1;
            if (studentIndex != -1 && students[studentIndex].borrow_count > 0)
                students[studentIndex].borrow_count--;

            saveBorrowRecords();
            saveBooks();
            saveStudents();

            printf("Book returned successfully.\n");
            return;
        }
    }

    printf("Borrow record not found.\n");
}

// ---------------------------
// Update Borrow Record
// ---------------------------
void updateBorrowRecord() {
    printf("\n====================================\n");
    printf("        UPDATE BORROW RECORD\n");
    printf("====================================\n");

    int borrowID;
    printf("Enter Borrow ID to update: ");
    scanf("%d", &borrowID);

    for (int i = 0; i < borrowCount; i++) {
        if (borrowRecords[i].borrowID == borrowID) {
            printf("Enter new return date: ");
            scanf("%s", borrowRecords[i].returnDate);

            saveBorrowRecords();
            printf("Borrow record updated successfully.\n");
            return;
        }
    }

    printf("Borrow record not found.\n");
}

// ---------------------------
// Remove Borrow Record
// ---------------------------
void removeBorrowRecord() {
    printf("\n====================================\n");
    printf("        DELETE BORROW RECORD\n");
    printf("====================================\n");

    int borrowID;
    printf("Enter Borrow ID to delete: ");
    scanf("%d", &borrowID);

    for (int i = 0; i < borrowCount; i++) {
        if (borrowRecords[i].borrowID == borrowID) {

            int studentIndex = findStudentIndexByID(borrowRecords[i].studentID);
            if (studentIndex != -1 && borrowRecords[i].isReturned == 0) {
                if (students[studentIndex].borrow_count > 0)
                    students[studentIndex].borrow_count--;
            }

            for (int j = i; j < borrowCount - 1; j++)
                borrowRecords[j] = borrowRecords[j + 1];

            borrowCount--;

            saveBorrowRecords();
            saveStudents();

            printf("Borrow record deleted successfully.\n");
            return;
        }
    }

    printf("Borrow record not found.\n");
}
