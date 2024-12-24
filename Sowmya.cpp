#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_VACCINE_NAME 50

typedef struct {
    char name[50];
    int validity; // in days
} Vaccine;

char name[50];
char *c;
int i, validity = -1; // in days
char vaccineName[MAX_VACCINE_NAME];
char manufactureDate[10]; // DD/MM/YYYY
int expiryDate;
time_t expirationtime;
char formattedExpiryDate[20];

Vaccine vaccines[] = {
    {"adult pfizer", 70},
    {"moderna", 30},
    {"novavax", 365},
    {"influenza", 152},
    {"hepatitis b", 1095},
    {"human papillomavirus", 1095},
    {"tdap", 730},
    {"polio", 730}
};

void welcome() {
    printf("\n Welcome to vaccine management system");
    printf("\n *********************************************");
    printf("\n press any key to continue");
    getchar();
}

void input(){
    printf("Vaccine Tracker\n");
    printf("Vaccine Name: ");
    scanf("%s", vaccineName);
    printf("Manufacture Date (DD/MM/YYYY): ");
    scanf("%s", manufactureDate);
}

void calculation() {
    for (c = vaccineName; *c; c++) {
        *c = tolower(*c);
    }

    // Search for matching vaccine
    for (i = 0; i < sizeof(vaccines) / sizeof(vaccines[0]); i++) {
        if (strcmp(vaccineName, vaccines[i].name) == 0) {
            validity = vaccines[i].validity;
            break;
        }
    }

    if (validity != -1) {
        // Calculate expiration date
        struct tm manufactureTm = {0};
        sscanf(manufactureDate, "%d/%d/%d", &manufactureTm.tm_mday, &manufactureTm.tm_mon, &manufactureTm.tm_year);
        manufactureTm.tm_mon--; // Month is 0-based
        manufactureTm.tm_year -= 1900; // Convert to years since 1900
        time_t manufactureTime = mktime(&manufactureTm);
        expirationtime = manufactureTime + (validity * 24 * 60 * 60);
        // Format expiration date
        struct tm *expirationTm = localtime(&expirationtime);
        strftime(formattedExpiryDate, sizeof(formattedExpiryDate), "%d/%m/%Y", expirationTm);
    }
}

void output() {
    printf("\nVaccine Name: %s\n", vaccineName);
    printf("Manufacture Date: %s\n", manufactureDate);
    printf("Expiry Date: %s\n", formattedExpiryDate);
    time_t currentTime = time(NULL);
    if (currentTime < expirationtime) {
        printf("Vaccine Status: Valid to use\n");
    } else {
        printf("Vaccine Status: Expired\n");
    }
}

int main() {
    welcome();
    input();
    calculation();
    output();
    return 0;
}
