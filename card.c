#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define NUM_PLAYERS 3
#define CARDS_PER_PLAYER 17
typedef struct {
    const char *suit;
    const char *rank;
} Card;

int main() {

    const char *suits[] = {"Hearts","Diamonds","Clubs", "Spades"};
    const char *ranks[] = {"2", "3", "4","5", "6", "7","8", "9", "10","Jack","Queen", "King", "Ace"};

    Card deck[DECK_SIZE];

    Card player1[CARDS_PER_PLAYER];
    Card player2[CARDS_PER_PLAYER];
    Card player3[CARDS_PER_PLAYER];
    srand(time(NULL));
    int cardIndex = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck[cardIndex].suit = suits[i];
            deck[cardIndex].rank = ranks[j];
            cardIndex++;
        }
    }
    for (int i = DECK_SIZE - 1;i > 0; i--) {
        int j = rand() %(i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
    int deckPtr = 0;
    for (int i =0; i < CARDS_PER_PLAYER;i++) {
        player1[i] = deck[deckPtr++];
        player2[i] = deck[deckPtr++];
        player3[i] = deck[deckPtr++];
    }
    printf("PLAYER 1\n");
    for (int i = 0;i < CARDS_PER_PLAYER; i++) {
        printf("%s of %s\n", player1[i].rank, player1[i].suit);
    }

    printf("\nPLAYER 2\n");
    for (int i = 0; i < CARDS_PER_PLAYER; i++) {
        printf("%s of %s\n", player2[i].rank, player2[i].suit);
    }

    printf("\nPLAYER 3\n");
    for (int i = 0; i < CARDS_PER_PLAYER; i++) {
        printf("%s of %s\n", player3[i].rank, player3[i].suit);
    }
    printf("\nleftover :\n");
    printf("%s of %s\n", deck[deckPtr].rank, deck[deckPtr].suit);

    return 0;
}