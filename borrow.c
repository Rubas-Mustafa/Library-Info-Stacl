#include <stdio.h>
#include <string.h>
#include "borrow.h"
#include "book.h"
#include "student.h"

#define MAX_BORROW 50

struct BorrowRecord borrowRecords[MAX_BORROW];
int borrowCount = 0;

// Load borrow records from file
void loadBorrowRecords() {
    FILE *file = fopen("borrow.txt", "r");
    if (!file) return;

    borrowCount = 0;

    while (fscanf(file, "%d %d %d %s %s %d",
                  &borrowRecords[borrowCount].borrowID,
                  &borrowRecords[borrowCount].studentID,
                  &borrowRecords[borrowCount].bookID,
                  borrowRecords[borrowCount].borrowDate,
                  borrowRecords[borrowCount].returnDate,
                  &borrowRecords[borrowCount].isReturned) == 6)
    {
        borrowCount++;
    }

    fclose(file);
}

// Save borrow records to file
void saveBorrowRecords() {
    FILE *file = fopen("borrow.txt", "w");
    if (!file) {
        printf("Error saving borrow records.\n");
        return;
    }

    for (int i = 0; i < borrowCount; i++) {
        fprintf(file, "%d %d %d %s %s %d\n",
                borrowRecords[i].borrowID,
                borrowRecords[i].studentID,
                borrowRecords[i].bookID,
                borrowRecords[i].borrowDate,
                borrowRecords[i].returnDate,
                borrowRecords[i].isReturned);
    }

    fclose(file);
}

// Borrow a book
void borrowBook() {
    int bookID, studentID;

    printf("Enter Student ID: ");
    scanf("%d", &studentID);

    // Find student index
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

    // Check borrow limit
    if (students[studentIndex].borrowedCount >= 3) {
        printf("Student has reached the borrow limit (3 books).\n");
        return;
    }

    printf("Enter Book ID to borrow: ");
    scanf("%d", &bookID);

    // Find book index
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

    // Create borrow record
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

    // Update book availability and student borrowed count
    books[bookIndex].available = 0;
    students[studentIndex].borrowedCount++;

    // Save changes
    saveBorrowRecords();
    saveBooks();
    saveStudents();

    printf("Book borrowed successfully!\n");
}

// Return a book
void returnBook() {
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

            // Find book and student to update
            int bookIndex = -1, studentIndex = -1;

            for (int j = 0; j < bookCount; j++) {
                if (books[j].id == borrowRecords[i].bookID) {
                    bookIndex = j;
                    break;
                }
            }

            for (int j = 0; j < studentCount; j++) {
                if (students[j].id == borrowRecords[i].studentID) {
                    studentIndex = j;
                    break;
                }
            }

            if (bookIndex != -1) books[bookIndex].available = 1;
            if (studentIndex != -1 && students[studentIndex].borrowedCount > 0)
                students[studentIndex].borrowedCount--;

            // Save all changes
            saveBorrowRecords();
            saveBooks();
            saveStudents();

            printf("Book returned successfully!\n");
            return;
        }
    }

    printf("Borrow record not found.\n");
}

// Update borrow record
void updateBorrowRecord() {
    int borrowID;
    printf("Enter Borrow ID to update: ");
    scanf("%d", &borrowID);

    for (int i = 0; i < borrowCount; i++) {
        if (borrowRecords[i].borrowID == borrowID) {
            printf("Enter new return date: ");
            scanf("%s", borrowRecords[i].returnDate);

            saveBorrowRecords();
            printf("Borrow record updated!\n");
            return;
        }
    }

    printf("Borrow record not found.\n");
}

// Remove borrow record
void removeBorrowRecord() {
    int borrowID;
    printf("Enter Borrow ID to delete: ");
    scanf("%d", &borrowID);

    for (int i = 0; i < borrowCount; i++) {
        if (borrowRecords[i].borrowID == borrowID) {

            // Find student to decrement borrow count if not yet returned
            int studentIndex = -1;
            for (int j = 0; j < studentCount; j++) {
                if (students[j].id == borrowRecords[i].studentID) {
                    studentIndex = j;
                    break;
                }
            }

            if (studentIndex != -1 && borrowRecords[i].isReturned == 0) {
                if (students[studentIndex].borrowedCount > 0)
                    students[studentIndex].borrowedCount--;
            }

            // Shift records to delete
            for (int j = i; j < borrowCount - 1; j++) {
                borrowRecords[j] = borrowRecords[j + 1];
            }

            borrowCount--;

            saveBorrowRecords();
            saveStudents();

            printf("Borrow record deleted.\n");
            return;
        }
    }

    printf("Borrow record not found.\n");
}
