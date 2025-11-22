#include <stdio.h>
#include <string.h>
#include "librarian.h"

struct Librarian librarians[MAX_LIBRARIANS];
int librarianCount = 0;

// ---------------- Load librarians from file ----------------
void loadLibrarians() {
    FILE *file = fopen("librarians.txt", "r");
    if (!file) return;

    librarianCount = 0;
    while (fscanf(file, "%d,%[^,],%[^,],%[^\n]\n",
                  &librarians[librarianCount].id,
                  librarians[librarianCount].name,
                  librarians[librarianCount].email,
                  librarians[librarianCount].phone) == 4)
    {
        librarianCount++;
        if (librarianCount >= MAX_LIBRARIANS) break;
    }
    fclose(file);
}

// ---------------- Save all librarians to file ----------------
void saveLibrarians() {
    FILE *file = fopen("librarians.txt", "w");
    if (!file) {
        printf("Error saving librarians.\n");
        return;
    }
    for (int i = 0; i < librarianCount; i++) {
        fprintf(file, "%d,%s,%s,%s\n",
                librarians[i].id,
                librarians[i].name,
                librarians[i].email,
                librarians[i].phone);
    }
    fclose(file);
}

// ---------------- Add a new librarian ----------------
void addLibrarian() {
    if (librarianCount >= MAX_LIBRARIANS) {
        printf("Librarian storage full.\n");
        return;
    }

    struct Librarian l;
    printf("Enter Librarian ID: ");
    scanf("%d", &l.id);

    printf("Enter Name: ");
    getchar();
    fgets(l.name, 50, stdin);
    l.name[strcspn(l.name, "\n")] = 0;

    printf("Enter Email: ");
    fgets(l.email, 50, stdin);
    l.email[strcspn(l.email, "\n")] = 0;

    printf("Enter Phone: ");
    fgets(l.phone, 15, stdin);
    l.phone[strcspn(l.phone, "\n")] = 0;

    librarians[librarianCount] = l;
    librarianCount++;

    // Save new librarian in append mode
    FILE *file = fopen("librarians.txt", "a");
    if (!file) {
        printf("Error saving librarian.\n");
        return;
    }
    fprintf(file, "%d,%s,%s,%s\n", l.id, l.name, l.email, l.phone);
    fclose(file);

    printf("Librarian added successfully.\n");
}

// ---------------- View all librarians ----------------
void viewLibrarians() {
    if (librarianCount == 0) {
        printf("No librarians available.\n");
        return;
    }

    printf("\n--- LIBRARIAN LIST ---\n");
    for (int i = 0; i < librarianCount; i++) {
        printf("ID: %d | Name: %s | Email: %s | Phone: %s\n",
               librarians[i].id,
               librarians[i].name,
               librarians[i].email,
               librarians[i].phone);
    }
}

// ---------------- Search librarian by ID ----------------
void searchLibrarian() {
    int id;
    printf("Enter Librarian ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < librarianCount; i++) {
        if (librarians[i].id == id) {
            printf("Librarian Found!\n");
            printf("ID: %d\nName: %s\nEmail: %s\nPhone: %s\n",
                   librarians[i].id,
                   librarians[i].name,
                   librarians[i].email,
                   librarians[i].phone);
            return;
        }
    }
    printf("Librarian not found.\n");
}

// ---------------- Update librarian by ID ----------------
void updateLibrarian() {
    int id;
    printf("Enter Librarian ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < librarianCount; i++) {
        if (librarians[i].id == id) {
            printf("Updating Librarian ID %d\n", id);

            printf("Enter new Name: ");
            getchar();
            fgets(librarians[i].name, 50, stdin);
            librarians[i].name[strcspn(librarians[i].name, "\n")] = 0;

            printf("Enter new Email: ");
            fgets(librarians[i].email, 50, stdin);
            librarians[i].email[strcspn(librarians[i].email, "\n")] = 0;

            printf("Enter new Phone: ");
            fgets(librarians[i].phone, 15, stdin);
            librarians[i].phone[strcspn(librarians[i].phone, "\n")] = 0;

            saveLibrarians(); // overwrite file
            printf("Librarian updated successfully.\n");
            return;
        }
    }
    printf("Librarian not found.\n");
}

// ---------------- Delete librarian by ID ----------------
void deleteLibrarian() {
    int id;
    printf("Enter Librarian ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < librarianCount; i++) {
        if (librarians[i].id == id) {
            for (int j = i; j < librarianCount - 1; j++) {
                librarians[j] = librarians[j + 1];
            }
            librarianCount--;
            saveLibrarians(); // overwrite file
            printf("Librarian deleted successfully.\n");
            return;
        }
    }
    printf("Librarian not found.\n");
}

