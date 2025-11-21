// student.c
#include <stdio.h>
#include <string.h>
#include "student.h"

Student students[MAX_STUDENTS];
int studentCount = 0;

// ---------------------------
// Utility: Clear Input Buffer
// ---------------------------
static void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ---------------------------
// Load Students from file
// ---------------------------
void loadStudents() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) return;

    studentCount = 0;
    while (fscanf(fp, "%d %49[^\n] %49s %d %d",
                  &students[studentCount].id,
                  students[studentCount].name,
                  students[studentCount].email,
                  &students[studentCount].university_id,
                  &students[studentCount].borrow_count) == 5) {
        studentCount++;
    }
    fclose(fp);
}

// ---------------------------
// Save Students to file
// ---------------------------
void saveStudents() {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) return;

    for (int i = 0; i < studentCount; i++) {
        fprintf(fp, "%d %s %s %d %d\n",
                students[i].id,
                students[i].name,
                students[i].email,
                students[i].university_id,
                students[i].borrow_count);
    }
    fclose(fp);
}

// ---------------------------
// Generate New Unique ID
// ---------------------------
int generateNewStudentID() {
    if (studentCount == 0) return 1;
    return students[studentCount - 1].id + 1;
}

// ---------------------------
// Find student index by ID
// ---------------------------
int findStudentIndexByID(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

// ---------------------------
// Add Student
// ---------------------------
void addStudent() {
    printf("\n====================================\n");
    printf("           ADD STUDENT\n");
    printf("====================================\n");

    if (studentCount >= MAX_STUDENTS) {
        printf("❌ Student list is full.\n");
        return;
    }

    Student s;
    s.id = generateNewStudentID();

    clearInputBuffer();
    printf("Enter full name        : ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter email            : ");
    scanf("%s", s.email);

    printf("Enter University ID    : ");
    scanf("%d", &s.university_id);

    s.borrow_count = 0;

    students[studentCount++] = s;
    saveStudents();

    printf("\n✔ Student added successfully!\n");
    printf("✔ Assigned Student ID : %d\n", s.id);
    printf("====================================\n");
}

// ---------------------------
// View Students
// ---------------------------
void viewStudents() {
    printf("\n============================================================\n");
    printf("                        STUDENT LIST\n");
    printf("============================================================\n");

    if (studentCount == 0) {
        printf("No students found.\n");
        printf("============================================================\n");
        return;
    }

    printf("ID    %-20s %-25s %-8s %-8s\n",
            "Name", "Email", "UnivID", "Borrow");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        printf("%-5d %-20s %-25s %-8d %-8d\n",
               students[i].id,
               students[i].name,
               students[i].email,
               students[i].university_id,
               students[i].borrow_count);
    }

    printf("------------------------------------------------------------\n");
    printf("Total Students: %d\n", studentCount);
    printf("============================================================\n");
}

// ---------------------------
// Search Student
// ---------------------------
void searchStudent() {
    printf("\n------------------------------------\n");
    printf("           SEARCH STUDENT\n");
    printf("------------------------------------\n");

    int id;
    printf("Enter Student ID: ");
    scanf("%d", &id);

    int index = findStudentIndexByID(id);
    if (index == -1) {
        printf("❌ No student found with ID %d\n", id);
        printf("------------------------------------\n");
        return;
    }

    printf("\n✔ Student Found\n");
    printf("------------------------------------\n");
    printf("ID              : %d\n", students[index].id);
    printf("Name            : %s\n", students[index].name);
    printf("Email           : %s\n", students[index].email);
    printf("University ID   : %d\n", students[index].university_id);
    printf("Borrow Count    : %d\n", students[index].borrow_count);
    printf("------------------------------------\n");
}

// ---------------------------
// Update Student
// ---------------------------
void updateStudent() {
    printf("\n------------------------------------\n");
    printf("           UPDATE STUDENT\n");
    printf("------------------------------------\n");

    int id;
    printf("Enter Student ID: ");
    scanf("%d", &id);

    int index = findStudentIndexByID(id);
    if (index == -1) {
        printf("❌ Student not found.\n");
        return;
    }

    clearInputBuffer();

    printf("Enter new full name    : ");
    fgets(students[index].name, sizeof(students[index].name), stdin);
    students[index].name[strcspn(students[index].name, "\n")] = 0;

    printf("Enter new email        : ");
    scanf("%s", students[index].email);

    printf("Enter new University ID: ");
    scanf("%d", &students[index].university_id);

    saveStudents();

    printf("\n✔ Student updated successfully!\n");
    printf("------------------------------------\n");
}

// ---------------------------
// Delete Student
// ---------------------------
void deleteStudent() {
    printf("\n------------------------------------\n");
    printf("           DELETE STUDENT\n");
    printf("------------------------------------\n");

    int id;
    printf("Enter Student ID: ");
    scanf("%d", &id);

    int index = findStudentIndexByID(id);
    if (index == -1) {
        printf("❌ Student not found.\n");
        printf("------------------------------------\n");
        return;
    }

    for (int i = index; i < studentCount - 1; i++)
        students[i] = students[i + 1];

    studentCount--;
    saveStudents();

    printf("\n✔ Student deleted successfully!\n");
    printf("------------------------------------\n");
}
