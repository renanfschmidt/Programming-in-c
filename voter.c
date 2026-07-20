#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    char firstName[50];
    char middleInitial; 
    char lastName[70];
} NAME;

typedef struct {
    NAME name;
    char gender;
    int favoriteNumber;
    float weight;
    int timesWon;
} VOTER;

void fixSentenceCase(char *str);
void sanitizeVoter(VOTER *v);
void getWeightStatement(VOTER *v, char *dest);

int main() {
    srand(time(NULL));

    FILE *file = fopen("SRC/input.bin", "rb");
    if (!file) {
        printf("Error: Could not open\n");
        return 1;
    }

    int totalSize = 0;
    int effectiveSize = 0;

    fread(&totalSize, sizeof(int), 1, file);
    fread(&effectiveSize, sizeof(int), 1, file);
    VOTER **voters = (VOTER **)malloc(totalSize * sizeof(VOTER *));
    for (int i = 0; i < totalSize; i++) voters[i] = NULL;

    for (int i = 0; i < effectiveSize; i++) {
        voters[i] = (VOTER *)malloc(sizeof(VOTER));
        fread(voters[i], sizeof(VOTER), 1, file);
        voters[i]->timesWon = 0; 
        sanitizeVoter(voters[i]);
    }
    fclose(file);
    char keepGoing = 'Y';
    while ((keepGoing == 'y' || keepGoing == 'Y') && effectiveSize < totalSize) {
        voters[effectiveSize] = (VOTER *)malloc(sizeof(VOTER));
        VOTER *v = voters[effectiveSize];
        v->timesWon = 0;

        printf("\nEnter First Name: ");
        scanf("%49s", v->name.firstName);
        printf("Enter Middle Initial (Use '-' if none): ");
        scanf(" %c", &v->name.middleInitial);
        printf("Enter Last Name: ");
        scanf("%69s", v->name.lastName);
        printf("Enter Gender (M, F, O, U): ");
        scanf(" %c", &v->gender);
        printf("Enter Favorite Number (0-999): ");
        scanf("%d", &v->favoriteNumber);
        printf("Enter Weight: ");
        scanf("%f", &v->weight);
        sanitizeVoter(v);
        effectiveSize++;

        if (effectiveSize >= totalSize) {
            printf("\nArray is full.\n");
            break;
        }

        printf("Enter another record? (Y/N): ");
        scanf(" %c", &keepGoing);
    }
    int drawings[500];
    for (int i = 0; i < 500; i++) {
        drawings[i] = rand() % 1000;
    }
    for (int i = 0; i < effectiveSize; i++) {
        for (int j = 0; j < 500; j++) {
            if (voters[i]->favoriteNumber == drawings[j]) {
                voters[i]->timesWon++;
            }
        }
    }
    printf("\n%-25s %-6s %-12s %-11s %-8s %-15s\n", 
           "Name", "Gender", "Favorite No.", "Times Won", "Weight", "Weight Statement");
    
    for (int i = 0; i < effectiveSize; i++) {
        VOTER *v = voters[i];
        char fullName[130];
        char weightStatement[10];
        if (v->name.middleInitial != '-') {
            sprintf(fullName, "%s %c. %s", v->name.firstName, v->name.middleInitial, v->name.lastName);
        } else {
            sprintf(fullName, "%s %s", v->name.firstName, v->name.lastName);
        }

        getWeightStatement(v, weightStatement);

        printf("%-25s %-6c %-12d %-11d %-8.0f %-15s\n", 
               fullName, v->gender, v->favoriteNumber, v->timesWon, v->weight, weightStatement);
    }
    FILE *outFile = fopen("SRC/input.bin", "wb");
    if (outFile) {
        fwrite(&totalSize, sizeof(int), 1, outFile);
        fwrite(&effectiveSize, sizeof(int), 1, outFile);
        for (int i = 0; i < effectiveSize; i++) {
            fwrite(voters[i], sizeof(VOTER), 1, outFile);
        }
        fclose(outFile);
        printf("\nSuccessfully exported to SRC/input.bin.\n");
    }

    
    for (int i = 0; i < totalSize; i++) {
        if (voters[i]) free(voters[i]);
    }
    free(voters);

    return 0;
}
void fixSentenceCase(char *str) {
    if (str[0] == '\0') return;
    str[0] = toupper((unsigned char)str[0]);
    for (int i = 1; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}
void sanitizeVoter(VOTER *v) {
    fixSentenceCase(v->name.firstName);
    fixSentenceCase(v->name.lastName);
    if (v->name.middleInitial != '-') {
        v->name.middleInitial = toupper((unsigned char)v->name.middleInitial);
    }
    v->gender = toupper((unsigned char)v->gender);
    if (v->gender != 'M' && v->gender != 'F' && v->gender != 'O') {
        v->gender = 'U';
    }
}
void getWeightStatement(VOTER *v, char *dest) {
    float w = v->weight;
    char g = v->gender;
    if (g == 'M') {
        if (w < 125.0) strcpy(dest, "SKINNY");
        else if (w <= 225.0) strcpy(dest, "FIT");
        else strcpy(dest, "FAT");
    } else if (g == 'F') {
        if (w < 100.0) strcpy(dest, "SKINNY");
        else if (w <= 150.0) strcpy(dest, "FIT");
        else strcpy(dest, "FAT");
    } else {
        if (w < 115.0) strcpy(dest, "SKINNY");
        else if (w <= 200.0) strcpy(dest, "FIT");
        else strcpy(dest, "FAT");
    }
}