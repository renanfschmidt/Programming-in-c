#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#pragma pack(push, 1)
typedef struct {
    char firstName[50];
    char middleInitial;
    char lastName[70];
} NAME;
#pragma pack(pop)

typedef struct {
    NAME name;
    char gender;
    int favoriteNumber;
    float weight;
    int timesWon;
} VOTER;
void readLine(char *buffer,size_t size) {
    if (fgets(buffer,size,stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

void capitalizeString(char *str) {
    if (str != NULL && strlen(str) > 0) {
        str[0] = toupper((unsigned char)str[0]);
        for (int i = 1; str[i] != '\0'; i++) {
            str[i] = tolower((unsigned char)str[i]);
        }
    }
}

void formatName(NAME *n) {
    capitalizeString(n->firstName);
    capitalizeString(n->lastName);
    if (n->middleInitial != '\0' && n->middleInitial != ' ') {
        n->middleInitial = toupper((unsigned char)n->middleInitial);
    }
}

void validateGender(char *gender) {
    *gender = toupper((unsigned char)*gender);
    if (*gender != 'M' && *gender != 'F' && *gender != 'O') {
        *gender = 'U';
    }
}

void getWeightCategory(char gender, float weight, char *categoryStr) {
    if (gender == 'M') {
        if (weight < 125.0f) strcpy(categoryStr,"SKINNY");
        else if (weight <= 225.0f) strcpy(categoryStr, "FIT");
        else strcpy(categoryStr,"FAT");
    } else if (gender == 'F') {
        if (weight < 100.0f) strcpy(categoryStr,"SKINNY");
        else if (weight <= 150.0f) strcpy(categoryStr, "FIT");
        else strcpy(categoryStr,"FAT");
    } else {
        if (weight < 115.0f) strcpy(categoryStr, "SKINNY");
        else if (weight <= 200.0f) strcpy(categoryStr, "FIT");
        else strcpy(categoryStr,"FAT");
    }
}

int main(void) {
    srand((unsigned int)time(NULL));
    const char *filePath = "SRC/input.bin";
    FILE *file = fopen(filePath,"rb");
    if (!file) {
        filePath = "input.bin";
        file = fopen(filePath, "rb");
    }
    
    int totalCapacity = 0;
    int effectiveSize = 0;
    VOTER **voters = NULL;

    if (file != NULL) {
        fread(&totalCapacity, sizeof(int), 1,file);
        fread(&effectiveSize, sizeof(int), 1,file);

        if (totalCapacity > 0) {
            voters = (VOTER **)malloc(sizeof(VOTER *) * totalCapacity);
            for (int i = 0; i < effectiveSize; i++) {
                voters[i] = (VOTER *)malloc(sizeof(VOTER));
                fread(&voters[i]->name, sizeof(NAME), 1, file);
                fread(&voters[i]->gender, sizeof(char), 1, file);
                fread(&voters[i]->favoriteNumber, sizeof(int), 1, file);
                fread(&voters[i]->weight, sizeof(float), 1, file);
                voters[i]->timesWon = 0;
            }
        }
        fclose(file);
    }

    if (totalCapacity == 0) {
        totalCapacity = 10;
        effectiveSize = 0;
        voters = (VOTER **)malloc(sizeof(VOTER *) * totalCapacity);
    }
    char inputBuf[100];
    printf("ADD VOTER RECORDS\n");
    
    while (effectiveSize < totalCapacity) {
        printf("\nDo you want to enter a new record?(Y/N): ");
        readLine(inputBuf, sizeof(inputBuf));
        if (toupper(inputBuf[0]) != 'Y') {
            break;
        }

        voters[effectiveSize] = (VOTER *)malloc(sizeof(VOTER));
        VOTER *v = voters[effectiveSize];
        v->timesWon = 0;

        printf("Enter First Name: ");
        readLine(v->name.firstName, sizeof(v->name.firstName));

        printf("Enter middle Initial (leave blank if none): ");
        readLine(inputBuf, sizeof(inputBuf));
        v->name.middleInitial = inputBuf[0];

        printf("Enter Last name: ");
        readLine(v->name.lastName, sizeof(v->name.lastName));

        printf("Enter Gender (M, F, O, U): ");
        readLine(inputBuf, sizeof(inputBuf));
        v->gender = inputBuf[0];

        printf("Enter favorite Number (0 - 999): ");
        readLine(inputBuf, sizeof(inputBuf));
        v->favoriteNumber = atoi(inputBuf);

        printf("Enter weight (10.0 - 999.0): ");
        readLine(inputBuf, sizeof(inputBuf));
        v->weight = (float)atof(inputBuf);

        effectiveSize++;
    }
    for (int i = 0; i < effectiveSize; i++) {
        formatName(&voters[i]->name);
        validateGender(&voters[i]->gender);
    }

    for (int draw = 0; draw < 500; draw++) {
        int winningNum = rand() % 1000;
        for (int i = 0; i < effectiveSize; i++) {
            if (voters[i]->favoriteNumber == winningNum) {
                voters[i]->timesWon++;
            }
        }
    }

    printf("\n%-25s %-8s %-12s %-10s %-8s %-15s\n", 
           "Name", "Gender", "Favorite No.", "Times Won", "Weight", "Weight Statement");

    for (int i = 0; i < effectiveSize; i++) {
        char fullName[130];
        if (voters[i]->name.middleInitial != '\0' && voters[i]->name.middleInitial != ' ') {
            snprintf(fullName, sizeof(fullName), "%s %c. %s", 
                     voters[i]->name.firstName, 
                     voters[i]->name.middleInitial, 
                     voters[i]->name.lastName);
        } else {
            snprintf(fullName, sizeof(fullName), "%s %s", 
                     voters[i]->name.firstName, 
                     voters[i]->name.lastName);
        }

        char weightCategory[10];
        getWeightCategory(voters[i]->gender, voters[i]->weight, weightCategory);

        printf("%-25s %-8c %-12d %-10d %-8.0f %-15s\n",
               fullName,
               voters[i]->gender,
               voters[i]->favoriteNumber,
               voters[i]->timesWon,
               voters[i]->weight,
               weightCategory);
    }
    file = fopen(filePath,"wb");
    if (file != NULL) {
        fwrite(&totalCapacity, sizeof(int), 1,file);
        fwrite(&effectiveSize, sizeof(int), 1,file);

        for (int i = 0; i < effectiveSize; i++) {
            fwrite(&voters[i]->name, sizeof(NAME),1, file);
            fwrite(&voters[i]->gender, sizeof(char),1, file);
            fwrite(&voters[i]->favoriteNumber, sizeof(int), 1,file);
            fwrite(&voters[i]->weight, sizeof(float), 1,file);
        }
        fclose(file);
        printf("\nData successfully saved to %s\n", filePath);
    } else {
        printf("\nError opening file for writing.\n");
    }

    for (int i = 0; i < effectiveSize; i++) {
        free(voters[i]);
    }
    free(voters);
    return 0;
}