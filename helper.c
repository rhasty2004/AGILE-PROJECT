#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classes.h"

typedef struct {
    char name[50];
    char major[30];
    int enrolled[NUM_COURSES];  // store chosen course numbers
    int enrolledCount;
} Profile;

Profile userProfile = {"", "", {0}, 0};

/*int searchByCourse() {
    printf("Searching by course...\n");



    
    return 0;
}*/

void createProfile() {
    int choice;
    printf("Would you like to create a profile or edit your existing one?\n");
    printf("Enter 1 to create, or 2 to edit.\n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter a name for your profile.\n");
        scanf("%s", userProfile.name);
        printf("Enter the name of your major.\n");
        scanf("%s", userProfile.major);
        for (int i = 0; i < 16; i++) {
        printf("%d. %s (%s) - Section %s, %s %s\n",
               courses[i].num,
               courses[i].course,
               courses[i].title,
               courses[i].section,
               courses[i].days,
               courses[i].time);
        }
        printf("\nEnter course numbers to enroll (separated by spaces, 0 to stop): ");
        userProfile.enrolledCount = 0;
        int courseNum;
        while (1) {
            scanf("%d", &courseNum);
            if (courseNum == 0) break;
            userProfile.enrolled[userProfile.enrolledCount++] = courseNum;
        }

        printf("\nProfile created:\nName: %s\nMajor: %s\nEnrolled Courses:\n",
               userProfile.name, userProfile.major);
        for (int i = 0; i < userProfile.enrolledCount; i++) {
            int idx = userProfile.enrolled[i] - 1;
            printf("  - %s (%s) Section %s\n",
                   courses[idx].course,
                   courses[idx].title,
                   courses[idx].section);
        }
    } else if (choice == 2) {
        // ===== Edit Existing Profile =====
        if (strlen(userProfile.name) == 0) {
            printf("No existing profile. Please create one first.\n");
            return;
        }

        int editChoice;
        printf("\nEditing Profile for %s (%s)\n", userProfile.name, userProfile.major);
        printf("1. Edit Name\n");
        printf("2. Edit Major\n");
        printf("3. Edit Enrolled Courses\n");
        printf("Enter your choice: ");
        scanf("%d", &editChoice);

        if (editChoice == 1) {
            printf("Enter new name: ");
            scanf("%s", userProfile.name);
            printf("Name updated!\n");
        }
        else if (editChoice == 2) {
            printf("Enter new major: ");
            scanf("%s", userProfile.major);
            printf("Major updated!\n");
        }
        else if (editChoice == 3) {
            printf("\nAvailable Courses:\n");
            for (int i = 0; i < NUM_COURSES; i++) {
                printf("%d. %s (%s) - Section %s, %s %s\n",
                       courses[i].num,
                       courses[i].course,
                       courses[i].title,
                       courses[i].section,
                       courses[i].days,
                       courses[i].time);
            }

            printf("\nRe-enter your courses (0 to stop): ");
            userProfile.enrolledCount = 0;
            int courseNum;
            while (1) {
                scanf("%d", &courseNum);
                if (courseNum == 0) break;
                userProfile.enrolled[userProfile.enrolledCount++] = courseNum;
            }
            printf("Courses updated!\n");
        }
        else {
            printf("Invalid choice.\n");
        }
        printf("\nProfile Summary:\n");
        printf("Name: %s\nMajor: %s\nEnrolled Courses:\n", userProfile.name, userProfile.major);
        for (int i = 0; i < userProfile.enrolledCount; i++) {
            int idx = userProfile.enrolled[i] - 1;
            printf("  - %s (%s) Section %s\n",
                courses[idx].course,
                courses[idx].title,
                courses[idx].section);
        }
    }
}

void deleteProfile() {
    if (strlen(userProfile.name) == 0) {
        printf("No profile exists to delete.\n");
        return;
    }

    // Clear out profile data
    userProfile.name[0] = '\0';
    userProfile.major[0] = '\0';
    userProfile.enrolledCount = 0;

    printf("Profile deleted successfully.\n");
}