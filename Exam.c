#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10
#define HIGH_SCORE_FILE "src/topTenScores.txt"
#define SAVE_FILE "src/battleship_save.txt"

typedef struct { char id; char name[30]; int len; } Ship;
typedef struct { char name[50]; int score; } Score;

Ship fleet[5] = {
    {'S', "Seminole State Ship", 3},
    {'A', "Air Force Academy", 5},
    {'V', "Valencia Destroyer", 4},
    {'E', "Eskimo University", 3},
    {'D', "Deland High School", 2}
};
char hidden[SIZE][SIZE], tracking[SIZE][SIZE];
int missiles = 0, hits_left = 17;
void print_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) printf("%c ", tracking[i][j]);
        printf("\n");
    }
    printf("\n");
}
void place_ships() {
    memset(hidden, ' ', sizeof(hidden));
    for (int s = 0; s < 5; s++) {
        int placed = 0;
        while (!placed) {
            int horiz = rand() % 2;
            int r = rand()% (SIZE - (!horiz ? fleet[s].len - 1 : 0));
            int c = rand() %(SIZE - (horiz ? fleet[s].len - 1 : 0));
            
            int overlap = 0;
            for (int i = 0; i < fleet[s].len; i++) {
                if (hidden[r +(!horiz ? i : 0)][c + (horiz ? i : 0)]!= ' ')overlap = 1;
            }
            
            if (!overlap) {
                for (int i = 0; i < fleet[s].len;i++) {
                    hidden[r + (!horiz ? i : 0)][c + (horiz ? i : 0)] = fleet[s].id;
                }
                placed = 1;
            }
        }
    }
}
void view_scores() {
    FILE *f = fopen(HIGH_SCORE_FILE, "r");
    printf("\n--- TOP 10 BEST SCORES ---\n");
    if (!f){ printf("No scores recorded yet.\n\n"); return; }
    char line[100];
    int rank = 1;
    while (fgets(line, sizeof(line), f) && rank<= 10) {
        printf("%d. %s",rank++, line);
    }
    fclose(f);
    printf("\n");
}
void log_score(char *name, int score) {
    Score list[11];
    int count = 0;
    FILE *f =fopen(HIGH_SCORE_FILE, "r");
    if (f) {
        while (count < 10 && fscanf(f, "%[^,],%d\n",list[count].name,&list[count].score)== 2) count++;
        fclose(f);
    }  
    strcpy(list[count].name, name);
    list[count].score = score;
    count++;
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j< count;j++) {
            if (list[i].score > list[j].score) {
                Score tmp = list[i]; list[i] = list[j]; list[j] = tmp;
            }
        }
    }

    f = fopen(HIGH_SCORE_FILE, "w");
    if (f) {
        int limit = count < 10 ? count : 10;
        for (int i = 0; i < limit; i++)fprintf(f, "%s,%d\n", list[i].name,list[i].score);
        fclose(f);
    }
}
void save_game() {
    FILE *f = fopen(SAVE_FILE,"w");
    if (!f) return;
    fprintf(f, "%d\n%d\n", missiles, hits_left);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) fputc(hidden[i][j],f);
        fputc('\n', f);
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)fputc(tracking[i][j],f);
        fputc('\n', f);
    }
    fclose(f);
}
int resume_game() {
    FILE *f = fopen(SAVE_FILE, "r");
    if (!f) return 0;
    fscanf(f, "%d\n%d\n", &missiles,&hits_left);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) hidden[i][j] =fgetc(f);
        fgetc(f);
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) tracking[i][j]= fgetc(f);
        fgetc(f);
    }
    fclose(f);
    return 1;
}

int ship_dead(char id) {
    for (int i = 0; i <SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (hidden[i][j] == id && tracking[i][j] != 'H') return 0;
        }
    }
    return 1;
}

void sink_animation(char id) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (hidden[i][j] == id) tracking[i][j] = id;
        }
    }
}

void play(int resume) {
    if (!resume || !resume_game()) {
        missiles = 0; hits_left = 17;
        memset(tracking, 'X',sizeof(tracking));
        place_ships();
    }

    while (hits_left > 0) {
        print_board();
        printf("Missiles fired: %d\nTarget (row col) or -1 to save & quit: ", missiles);
        int r, c;
        if (scanf("%d", &r) != 1 || r == -1) {
            if (r == -1) { save_game(); printf("Game saved. Goodbye!\n"); }
            return;
        }
        if (scanf("%d", &c) != 1 || r < 0 || r >= SIZE || c < 0 || c >= SIZE || tracking[r][c] != 'X') {
            printf("Invalid move. Try again.\n");continue;
        }
        missiles++;
        if (hidden[r][c] != ' ') {
            tracking[r][c] = 'H';
            hits_left--;
            printf("\nHIT!\n");
            if (ship_dead(hidden[r][c])) {
                for (int s = 0; s < 5; s++) {
                    if (fleet[s].id == hidden[r][c]) printf("You sank the %s!\n\n", fleet[s].name);
                }
                sink_animation(hidden[r][c]);
            }
        } else {
            tracking[r][c] = 'M';
            printf("\nMISS!\n");
        }
    }
    print_board();
    printf("win!You used %d missiles.\n", missiles);
    remove(SAVE_FILE);
    
    char name[50];
    printf("Enter name for leaderboard: ");
    scanf("%s", name);
    log_score(name, missiles);
    view_scores();
}

int main() {
    srand(time(NULL));
    char choice;
    while (1) {
        printf(" MAIN MENU\nA.New Game\nB.Resume Game\nC.High Scores\nD.Quit\nChoice: ");
        scanf(" %c", &choice);
        if (choice == 'A' || choice == 'a') play(0);
        else if (choice == 'B' || choice == 'b') play(1);
        else if (choice == 'C' || choice == 'c') view_scores();
        else if (choice == 'D' || choice == 'd') break;
    }
    return 0;
}