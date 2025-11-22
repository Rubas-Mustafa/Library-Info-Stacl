#include <stdio.h>
#include <string.h>
#include "borrow.h"
#include "student.h"
#include "book.h"
#include "borrow_limit.h"
BorrowRecord borrowRecords[MAX_BORROW];
int borrowCount = 0;

// ---------------------------
// Load borrow records
void loadBorrowRecords() {
    FILE *fp = fopen("borrow.txt", "r");
    if (!fp) return;

    borrowCount = 0;
    while (!feof(fp)) {
        BorrowRecord b;
        int ret = fscanf(fp, "%d, %d, %d, %[^,], %[^,], %d\n",
                         &b.borrowID,
                         &b.studentID,
                         &b.bookID,
                         b.borrowDate,
                         b.returnDate,
                         &b.isReturned);
        if (ret != 6) break;

        borrowRecords[borrowCount++] = b;
    }

    fclose(fp);
}

// ---------------------------
// Save borrow records
// ---------------------------
void saveBorrowRecords() {
    FILE *fp = fopen("borrow.txt", "w");  // overwrite with all records
    if (!fp) return;

    for (int i = 0; i < borrowCount; i++) {
        fprintf(fp, "%d, %d, %d, %s, %s, %d\n",
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
// Borrow a book
// ---------------------------
void borrowBook() {
    int studentID, bookID;

    printf("Enter Student ID: ");
    scanf("%d", &studentID);

    int studentIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == studentID) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    if (students[studentIndex].borrow_count >= 3) {
        printf("Student has reached the borrow limit (3 books).\n");
        return;
    }

    printf("Enter Book ID to borrow: ");
    scanf("%d", &bookID);

    int bookIndex = -1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == bookID) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
        printf("Book not found.\n");
        return;
    }

    if (books[bookIndex].available == 0) {
        printf("Book is currently borrowed.\n");
        return;
    }

    BorrowRecord b;
    b.borrowID = borrowCount + 1;
    b.studentID = studentID;
    b.bookID = bookID;

    printf("Enter Borrow Date (dd-mm-yyyy): ");
    scanf("%s", b.borrowDate);

    strcpy(b.returnDate, "-");
    b.isReturned = 0;

    borrowRecords[borrowCount++] = b;

    books[bookIndex].available = 0;
    students[studentIndex].borrow_count++;

    saveBorrowRecords();
    saveBooks();
    saveStudents();

    printf("Book borrowed successfully!\n");
}

// ---------------------------
// Return a book
// ---------------------------
void returnBook() {
    int borrowID;
    printf("Enter Borrow ID: ");
    scanf("%d", &borrowID);

    int index = -1;
    for (int i = 0; i < borrowCount; i++) {
        if (borrowRecords[i].borrowID == borrowID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Borrow record not found.\n");
        return;
    }

    if (borrowRecords[index].isReturned == 1) {
        printf("Book is already returned.\n");
        return;
    }

    printf("Enter Return Date (dd-mm-yyyy): ");
    scanf("%s", borrowRecords[index].returnDate);

    borrowRecords[index].isReturned = 1;

    int studentIndex = -1, bookIndex = -1;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == borrowRecords[index].studentID) {
            studentIndex = i;
            break;
        }
    }

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == borrowRecords[index].bookID) {
            bookIndex = i;
            break;
        }
    }

    if (studentIndex != -1 && students[studentIndex].borrow_count > 0)
        students[studentIndex].borrow_count--;

    if (bookIndex != -1)
        books[bookIndex].available = 1;

    saveBorrowRecords();
    saveBooks();
    saveStudents();

    printf("Book returned successfully!\n");
    int lateDays = calculateLateDays(borrowRecords[index].borrowDate, borrowRecords[index].returnDate);
float fine = calculateFineAmount(lateDays);
if (fine > 0) {
    printf("Book returned late by %d days. Fine: Rs %.2f\n", lateDays, fine);
}

}

// ---------------------------
// Update borrow record
// ---------------------------
void updateBorrowRecord() {
    int borrowID;
    printf("Enter Borrow ID to update: ");
    scanf("%d", &borrowID);

    int index = -1;
    for (int i = 0; i < borrowCount; i++) {
        if (borrowRecords[i].borrowID == borrowID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Borrow record not found.\n");
        return;
    }

    printf("Enter new Return Date: ");
    scanf("%s", borrowRecords[index].returnDate);

    saveBorrowRecords();
    printf("Borrow record updated successfully!\n");
}
void viewBorrowRecords() {
    printf("\n============================================================\n");
    printf("                      BORROW RECORDS\n");
    printf("============================================================\n");
    if (borrowCount == 0) {
        printf("No borrow records found.\n");
        printf("============================================================\n");
        return;
    }

    printf("ID   StudentID  BookID  BorrowDate   ReturnDate  Returned\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < borrowCount; i++) {
        printf("%-4d %-10d %-7d %-12s %-12s %-8d\n",
               borrowRecords[i].borrowID,
               borrowRecords[i].studentID,
               borrowRecords[i].bookID,
               borrowRecords[i].borrowDate,
               borrowRecords[i].returnDate,
               borrowRecords[i].isReturned);
    }
    printf("------------------------------------------------------------\n");
    printf("Total Borrow Records: %d\n", borrowCount);
    printf("============================================================\n");
}

// ---------------------------
// Remove borrow record
// ---------------------------
void removeBorrowRecord() {
    int borrowID;
    printf("Enter Borrow ID to delete: ");
    scanf("%d", &borrowID);

    int index = -1;
    for (int i = 0; i < borrowCount; i++) {
        if (borrowRecords[i].borrowID == borrowID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Borrow record not found.\n");
        return;
    }

    int studentIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == borrowRecords[index].studentID) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex != -1 && borrowRecords[index].isReturned == 0)
        students[studentIndex].borrow_count--;

    for (int i = index; i < borrowCount - 1; i++)
        borrowRecords[i] = borrowRecords[i + 1];

    borrowCount--;

    saveBorrowRecords();
    saveStudents();

    printf("Borrow record deleted successfully.\n");
}
