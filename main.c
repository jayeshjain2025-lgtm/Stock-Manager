#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 1000
#define NAME_LENGTH 64
#define DATA_FILE "inventory.txt"

typedef struct {
    int productId;
    char name[NAME_LENGTH];
    double price;
    int quantity;
    int inUse;
} Product;

int findProductIndexById(Product inventory[], int count, int productId);
int readInt(const char *prompt, int min, int max);
double readDouble(const char *prompt, double min, double max);
void readString(const char *prompt, char *buffer, size_t size);
void addProduct(Product inventory[], int *count);
void updateStock(Product inventory[], int count);
void deleteProduct(Product inventory[], int *count);
void searchProduct(Product inventory[], int count);
void lowStockReport(Product inventory[], int count);
void showTotalInventoryValue(Product inventory[], int count);
int saveToFile(Product inventory[], int count, const char *filename);
int loadFromFile(Product inventory[], int *count, const char *filename);
void displayMenu(void);

int main(void) {
    Product inventory[MAX_PRODUCTS] = {0};
    int count = 0;
    int choice;

    if (loadFromFile(inventory, &count, DATA_FILE)) {
        printf("Loaded %d products from %s.\n", count, DATA_FILE);
    }

    do {
        displayMenu();
        choice = readInt("Enter your choice: ", 0, 8);

        switch (choice) {
            case 1:
                addProduct(inventory, &count);
                break;
            case 2:
                updateStock(inventory, count);
                break;
            case 3:
                deleteProduct(inventory, &count);
                break;
            case 4:
                searchProduct(inventory, count);
                break;
            case 5:
                if (saveToFile(inventory, count, DATA_FILE)) {
                    printf("Inventory saved successfully.\n");
                } else {
                    printf("Failed to save inventory.\n");
                }
                break;
            case 6:
                if (loadFromFile(inventory, &count, DATA_FILE)) {
                    printf("Inventory loaded successfully.\n");
                } else {
                    printf("Failed to load inventory.\n");
                }
                break;
            case 7:
                lowStockReport(inventory, count);
                break;
            case 8:
                showTotalInventoryValue(inventory, count);
                break;
            case 0:
                if (saveToFile(inventory, count, DATA_FILE)) {
                    printf("Saved before exit. Goodbye!\n");
                } else {
                    printf("Could not save before exit. Goodbye anyway!\n");
                }
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}

void displayMenu(void) {
    printf("\n=== Inventory Management System ===\n");
    printf("1. Add Product\n");
    printf("2. Update Stock (Purchase/Sale)\n");
    printf("3. Delete Product\n");
    printf("4. Search by ProductID\n");
    printf("5. Save to File\n");
    printf("6. Load from File\n");
    printf("7. Low-Stock Report\n");
    printf("8. Show Total Inventory Value\n");
    printf("0. Exit\n");
}

int readInt(const char *prompt, int min, int max) {
    char input[128];
    int value;
    char extra;

    while (1) {
        printf("%s", prompt);
        if (!fgets(input, sizeof(input), stdin)) {
            clearerr(stdin);
            continue;
        }

        if (sscanf(input, "%d %c", &value, &extra) == 1 && value >= min && value <= max) {
            return value;
        }

        printf("Invalid input. Please enter an integer between %d and %d.\n", min, max);
    }
}

double readDouble(const char *prompt, double min, double max) {
    char input[128];
    double value;
    char extra;

    while (1) {
        printf("%s", prompt);
        if (!fgets(input, sizeof(input), stdin)) {
            clearerr(stdin);
            continue;
        }

        if (sscanf(input, "%lf %c", &value, &extra) == 1 && value >= min && value <= max) {
            return value;
        }

        printf("Invalid input. Please enter a number between %.2f and %.2f.\n", min, max);
    }
}

void readString(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (!fgets(buffer, (int)size, stdin)) {
        clearerr(stdin);
        buffer[0] = '\0';
        return;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
}

int findProductIndexById(Product inventory[], int count, int productId) {
    int i;
    for (i = 0; i < count; i++) {
        if (inventory[i].inUse && inventory[i].productId == productId) {
            return i;
        }
    }
    return -1;
}

void addProduct(Product inventory[], int *count) {
    Product p;

    if (*count >= MAX_PRODUCTS) {
        printf("Inventory is full.\n");
        return;
    }

    p.productId = readInt("Enter Product ID (1-999999): ", 1, 999999);
    if (findProductIndexById(inventory, *count, p.productId) != -1) {
        printf("A product with ID %d already exists.\n", p.productId);
        return;
    }

    readString("Enter Name: ", p.name, sizeof(p.name));
    if (strlen(p.name) == 0) {
        printf("Name cannot be empty.\n");
        return;
    }

    p.price = readDouble("Enter Price (0.01-1000000): ", 0.01, 1000000.0);
    p.quantity = readInt("Enter Quantity (0-1000000): ", 0, 1000000);
    p.inUse = 1;

    inventory[*count] = p;
    (*count)++;

    printf("Product added successfully.\n");
}

void updateStock(Product inventory[], int count) {
    int id;
    int index;
    int option;
    int amount;

    if (count == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    id = readInt("Enter Product ID to update: ", 1, 999999);
    index = findProductIndexById(inventory, count, id);

    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    printf("Selected: %s (Current Qty: %d)\n", inventory[index].name, inventory[index].quantity);
    option = readInt("1. Purchase (increase)  2. Sale (decrease): ", 1, 2);
    amount = readInt("Enter quantity amount: ", 1, 1000000);

    if (option == 1) {
        inventory[index].quantity += amount;
        printf("Stock increased. New quantity: %d\n", inventory[index].quantity);
    } else {
        if (amount > inventory[index].quantity) {
            printf("Sale quantity exceeds current stock.\n");
            return;
        }
        inventory[index].quantity -= amount;
        printf("Stock decreased. New quantity: %d\n", inventory[index].quantity);
    }
}

void deleteProduct(Product inventory[], int *count) {
    int id;
    int index;
    int i;

    if (*count == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    id = readInt("Enter Product ID to delete: ", 1, 999999);
    index = findProductIndexById(inventory, *count, id);

    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    for (i = index; i < *count - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    (*count)--;
    printf("Product deleted successfully.\n");
}

void searchProduct(Product inventory[], int count) {
    int id;
    int index;

    if (count == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    id = readInt("Enter Product ID to search: ", 1, 999999);
    index = findProductIndexById(inventory, count, id);

    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    printf("Found: ID=%d, Name=%s, Price=%.2f, Quantity=%d\n",
           inventory[index].productId,
           inventory[index].name,
           inventory[index].price,
           inventory[index].quantity);
}

void lowStockReport(Product inventory[], int count) {
    int threshold;
    int i;
    int found = 0;

    if (count == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    threshold = readInt("Enter low-stock threshold: ", 0, 1000000);
    printf("\nProducts below threshold (%d):\n", threshold);

    for (i = 0; i < count; i++) {
        if (inventory[i].inUse && inventory[i].quantity < threshold) {
            printf("- ID=%d, Name=%s, Qty=%d, Price=%.2f\n",
                   inventory[i].productId,
                   inventory[i].name,
                   inventory[i].quantity,
                   inventory[i].price);
            found = 1;
        }
    }

    if (!found) {
        printf("No low-stock products found.\n");
    }
}

void showTotalInventoryValue(Product inventory[], int count) {
    int i;
    double total = 0.0;

    for (i = 0; i < count; i++) {
        if (inventory[i].inUse) {
            total += inventory[i].price * inventory[i].quantity;
        }
    }

    printf("Total inventory value: %.2f\n", total);
}

int saveToFile(Product inventory[], int count, const char *filename) {
    FILE *fp;
    int i;

    fp = fopen(filename, "w");
    if (!fp) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (inventory[i].inUse) {
            fprintf(fp, "%d|%s|%.2f|%d\n",
                    inventory[i].productId,
                    inventory[i].name,
                    inventory[i].price,
                    inventory[i].quantity);
        }
    }

    fclose(fp);
    return 1;
}

int loadFromFile(Product inventory[], int *count, const char *filename) {
    FILE *fp;
    char line[256];
    Product p;

    fp = fopen(filename, "r");
    if (!fp) {
        return 0;
    }

    *count = 0;
    while (fgets(line, sizeof(line), fp) && *count < MAX_PRODUCTS) {
        if (sscanf(line, "%d|%63[^|]|%lf|%d",
                   &p.productId,
                   p.name,
                   &p.price,
                   &p.quantity) == 4) {
            p.inUse = 1;
            inventory[*count] = p;
            (*count)++;
        }
    }

    fclose(fp);
    return 1;
}
