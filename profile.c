#include <stdio.h>
#include <string.h>
#include "helper.h"

#define MAX_PROFILES 100
#define MAX_COURSES 10
#define MAX_COURSE_LEN 20
#define MAX_AVAIL 10
#define MAX_SESSIONS 100



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
int pfpCount = 0;
int sessionCount = 0;


// Display all profiles
void viewProfiles() {
    if (pfpCount == 0) {
        printf("No profiles available.\n");
        return;
    }

    for (int i = 0; i < pfpCount; i++) {
        printf("\nProfile %d:\n", i + 1);
        printf("Name: %s\n", profiles[i].name);
        printf("Courses: ");
        for (int j = 0; j < profiles[i].numCourses; j++) {
            printf("%s ", profiles[i].courses[j]);
        }
        printf("\n");
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
    for (int i = 0; i < pfpCount - 1; i++) {
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