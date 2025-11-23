#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100

typedef struct {
    int id;
    char name[50];
    char email[50];
    int university_id;
    int borrow_count;
} Student;

extern Student students[MAX_STUDENTS];
extern int studentCount;

void loadStudents();
void saveStudents();

void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int generateNewStudentID();
int findStudentIndexByID(int id);

#endif
