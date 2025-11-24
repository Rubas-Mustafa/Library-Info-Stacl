#include <stdio.h>
#include "student.h"
#include "university.h"
#include "book.h"
#include "borrow.h"
#include "librarian.h"

int main() {
    loadStudents();
    loadUniversities();
    loadBooks();  
    loadBorrowRecords(); 
    loadLibrarians();
    int choice;

    while (1) {
                            printf("----------------------------------\n");

        printf("\n=== MAIN MENU ===\n");
        printf("1. Student Management\n");
        printf("2. University Management\n");
        printf("3. Book Management\n");
        printf("4. Librarian Management\n");
        printf("5. Borrow / Return Management\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int s_choice;
                do {
                    printf("----------------------------------\n");
                    printf("\n--- STUDENT MENU ---\n");
                    printf("1. Add Student\n");
                    printf("2. View Students\n");
                    printf("3. Search Student\n");
                    printf("4. Update Student\n");
                    printf("5. Delete Student\n");
                    printf("0. Back to Main Menu\n");
                    printf("Enter choice: ");
                    scanf("%d", &s_choice);

                    switch (s_choice) {
                        case 1: addStudent(); break;
                        case 2: viewStudents(); break;
                        case 3: searchStudent(); break;
                        case 4: updateStudent(); break;
                        case 5: deleteStudent(); break;
                        case 0: break;
                        default: printf("Invalid choice.\n");
                    }
                } while (s_choice != 0);
                break;
            }

            case 2: {
                int u_choice;
                do {
                    printf("----------------------------------\n");

                    printf("\n--- UNIVERSITY MENU ---\n");
                    printf("1. Add University\n");
                    printf("2. View Universities\n");
                    printf("3. Search University\n");
                    printf("4. Update University\n");
                    printf("5. Delete University\n");
                    printf("6. Update Discount Policy\n");
                    printf("0. Back to Main Menu\n");
                    printf("Enter choice: ");
                    scanf("%d", &u_choice);

                    switch (u_choice) {
                        case 1: addUniversity(); break;
                        case 2: viewUniversities(); break;
                        case 3: searchUniversity(); break;
                        case 4: updateUniversity(); break;
                        case 5: deleteUniversity(); break;
                        case 6: updateDiscountPolicy(); break;
                        case 0: break;
                        default: printf("Invalid choice.\n");
                    }
                } while (u_choice != 0);
                break;
            }

            case 3: {
                int b_choice;
                do {
                    printf("----------------------------------\n");

                    printf("\n--- BOOK MENU ---\n");
                    printf("1. Add Book\n");
                    printf("2. View Books\n");
                    printf("3. Search Book\n");
                    printf("4. Update Book\n");
                    printf("5. Delete Book\n");
                    printf("0. Back to Main Menu\n");
                    printf("Enter choice: ");
                    scanf("%d", &b_choice);

                    switch (b_choice) {
                        case 1: addBook(); break;
                        case 2: viewBooks(); break;
                        case 3: searchBook(); break;
                        case 4: updateBook(); break;
                        case 5: deleteBook(); break;
                        case 0: break;
                        default: printf("Invalid choice.\n");
                    }
                } while (b_choice != 0);
                break;
            }

            case 4: {
                int l_choice;
                do {
                    printf("----------------------------------\n");

                    printf("\n--- LIBRARIAN MENU ---\n");
                    printf("1. Add Librarian\n");
                    printf("2. View Librarians\n");
                    printf("3. Search Librarian\n");
                    printf("4. Update Librarian\n");
                    printf("5. Delete Librarian\n");
                    printf("0. Back to Main Menu\n");
                    printf("Enter choice: ");
                    scanf("%d", &l_choice);

                    switch (l_choice) {
                        case 1: addLibrarian(); break;
                        case 2: viewLibrarians(); break;
                        case 3: searchLibrarian(); break;
                        case 4: updateLibrarian(); break;
                        case 5: deleteLibrarian(); break;
                        case 0: break;
                        default: printf("Invalid choice.\n");
                    }
                } while (l_choice != 0);
                break;
            }

            case 5: {
                int br_choice;
                do {
                    printf("----------------------------------\n");

                    printf("\n--- BORROW / RETURN MENU ---\n");
                    printf("1. Borrow Book\n");
                    printf("2. Return Book\n");
                    printf("3. Update Borrow Record\n");
                    printf("4. Remove Borrow Record\n");
                    printf("5. View BookRecords\n");
                    printf("0. Back to Main Menu\n");
                    printf("Enter choice: ");
                    scanf("%d", &br_choice);

                    switch (br_choice) {
                        case 1: borrowBook(); break;
                        case 2: returnBook(); break;
                        case 3: updateBorrowRecord(); break;
                        case 4: removeBorrowRecord(); break;
                        case 5: viewBorrowRecords(); break;
                        case 0: break;
                        default: printf("Invalid choice.\n");
                    }
                } while (br_choice != 0);
                break;
            }

            case 0:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
