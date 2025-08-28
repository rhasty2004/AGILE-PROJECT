#include <stdio.h>

#define NUM_COURSES 16

typedef struct {
    int num;            // unique ID number for the course
    char course[10];    // course code
    char title[50];     // course title
    char section[5];    // section number
    char days[5];       // days of week
    char time[20];      // meeting time
} Course;

int main() {
    Course courses[NUM_COURSES] = {
        {1,  "CPSC 2120", "Data Structures", "001", "MWF", "10:10–11:00 AM"},
        {2,  "CPSC 2120", "Data Structures", "002", "TR",  "1:30–2:45 PM"},
        {3,  "CPSC 3600", "Networks", "001", "MWF", "11:15–12:05 PM"},
        {4,  "CPSC 3600", "Networks", "002", "TR",  "9:30–10:45 AM"},
        {5,  "CPSC 2311", "Intro to Comp Systems", "001", "MWF", "9:05–9:55 AM"},
        {6,  "CPSC 2311", "Intro to Comp Systems", "002", "TR",  "11:00–12:15 PM"},
        {7,  "MATH 2080", "Linear Algebra", "001", "MWF", "1:25–2:15 PM"},
        {8,  "MATH 2080", "Linear Algebra", "002", "TR",  "12:30–1:45 PM"},
        {9,  "MATH 2060", "Calculus III", "001", "MWF", "8:00–8:50 AM"},
        {10, "MATH 2060", "Calculus III", "002", "TR",  "2:00–3:15 PM"},
        {11, "ECE 2010",  "Logic & Computing Devices", "001", "MWF", "12:20–1:10 PM"},
        {12, "ECE 2010",  "Logic & Computing Devices", "002", "TR",  "3:30–4:45 PM"},
        {13, "ENGL 1030", "Composition & Rhetoric", "001", "MWF", "10:10–11:00 AM"},
        {14, "ENGL 1030", "Composition & Rhetoric", "002", "TR",  "8:00–9:15 AM"},
        {15, "PHYS 1220", "Physics w/ Calculus I", "001", "MWF", "2:30–3:20 PM"},
        {16, "PHYS 1220", "Physics w/ Calculus I", "002", "TR",  "5:00–6:15 PM"}
    };

    // Example: print all courses
    for (int i = 0; i < NUM_COURSES; i++) {
        printf("%d. %s (%s) - Section %s, %s %s\n",
               courses[i].num,
               courses[i].course,
               courses[i].title,
               courses[i].section,
               courses[i].days,
               courses[i].time);
    }

    return 0;
}
