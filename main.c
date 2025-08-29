#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "profile.h"
#include "helper.h"
#include "classes.h"

int main() {
    int choice;
    printf("Welcome to the Clemson Study Buddy App!\n");
    printf("select an option by entering the respective number:\n");
    while (1) {
        printf("1. Create/Edit Profile\n");
        printf("2. Delete Profile\n");  
        printf("3. Search Classmates by Course\n");
        printf("4. Manage Availability\n");
        printf("5. Schedule Study Session\n");
        printf("6. Confirm/Cancel Session\n");
        printf("7. Exit\n");

        switch(choice) {
            case 1: createProfile(); break;
            case 2: deleteProfile(); break;   
            case 3: searchByCourse(); break;
            case 4: manageAvailability(); break;
            case 5: createSession(); break;
            case 6: confirmSession(); break;
            case 7: return 0;
            default: printf("Invalid choice.\n");
}
    }
}
