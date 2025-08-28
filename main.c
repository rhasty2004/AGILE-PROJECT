#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "profile.h"
int main() {
    int choice;
    while (1) {
        printf("\n=== Clemson Study Buddy App ===\n");
        printf("1. Create/Edit Profile\n");
        printf("2. Search Classmates by Course\n");
        printf("3. Manage Availability\n");
        printf("4. Schedule Study Session\n");
        printf("5. Confirm/Cancel Session\n");
        printf("6. Exit\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createProfile(); break;
            case 2: searchByCourse(); break;
            case 3: manageAvailability(); break;
            case 4: createSession(); break;
            case 5: confirmSession(); break;
            case 6: return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
