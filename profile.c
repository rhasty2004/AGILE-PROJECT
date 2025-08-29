#include <stdio.h>
#include <string.h>

#define MAX_PROFILES 100
#define MAX_COURSES 10
#define MAX_COURSE_LEN 50
#define MAX_AVAIL 10
#define MAX_SESSIONS 100

typedef struct {
    char name[100];
    char courses[MAX_COURSES][MAX_COURSE_LEN];
    int numCourses;
} Profile;

typedef struct {
    char times[MAX_AVAIL][30];
    int availCount;
} Availability;

typedef struct {
    int profileIdx1;
    int profileIdx2;
    char course[MAX_COURSE_LEN];
    char time[30];
    int confirmed; // 0 = pending, 1 = confirmed
} Session;

Profile profiles[MAX_PROFILES];
Availability availabilities[MAX_PROFILES];
Session sessions[MAX_SESSIONS];
int profileCount = 0;
int sessionCount = 0;

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

// Add or remove availability for the current user (last profile)
void manageAvailability() {
    if (profileCount == 0) {
        printf("No profile found. Create a profile first.\n");
        return;
    }
    int idx = profileCount - 1;
    int choice;
    printf("Manage Availability for %s\n", profiles[idx].name);
    printf("1. Add availability\n2. Remove availability\n3. View availability\n");
    scanf("%d", &choice);

    if (choice == 1) {
        if (availabilities[idx].availCount >= MAX_AVAIL) {
            printf("Maximum availability slots reached.\n");
            return;
        }
        printf("Enter available time (e.g., MWF 10:00AM): ");
        scanf(" %[^\n]", availabilities[idx].times[availabilities[idx].availCount]);
        availabilities[idx].availCount++;
        printf("Availability added.\n");
    } else if (choice == 2) {
        printf("Enter slot number to remove (1-%d): ", availabilities[idx].availCount);
        int slot;
        scanf("%d", &slot);
        if (slot < 1 || slot > availabilities[idx].availCount) {
            printf("Invalid slot.\n");
            return;
        }
        for (int i = slot - 1; i < availabilities[idx].availCount - 1; i++) {
            strcpy(availabilities[idx].times[i], availabilities[idx].times[i+1]);
        }
        availabilities[idx].availCount--;
        printf("Availability removed.\n");
    } else if (choice == 3) {
        printf("Your availability:\n");
        for (int i = 0; i < availabilities[idx].availCount; i++) {
            printf("%d. %s\n", i+1, availabilities[idx].times[i]);
        }
    } else {
        printf("Invalid choice.\n");
    }
}

// Suggest matches for study sessions
void createSession() {
    if (profileCount == 0) {
        printf("No profiles available.\n");
        return;
    }
    int idx = profileCount - 1;
    printf("Enter course to find study buddies: ");
    char course[MAX_COURSE_LEN];
    scanf(" %s", course);

    printf("Enter preferred time slot: ");
    char time[30];
    scanf(" %[^\n]", time);

    int found = 0;
    for (int i = 0; i < profileCount - 1; i++) {
        // Check if course matches and time overlaps
        for (int j = 0; j < profiles[i].numCourses; j++) {
            if (strcmp(profiles[i].courses[j], course) == 0) {
                for (int k = 0; k < availabilities[i].availCount; k++) {
                    if (strcmp(availabilities[i].times[k], time) == 0) {
                        printf("Suggested match: %s\n", profiles[i].name);
                        // Schedule session
                        if (sessionCount < MAX_SESSIONS) {
                            Session s = {idx, i, "", "", 0};
                            strcpy(s.course, course);
                            strcpy(s.time, time);
                            sessions[sessionCount++] = s;
                            printf("Session scheduled with %s (pending confirmation).\n", profiles[i].name);
                        }
                        found = 1;
                    }
                }
            }
        }
    }
    if (!found) {
        printf("No matches found for course and time.\n");
    }
}

// Confirm or cancel meetings
void confirmSession() {
    if (sessionCount == 0) {
        printf("No sessions scheduled.\n");
        return;
    }
    printf("Scheduled sessions:\n");
    for (int i = 0; i < sessionCount; i++) {
        printf("%d. %s & %s, Course: %s, Time: %s, Status: %s\n",
            i+1,
            profiles[sessions[i].profileIdx1].name,
            profiles[sessions[i].profileIdx2].name,
            sessions[i].course,
            sessions[i].time,
            sessions[i].confirmed ? "Confirmed" : "Pending");
    }
    printf("Enter session number to confirm/cancel: ");
    int num;
    scanf("%d", &num);
    if (num < 1 || num > sessionCount) {
        printf("Invalid session.\n");
        return;
    }
    printf("1. Confirm\n2. Cancel\n");
    int action;
    scanf("%d", &action);
    if (action == 1) {
        sessions[num-1].confirmed = 1;
        printf("Session confirmed.\n");
    } else if (action == 2) {
        // Remove session
        for (int i = num-1; i < sessionCount-1; i++) {
            sessions[i] = sessions[i+1];
        }
        sessionCount--;
        printf("Session cancelled.\n");
    } else {
        printf("Invalid action.\n");
    }
}