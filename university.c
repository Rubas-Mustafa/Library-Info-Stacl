// university.c
#include <stdio.h>
#include <string.h>
#include "university.h"

University universities[MAX_UNIVERSITIES];
int universityCount = 0;


// Clear input buffer
static void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// Load Universities from file
void loadUniversities() {
    FILE *fp = fopen("universities.txt", "r");
    if (!fp) return;

    universityCount = 0;

    while (fscanf(fp, "%d, %[^0-9] %f", 
                  &universities[universityCount].id, 
                  universities[universityCount].name, 
                  &universities[universityCount].discount) == 3) {

        // Trim trailing spaces
        universities[universityCount].name[strcspn(universities[universityCount].name, " ")] = '\0';

        universityCount++;
    }

    fclose(fp);
}


// Save Universities to file
void saveUniversities() {
    FILE *fp = fopen("universities.txt", "w");
    if (!fp) return;

    for (int i = 0; i < universityCount; i++) {
        fprintf(fp, "%d, %s ", 
                universities[i].id,
                universities[i].name);

        fprintf(fp, "%.2f\n", universities[i].discount);
    }

    fclose(fp);
}



// Generate New University ID

int generateNewUniversityID() {
    if (universityCount == 0) return 1;
    return universities[universityCount - 1].id + 1;
}


// Find University index by ID

int findUniversityIndexByID(int id) {
    for (int i = 0; i < universityCount; i++) {
        if (universities[i].id == id)
            return i;
    }
    return -1;
}


// Add University
void addUniversity() {
    printf("\n====================================\n");
    printf("           ADD UNIVERSITY\n");
    printf("====================================\n");

    if (universityCount >= MAX_UNIVERSITIES) {
        printf("❌ University list is full.\n");
        return;
    }

    University u;
    u.id = generateNewUniversityID();

    clearInputBuffer();
    printf("Enter university name : ");
    fgets(u.name, sizeof(u.name), stdin);
    u.name[strcspn(u.name, "\n")] = 0;

    printf("Enter discount (%%)    : ");
    scanf("%f", &u.discount);

    universities[universityCount++] = u;
    saveUniversities();

    printf("\n✔ University added successfully!\n");
    printf("✔ Assigned University ID : %d\n", u.id);
    printf("====================================\n");
}


// View Universities
void viewUniversities() {
    printf("\n============================================================\n");
    printf("                     UNIVERSITY LIST\n");
    printf("============================================================\n");

    if (universityCount == 0) {
        printf("No universities found.\n");
        printf("============================================================\n");
        return;
    }

    printf("ID    %-25s %-10s\n", "Name", "Discount(%)");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < universityCount; i++) {
        printf("%-5d %-25s %-10.2f\n",
               universities[i].id,
               universities[i].name,
               universities[i].discount);
    }

    printf("------------------------------------------------------------\n");
    printf("Total Universities: %d\n", universityCount);
    printf("============================================================\n");
}


// Search University
void searchUniversity() {
    printf("\n------------------------------------\n");
    printf("          SEARCH UNIVERSITY\n");
    printf("------------------------------------\n");

    int id;
    printf("Enter University ID: ");
    scanf("%d", &id);

    int index = findUniversityIndexByID(id);
    if (index == -1) {
        printf("❌ No university found with ID %d\n", id);
        printf("------------------------------------\n");
        return;
    }

    printf("\n✔ University Found\n");
    printf("------------------------------------\n");
    printf("ID       : %d\n", universities[index].id);
    printf("Name     : %s\n", universities[index].name);
    printf("Discount : %.2f%%\n", universities[index].discount);
    printf("------------------------------------\n");
}


// Update University

void updateUniversity() {
    printf("\n------------------------------------\n");
    printf("         UPDATE UNIVERSITY\n");
    printf("------------------------------------\n");

    int id;
    printf("Enter University ID: ");
    scanf("%d", &id);

    int index = findUniversityIndexByID(id);
    if (index == -1) {
        printf("❌ University not found.\n");
        return;
    }

    clearInputBuffer();
    printf("Enter new name       : ");
    fgets(universities[index].name, sizeof(universities[index].name), stdin);
    universities[index].name[strcspn(universities[index].name, "\n")] = 0;

    printf("Enter new discount(%%): ");
    scanf("%f", &universities[index].discount);

    saveUniversities();

    printf("\n✔ University updated successfully!\n");
    printf("------------------------------------\n");
}


// Delete University

void deleteUniversity() {
    printf("\n------------------------------------\n");
    printf("         DELETE UNIVERSITY\n");
    printf("------------------------------------\n");

    int id;
    printf("Enter University ID: ");
    scanf("%d", &id);

    int index = findUniversityIndexByID(id);
    if (index == -1) {
        printf("❌ University not found.\n");
        printf("------------------------------------\n");
        return;
    }

    for (int i = index; i < universityCount - 1; i++)
        universities[i] = universities[i + 1];

    universityCount--;
    saveUniversities();

    printf("\n✔ University deleted successfully!\n");
    printf("------------------------------------\n");
}


// Get University Discount

float getUniversityDiscount(int university_id) {
    int index = findUniversityIndexByID(university_id);
    if (index == -1) return 0.0;
    return universities[index].discount;
}


// Update Discount Policy (for admin)

void updateDiscountPolicy() {
    printf("\n------------------------------------\n");
    printf("       UPDATE DISCOUNT POLICY\n");
    printf("------------------------------------\n");

    int id;
    printf("Enter University ID: ");
    scanf("%d", &id);

    int index = findUniversityIndexByID(id);
    if (index == -1) {
        printf("❌ University not found.\n");
        return;
    }

    printf("Current discount for %s: %.2f%%\n", universities[index].name, universities[index].discount);
    printf("Enter new discount(%%): ");
    scanf("%f", &universities[index].discount);

    saveUniversities();

    printf("\n✔ Discount updated successfully!\n");
    printf("------------------------------------\n");
}
