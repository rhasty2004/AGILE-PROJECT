#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "classes.h"

#define MAX_PROFILES 50

typedef struct {
    char name[50];
    char major[30];
    char availability[20][20];
    int availCount;
    int enrolled[NUM_COURSES];  // store chosen course numbers
    int enrolledCount;
} Profile;

Profile allProfiles[MAX_PROFILES];
int profileCount = 0;
Profile userProfile = {"", "", {0}, 0};

int searchByCourse() {
    if (profileCount == 0) {
        printf("No profiles exist yet.\n");
        return 0;
    }

    int courseNum;
    printf("\nEnter course number to search (1-%d): ", NUM_COURSES);
    scanf("%d", &courseNum);

    printf("\nProfiles enrolled in %s (%s) Section %s:\n",
           courses[courseNum-1].course,
           courses[courseNum-1].title,
           courses[courseNum-1].section);

    int found = 0;
    for (int i = 0; i < profileCount; i++) {
        for (int j = 0; j < allProfiles[i].enrolledCount; j++) {
            if (allProfiles[i].enrolled[j] == courseNum) {
                printf(" - %s (%s)\n", allProfiles[i].name, allProfiles[i].major);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("No classmates found in this course.\n");
    }

    return 1;
}

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
        allProfiles[profileCount++] = userProfile;
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
    saveProfilesToCSV();
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
    saveProfilesToCSV();
}

void saveProfileToCSV() {
    FILE *fp = fopen("userdata.csv", "w");
    if (!fp) {
        printf("Error opening userdata.csv for writing!\n");
        return;
    }
    fprintf(fp, "Name,Major,Courses,Availability\n");
    if (strlen(userProfile.name) > 0) {
        // name, major
        fprintf(fp, "%s,%s,", userProfile.name, userProfile.major);
        // courses
        for (int j = 0; j < userProfile.enrolledCount; j++) {
            fprintf(fp, "%s", courses[userProfile.enrolled[j] - 1].course);
            if (j < userProfile.enrolledCount - 1) {
                fprintf(fp, "|");  // separate multiple courses
            }
        }
        fprintf(fp, ",");
        // availability
        for (int j = 0; j < userProfile.availCount; j++) {
            fprintf(fp, "%s", userProfile.availability[j]);
            if (j < userProfile.availCount - 1) {
                fprintf(fp, "|");  // separate multiple slots
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}


void loadProfileFromCSV() {
    FILE *fp = fopen("userdata.csv", "r");
    if (!fp) return;  // no saved profile yet
    char line[512];
    fgets(line, sizeof(line), fp); // skip header

    if (fgets(line, sizeof(line), fp)) {
        char *token = strtok(line, ",");
        if (token) strcpy(userProfile.name, token);
        token = strtok(NULL, ",");
        if (token) strcpy(userProfile.major, token);
        token = strtok(NULL, ",");
        userProfile.enrolledCount = 0;
        if (token) {
            char *courseToken = strtok(token, "|");
            while (courseToken) {
                for (int i = 0; i < NUM_COURSES; i++) {
                    if (strcmp(courseToken, courses[i].course) == 0) {
                        userProfile.enrolled[userProfile.enrolledCount++] = courses[i].num;
                        break;
                    }
                }
                courseToken = strtok(NULL, "|");
            }
        }
        token = strtok(NULL, ",");
        userProfile.availCount = 0;
        if (token) {
            char *availToken = strtok(token, "|");
            while (availToken && userProfile.availCount < 20) {
                // strip newline
                size_t len = strlen(availToken);
                if (len > 0 && availToken[len - 1] == '\n') {
                    availToken[len - 1] = '\0';
                }
                strcpy(userProfile.availability[userProfile.availCount++], availToken);
                availToken = strtok(NULL, "|");
            }
        }
    }
    fclose(fp);
}


void manageAvailability() {
    if (strlen(userProfile.name) == 0) {
        printf("No profile exists. Please create one first.\n");
        return;
    }

    int choice;
    while (1) {
        printf("\n=== Manage Availability for %s ===\n", userProfile.name);
        printf("1. View Availability\n");
        printf("2. Add Availability Slot\n");
        printf("3. Remove Availability Slot\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (userProfile.availCount == 0) {
                printf("No availability set.\n");
            } else {
                printf("Your availability:\n");
                for (int i = 0; i < userProfile.availCount; i++) {
                    printf("%d. %s\n", i+1, userProfile.availability[i]);
                }
            }
        }
        else if (choice == 2) {
            if (userProfile.availCount >= 20) {
                printf("Maximum availability slots reached.\n");
                continue;
            }
            printf("Enter availability (e.g., MWF 10:00-11:00): ");
            getchar(); // clear newline
            fgets(userProfile.availability[userProfile.availCount], sizeof(userProfile.availability[userProfile.availCount]), stdin);

            // remove newline from fgets
            size_t len = strlen(userProfile.availability[userProfile.availCount]);
            if (len > 0 && userProfile.availability[userProfile.availCount][len-1] == '\n')
                userProfile.availability[userProfile.availCount][len-1] = '\0';

            userProfile.availCount++;
            printf("Availability added!\n");
        }
        else if (choice == 3) {
            if (userProfile.availCount == 0) {
                printf("No availability to remove.\n");
                continue;
            }
            printf("Enter the number of the slot to remove: ");
            int removeIndex;
            scanf("%d", &removeIndex);
            if (removeIndex < 1 || removeIndex > userProfile.availCount) {
                printf("Invalid slot number.\n");
            } else {
                for (int i = removeIndex-1; i < userProfile.availCount-1; i++) {
                    strcpy(userProfile.availability[i], userProfile.availability[i+1]);
                }
                userProfile.availCount--;
                printf("Availability removed.\n");
            }
        }
        else if (choice == 4) {
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    saveProfileToCSV(); // keep it consistent with CSV storage
}