#include <stdio.h>
#include <string.h>

#define MAX_PROFILES 100
#define MAX_COURSES 10
#define MAX_COURSE_LEN 50

typedef struct {
    char name[100];
    char courses[MAX_COURSES][MAX_COURSE_LEN];
    int numCourses;
} Profile;

Profile profiles[MAX_PROFILES];
int profileCount = 0;

// Create a new profile
void createProfile() {
    if (profileCount >= MAX_PROFILES) {
        printf("Profile limit reached.\n");
        return;
    }

    Profile p;
    printf("Enter your name: ");
    scanf(" %[^\n]", p.name);

    printf("How many courses are you enrolled in (max %d)? ", MAX_COURSES);
    scanf("%d", &p.numCourses);

    if (p.numCourses > MAX_COURSES) p.numCourses = MAX_COURSES;

    for (int i = 0; i < p.numCourses; i++) {
        printf("Enter course %d: ", i + 1);
        scanf(" %s", p.courses[i]);
    }

    profiles[profileCount++] = p;
    printf("Profile created successfully!\n");
}

// Display all profiles
void viewProfiles() {
    if (profileCount == 0) {
        printf("No profiles available.\n");
        return;
    }

    for (int i = 0; i < profileCount; i++) {
        printf("\nProfile %d:\n", i + 1);
        printf("Name: %s\n", profiles[i].name);
        printf("Courses: ");
        for (int j = 0; j < profiles[i].numCourses; j++) {
            printf("%s ", profiles[i].courses[j]);
        }
        printf("\n");
    }
}

// Search for classmates by course
void searchByCourse() {
    char searchCourse[MAX_COURSE_LEN];
    int found = 0;

    printf("Enter course to search: ");
    scanf(" %s", searchCourse);

    for (int i = 0; i < profileCount; i++) {
        for (int j = 0; j < profiles[i].numCourses; j++) {
            if (strcmp(profiles[i].courses[j], searchCourse) == 0) {
                printf("Match found: %s\n", profiles[i].name);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("No students found for course %s\n", searchCourse);
    }
}

// Add stubs for new features
void manageAvailability() {
    
}

void createSession() {
    
}

void confirmSession() {
    
}