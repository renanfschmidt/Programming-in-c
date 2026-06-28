#include <stdio.h>
#include <ctype.h>

int main() {
    char cipher[] = "HIVJKWLMNYNBOZCPUDQSREGF";
    char input[100], encoded[100];
    char repeat;
    do {
        printf("Enter a word: ");
        scanf("%99s", input);
        int i = 0;
        while (input[i] != '\0') {
            char current = input[i];
            if (isalpha(current)) {
                int index= toupper(current) -'A';
                char encoded_char = cipher[index];
                encoded[i] = islower(current) ? tolower(encoded_char) : encoded_char;
            } else {
                encoded[i] =current;
            }
            i++;
        }
        encoded[i]= '\0';
        printf("original: %s\n", input);
        printf("encoded:  %s\n\n", encoded);
        printf("add another word?(y/n): ");
        scanf(" %c",&repeat);
        printf("\n");

    } while (repeat== 'y' || repeat== 'Y');
    return 0;
}