#include <stdio.h>
#include "student.h"
#include "university.h"
#include "book.h"
int main() {
    loadUniversities();
    loadStudents();

    int choice;

    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Student Management\n");
        printf("2. University Management\n");
        printf("3.Book Management\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int s_choice;
                while (1) {
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
                        case 0: goto main_menu; // back to main menu
                        default: printf("Invalid choice.\n");
                    }
                }
            }
            case 2: {
                int u_choice;
                while (1) {
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
                        case 0: goto main_menu; // back to main menu
                        default: printf("Invalid choice.\n");
                    }
                }
            }
            case 3: { 
        int b_choice;
        while (1) {
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
                case 0: goto main_menu;
                default: printf("Invalid choice.\n");
            }
        }
    }
            case 0: 
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
        main_menu: ;
    }
}
