#include <stdio.h>
int main() {
    int values[]  ={1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *roman[]= {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int number;
    char choice;
    do {
        printf("Enter a number between 1 and 1000: ");
        if (scanf("%d", &number)!= 1 ||number < 1|| number >1000) {
            printf("Invalid input.Please enter a number from 1 to 1000.\n");
            while (getchar()!= '\n');
            continue;
        }
        printf("Roman numeral equivalent: ");
        for (int i = 0; i < 13; i++) {
            while (number >= values[i]) {
                printf("%s", roman[i]);
                number -= values[i];
            }
        }
        printf("\n\n");
        printf("enter another number? (y/n): ");
        scanf(" %c",&choice);
        printf("\n");
    } while (choice == 'y' || choice == 'Y');
    return 0;
}