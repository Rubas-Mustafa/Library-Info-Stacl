#include <stdio.h>
#include <string.h>
#include "borrow.h"
#include "book.h"

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
    int bookID;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &bookID);

    // Find the book
    int index = -1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == bookID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    if (books[index].available == 0) {
        printf("Book is currently borrowed.\n");
        return;
    }

    struct BorrowRecord b;
    b.borrowID = borrowCount + 1;

    printf("Enter Student ID: ");
    scanf("%d", &b.studentID);

    b.bookID = bookID;

    printf("Enter Borrow Date (dd-mm-yyyy): ");
    scanf("%s", b.borrowDate);

    strcpy(b.returnDate, "-"); // No return yet
    b.isReturned = 0;

    borrowRecords[borrowCount] = b;
    borrowCount++;

    books[index].available = 0; // mark book borrowed

    saveBorrowRecords();
    saveBooks();

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

            // Mark book available
            for (int j = 0; j < bookCount; j++) {
                if (books[j].id == borrowRecords[i].bookID) {
                    books[j].available = 1;
                    break;
                }
            }

            saveBorrowRecords();
            saveBooks();

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

            for (int j = i; j < borrowCount - 1; j++) {
                borrowRecords[j] = borrowRecords[j + 1];
            }

            borrowCount--;
            saveBorrowRecords();

            printf("Borrow record deleted.\n");
            return;
        }
    }

    printf("Borrow record not found.\n");
}

