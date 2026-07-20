#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIMIT 1000
#define INITIAL_COUNT 10

typedef struct {
    int id;
    char name[50];
    double price;
} Product;

int main() {
    Product stackArray[MAX_LIMIT] = {
        {101, "Laptop", 899.99},
        {102, "Smartphone", 599.99},
        {103, "Headphones", 79.99},
        {104, "Keyboard", 45.50},
        {105, "Mouse", 25.00},
        {106, "Monitor", 179.99},
        {107, "Desk Lamp", 34.99},
        {108, "External Hard Drive", 89.00},
        {109, "Webcam", 69.99},
        {110, "USB Flash Drive", 14.99}
    };
    
    int count = INITIAL_COUNT;
    Product *heapArray = (Product *)malloc(count * sizeof(Product));
    if (heapArray == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        heapArray[i] = stackArray[i];
    }
    printf("--- Printing Stack Array Contents ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %-20s | Price: $%.2f\n", 
               stackArray[i].id, stackArray[i].name, stackArray[i].price);
    }

    printf("\n--- Printing Heap Array Contents ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %-20s | Price: $%.2f\n", 
               heapArray[i].id, heapArray[i].name, heapArray[i].price);
    }
    FILE *file = fopen("products.bin", "wb");
    if (file == NULL) {
        printf("\nError opening file for writing!\n");
        free(heapArray);
        return 1;
    }
    size_t elementsWritten = fwrite(heapArray, sizeof(Product), count, file);
    fclose(file);

    if (elementsWritten == count) {
        printf("\nSuccessfully saved %d elements to 'products.bin'.\n", count);
    } else {
        printf("\nError: Failed to write all elements to file.\n");
    }
    free(heapArray);

    return 0;
}