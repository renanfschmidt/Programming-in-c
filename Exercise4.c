#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void cleanWord(char *str) {
 int len = strlen(str);
 while (len > 0 && (ispunct(str[len - 1]) || isspace(str[len - 1]))) {
        str[len - 1] = '\0';
        len--;}
}
int main() {
    FILE *keyFile,*resumeFile;
   char keywordBuffer[1024];
   char resumeBuffer[100];
   char keywords[50][30];
   int keywordCount = 0;
   int matchTally= 0;
    keyFile = fopen("keywords.txt", "r");
    if (keyFile == NULL) {
      printf("Check'keywords.txt' is in the same folder.\n");
        return 1;
    }
    if (fgets(keywordBuffer, sizeof(keywordBuffer), keyFile) != NULL) {

        keywordBuffer[strcspn(keywordBuffer, "\n")] = '\0';
        char *token = strtok(keywordBuffer, ",");
        while (token != NULL && keywordCount < 50) {
            strcpy(keywords[keywordCount], token);
            keywordCount++;
            token = strtok(NULL, ",");
        }
    }
    fclose(keyFile);
    printf("Loaded %d keywords to scan for:\n", keywordCount);
    for(int i = 0; i < keywordCount; i++) {
        printf("- %s\n", keywords[i]);
    }
    resumeFile = fopen("resume.txt", "r");
    if (resumeFile == NULL) {
        printf("Check'resume.txt' is in the same folder.\n");
        return 1;
    }
    while (fscanf(resumeFile, "%99s", resumeBuffer) != EOF) {
        cleanWord(resumeBuffer);
        for (int i = 0; i < keywordCount; i++) {
            if (strcasecmp(resumeBuffer, keywords[i]) == 0) {
                matchTally++;
            }
        }
    }
    fclose(resumeFile);
    printf("Total Keyword Matches Found: %d\n", matchTally);
    
    if (matchTally >= 5) {
        printf("Result:Interview!\n");
    } else {
        printf("Result:Review.\n");
    }

    return 0;
}