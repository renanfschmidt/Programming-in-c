#include <stdio.h>
#include <stdlib.h>
#define MAX_WORDS 1000
#define STR_LEN 50
typedef struct { 
    char words[MAX_WORDS][STR_LEN];
    int count;
} Tracker;
void handleFiles(Tracker *t, int save) {
    FILE *f = fopen("data.bin",save ? "wb" : "rb");
    if (f) {
      if (save) fwrite(t, sizeof(Tracker), 1, f);
      else fread(t, sizeof(Tracker), 1, f);
        fclose(f);
    }
}
int main() {
    Tracker t = {.count = 0};
    handleFiles(&t,0);
    int choice;
    do {
        printf("\n1 Add 2 Export 3 Dumnp 4 Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
          while (getchar()!= '\n');
        continue;
        }
        if (choice == 1) {
            int num;
            printf("How many? ");
            if (scanf("%d", &num) ==1 && t.count + num<= MAX_WORDS) {
                for (int i = 0; i < num; i++) {
                    printf("Word %d: ",t.count + 1);
                    scanf("%49s", t.words[t.count++]);
                }
            } else printf("Invalid\n");
        } 
        else if (choice == 2) {
            FILE *txt = fopen("export.txt","w");
            if (txt) {
                for (int i = 0; i < t.count; i++) fprintf(txt, "%s\n", t.words[i]);
                fclose(txt);
                printf("Exported\n");
            }
        } 
        else if (choice == 3) {
           t.count = 0;
            printf("memory cleared\n");
        }
    } while (choice!= 4);
    handleFiles(&t, 1);
    printf("Saved\n");
    return 0;
}