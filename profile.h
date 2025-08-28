#ifndef PROFILE_H
#define PROFILE_H

#define MAX_COURSES 10
#define MAX_NAME_LEN 50
#define MAX_COURSE_LEN 20
#define MAX_PROFILES 100

typedef struct {
    char name[MAX_NAME_LEN];
    int numCourses;
    char courses[MAX_COURSES][MAX_COURSE_LEN];
} Profile;

extern Profile profiles[MAX_PROFILES];
extern int profileCount;

// Function declarations
void createProfile();
void viewProfiles();
void searchByCourse();
void runTests();

#endif