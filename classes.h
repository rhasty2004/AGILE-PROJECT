#ifndef CLASSES_H
#define CLASSES_H

#define NUM_COURSES 16

typedef struct {
    int num;            // unique ID number for the course
    char course[10];    // course code
    char title[50];     // course title
    char section[5];    // section number
    char days[5];       // days of week
    char time[20];      // meeting time
} Course;

extern Course courses[NUM_COURSES];

#endif // CLASSES_H
