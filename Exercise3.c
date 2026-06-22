#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct {
    int month;
    int day;
    int year;
} DATE;

typedef struct {
    char name[100];
    DATE birthdate;
    char gender;
    double annualIncome;
} PERSON;
int isValidDate(int m, int d, int y);
void toSentenceCase(char *str);
void populatePerson(PERSON *p);
void printPerson(PERSON p);
int main() {
    PERSON p1, p2, p3;

    printf("Enter Details for Person 1\n");
    populatePerson(&p1);

    printf("\nEnter Details for Person 2\n");
    populatePerson(&p2);
    printf("\nEnter Details for Person 3 \n");
    populatePerson(&p3);
    printPerson(p1);
    printPerson(p2);
    printPerson(p3);

    return 0;
}
int isValidDate(int m, int d, int y) {
    if (y < 1900 || y > 2026) return 0;
    if (m < 1 || m > 12) return 0;

    int daysInMonth = 31;
    switch(m) {
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
        case 2:
            if (y % 4 == 0) {
                daysInMonth = 29;
            } else {
                daysInMonth = 28;
            }
            break;
        default:
            daysInMonth = 31;
    }
    if (d < 1 || d > daysInMonth) {
        return 0;
    }

    return 1;
}

void toSentenceCase(char *str) {
    if (str[0] == '\0') return;
    str[0] = toupper(str[0]);
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i - 1] == ' ') {
            str[i] = toupper(str[i]);
        } else {
            str[i] = tolower(str[i]);
        }
    }
}

void populatePerson(PERSON *p) {
    printf("Enter Name: ");
    fgets(p->name, sizeof(p->name), stdin);
    p->name[strcspn(p->name, "\n")] = '\0'; 
    toSentenceCase(p->name);
    do {
        printf("Enter Birthdate (MM DD YYYY): ");
        scanf("%d %d %d", &p->birthdate.month, &p->birthdate.day, &p->birthdate.year);
        
        if (!isValidDate(p->birthdate.month, p->birthdate.day, p->birthdate.year)) {
            printf("Invalid\n");
        }
    } while (!isValidDate(p->birthdate.month, p->birthdate.day, p->birthdate.year));
    do {
        printf("Gender (M, F, O): ");
        scanf(" %c", &p->gender);
        if (p->gender != 'M' && p->gender != 'F' && p->gender != 'O') {
            printf("Invalid\n");
        }
    } while (p->gender != 'M' && p->gender != 'F' && p->gender != 'O');
    do {
        printf("Enter Annual Income(0 to 1,000,000): ");
        scanf("%lf", &p->annualIncome);
        if (p->annualIncome < 0 || p->annualIncome > 1000000) {
            printf("Invalid\n");
        }
    } while (p->annualIncome < 0 || p->annualIncome > 1000000);
    while (getchar() != '\n');
}
void printPerson(PERSON p) {
    printf("\nName:          %s", p.name);
    printf("\nBirthdate:     %02d/%02d/%04d", p.birthdate.month, p.birthdate.day, p.birthdate.year);
    printf("\nGender:        %c", p.gender);
    printf("\nAnnual Income: $%.2f", p.annualIncome);
    
}