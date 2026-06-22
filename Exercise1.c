#include <stdio.h>
int main(){
    int totalDeposits = 0;
    double deposits[100];
    char choice;
    
    do{
        printf("\n***Banking Main Menu***\n");
        printf("[G]et a new deposit\n");
        printf("[S]um of all deposits\n");
        printf("[D]eposits will be displayed from highest to lowest deposit\n");
        printf("[L]owest deposit will be displayed\n");
        printf("[Q]uit\n");
        scanf(" %c",&choice);

        switch(choice) {
         case 'G':
         case 'g':
             printf("Enter a new deposit amount:");
             scanf("%lf", &deposits[totalDeposits]);
             totalDeposits++;
             break;
         case 'S':
         case 's':
                double totalSum = 0.0; 
                for (int i = 0; i < totalDeposits; i++) {
                    totalSum += deposits[i];
                }
                printf("The sum of all deposits is: $%.2f\n", totalSum);
                break;
         case 'D':
         case 'd':
               double sortedDeposits[100];
               double temp;
               for(int i = 0; i < totalDeposits; i++) {
               sortedDeposits[i] = deposits[i];}for (int i = 0; i < totalDeposits - 1; i++) {for (int j = 0; j < totalDeposits - 1 - i; j++) {
                if (sortedDeposits[j] <sortedDeposits[j + 1]) 
                temp = sortedDeposits[j];
                         sortedDeposits[j] = sortedDeposits[j + 1];
                         sortedDeposits[j + 1] = temp;

    }
}
printf("\nDeposits from Highest to Lowest:\n");
for(int i = 0; i < totalDeposits; i++) {
    printf("$%.2f\n", sortedDeposits[i]);
}
                 break;
         case'Q':
         case'q':
                printf("Exiting the program.Goodbye!\n");
                break;
        case 'L':
        case 'l':
                if(totalDeposits == 0){
                    printf("You dont have a deposit\n");}
                    else { double lowest = deposits[0];
                    for(int i =1;i<totalDeposits;i++){
                        if(deposits[i]<lowest){
                         lowest = deposits[i];
                        }
                    }
                     printf("The lowest deposit is :%.2f\n", lowest);
                }
                break;
         default:
                printf("Invalid choice!\n");
         }
     } while (choice!= 'Q' && choice != 'q');

     return 0;
    
}
     