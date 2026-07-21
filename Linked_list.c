#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[100];
    int age;
    float weight;
    struct Node *next;
} Node;
void readLine(char *buffer,size_t size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
    } else {
        buffer[0] = '\0';
    }
}
Node* createNode(const char *name,int age,float weight) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0';
    newNode->age = age;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
void insertSorted(Node **headRef,const char *name,int age,float weight) {
    Node *newNode = createNode(name, age, weight);
    if (*headRef == NULL || strcmp(name, (*headRef)->name) < 0) {
        newNode->next = *headRef;
        *headRef = newNode;
        return;
    }
    Node *current = *headRef;
    while (current->next != NULL && strcmp(current->next->name, name) < 0) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}
void displayList(Node *head) {
    if (head == NULL) {
        printf("\nNo records found in the list.\n");
        return;
    }

    printf("\n%-25s %-8s %-8s\n","Name","Age","Weight");

    Node *current = head;
    while (current != NULL) {
        printf("%-25s %-8d %-8.2f\n", current->name, current->age, current->weight);
        current = current->next;
    }
}
void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node *head = NULL;
    char inputBuf[100];
    int choice = 0;

    while (choice != 3) {
        printf("\nMENU SYSTEM\n");
        printf("1.Add a Record\n");
        printf("2.Display All Records\n");
        printf("3.Quit\n");
        printf("Enter choice (1-3):");

        readLine(inputBuf, sizeof(inputBuf));
        choice = atoi(inputBuf);

        switch (choice) {
            case 1: {
                char name[100];
                int age;
                float weight;

                printf("\nEnter Name:");
                readLine(name, sizeof(name));

                printf("Enter Age:");
                readLine(inputBuf, sizeof(inputBuf));
                age = atoi(inputBuf);

                printf("Enter Weight:");
                readLine(inputBuf, sizeof(inputBuf));
                weight = (float)atof(inputBuf);

                insertSorted(&head, name, age, weight);
                printf("Record successfully added!\n");
                break;
            }
            case 2:
                displayList(head);
                break;

            case 3:
                printf("\nExiting program\n");
                break;

            default:
                printf("\nInvalid option. Please enter 1, 2, or 3.\n");
                break;
        }
    }
    freeList(head);
    return 0;
}