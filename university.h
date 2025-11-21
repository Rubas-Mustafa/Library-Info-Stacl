// university.h
#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#define MAX_UNIVERSITIES 50

typedef struct {
    int id;
    char name[50];
    float discount; // in percentage, e.g., 10 for 10%
} University;

// Function prototypes
void loadUniversities();
void saveUniversities();

int generateNewUniversityID();
int findUniversityIndexByID(int id);

void addUniversity();
void viewUniversities();
void searchUniversity();
void updateUniversity();
void deleteUniversity();

float getUniversityDiscount(int university_id);
void updateDiscountPolicy();

#endif
