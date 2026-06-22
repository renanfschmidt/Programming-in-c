#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(){
    char string[101];
    int lenght;
    char choice;
    do{
    
    int lettercount = 0;
    printf("Type a string:");
    fgets(string ,sizeof(string),stdin);
    string[strcspn(string, "\n")] = '\0';
    printf("The string is %s\n",string);
    lenght=strlen(string);
    printf("Total characters is: %d\n", lenght);

    for (int i = lenght -1; i >=0; i--){
        printf("%c",string[i]);
    }
    for (int i = 0; i< lenght;i++){
        printf("%c\n",string[i]);
    }
    for (int i = 0; i <lenght;i++){
        for (int j=0;j<=i ; j++){
            printf("%c",string[j]);
        }
        printf("\n");
    }
    printf("\nDo you wnat to type a new string [Y/N]:");
    scanf("%c",&choice);
    while(getchar()!= '\n');}
    while (choice== 'Y');
    return 0;

}