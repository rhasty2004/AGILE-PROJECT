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

int searchByCourse() {
    printf("Searching by course...\n");



    
    return 0;
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
    }
}