#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct { char name[20]; int mult, chance; } DOG;
typedef struct { char chosen[20], winner[20]; double wager, net; } Record;
int main() {
    srand(time(NULL));
    DOG dogs[9] = {{"Bolt",2,40}, {"Sparky",5,10}, {"Rocky",10,8}, {"Buster",15,6}, 
                   {"Lucky",50,1}, {"Shadow",20,4}, {"Rex",10,8}, {"Max",5,10}, {"Buddy",3,13}};
    Record history[100];
    int r_count = 0;
    double wallet = 100.0;
    char choice;
    do {
        printf("\nWallet: $%.2f\n[G]amble [B]anking [R]esults [L]eave\nChoice: ", wallet);
        scanf(" %c", &choice);
        if ((choice == 'g' || choice == 'G') && wallet > 0 && r_count < 100) {
            double wager;
            printf("Wager amount: $");
            if (scanf("%lf", &wager) != 1 || wager <= 0 || wager > wallet) continue;
            for (int i = 0; i < 9; i++) printf("%d. %s (%d to 1)\n", i+1, dogs[i].name, dogs[i].mult);
            int pick;
            printf("Pick a dog (1-9): ");
            if (scanf("%d", &pick) != 1 || pick < 1 || pick > 9) continue;
            pick--;
            int roll = rand() % 100 + 1, sum = 0, win = 8;
            for (int i = 0; i < 9; i++) {
                sum += dogs[i].chance;
                if (roll <= sum) { win = i; break; }
            }
            Record *r = &history[r_count++];
            strcpy(r->chosen, dogs[pick].name);
            strcpy(r->winner, dogs[win].name);
            r->wager = wager;
            r->net = (pick == win) ? wager * dogs[pick].mult : -wager;
            wallet += r->net;
            printf("Winner: %s! You %s $%.2f\n", dogs[win].name, (pick == win) ? "won" : "lost", (pick == win) ? r->net : wager);
        } 
        else if (choice == 'b' || choice == 'B') {
            char act; double amt;
            printf("[D]eposit or [W]ithdraw? ");
            scanf(" %c", &act);
            printf("Amount: $");
            if (scanf("%lf", &amt) == 1 && amt > 0) {
                if ((act == 'd' || act == 'D')) wallet += amt;
                else if ((act == 'w' || act == 'W') && amt <= wallet) wallet -= amt;
            }
        } 
        else if (choice == 'r' || choice == 'R') {
            if (r_count == 0) printf("No races yet.\n");
            for (int i = 0; i < r_count; i++) 
                printf("Race %d | Bet: %s | Winner: %s | Net: %.2f\n", i+1, history[i].chosen, history[i].winner, history[i].net);
        }
    } while (choice != 'l' && choice != 'L');
    return 0;
}