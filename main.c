#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100

typedef struct {
    char name[50];
    char location[100];
    int type; /* 1 = Lost, 2 = Found */
} Item;

Item items[MAX_ITEMS];
int count = 0;

void removeNewline(char text[]) {
    text[strcspn(text, "\n")] = '\0';
}

void loadItems(void) {
    FILE *file = fopen("items.txt", "r");
    if (file == NULL) return;

    while (count < MAX_ITEMS &&
           fscanf(file, "%d|%49[^|]|%99[^\n]\n",
                  &items[count].type,
                  items[count].name,
                  items[count].location) == 3) {
        count++;
    }
    fclose(file);
}

void saveItems(void) {
    FILE *file = fopen("items.txt", "w");
    if (file == NULL) {
        printf("Error: Could not save items.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s\n",
                items[i].type, items[i].name, items[i].location);
    }
    fclose(file);
}

void showMenu(void) {
    printf("\n================================\n");
    printf("       CAMPUS LOST & FOUND\n");
    printf("================================\n");
    printf("1. Report Lost Item\n");
    printf("2. Report Found Item\n");
    printf("3. Search for Item\n");
    printf("4. View All Items\n");
    printf("5. Remove Item\n");
    printf("6. Exit\n");
}

void reportItem(int type) {
    if (count >= MAX_ITEMS) {
        printf("\nStorage is full!\n");
        return;
    }

    printf("\nEnter item name: ");
    fgets(items[count].name, sizeof(items[count].name), stdin);
    removeNewline(items[count].name);

    printf("Enter location: ");
    fgets(items[count].location, sizeof(items[count].location), stdin);
    removeNewline(items[count].location);

    if (items[count].name[0] == '\0' || items[count].location[0] == '\0') {
        printf("\nName and location cannot be empty.\n");
        return;
    }

    items[count].type = type;
    count++;
    saveItems();

    printf("\n%s item reported successfully!\n",
           type == 1 ? "Lost" : "Found");
}

void displayItem(int index) {
    printf("\nItem %d\n", index + 1);
    printf("Name: %s\n", items[index].name);
    printf("Location: %s\n", items[index].location);
    printf("Status: %s\n", items[index].type == 1 ? "Lost" : "Found");
}

void viewItems(void) {
    if (count == 0) {
        printf("\nNo items reported yet.\n");
        return;
    }

    printf("\n===== ALL REPORTED ITEMS =====\n");
    for (int i = 0; i < count; i++) {
        displayItem(i);
    }
}

void searchItem(void) {
    char searchName[50];
    int found = 0;

    printf("\nEnter item name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    removeNewline(searchName);

    for (int i = 0; i < count; i++) {
        if (strcmp(items[i].name, searchName) == 0) {
            printf("\nItem found!");
            displayItem(i);
            found = 1;
        }
    }

    if (!found) printf("\nItem not found.\n");
}

void removeItem(void) {
    int number;

    if (count == 0) {
        printf("\nNo items available to remove.\n");
        return;
    }

    viewItems();
    printf("\nEnter item number to remove: ");

    if (scanf("%d", &number) != 1) {
        printf("\nPlease enter a valid number.\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    if (number < 1 || number > count) {
        printf("\nInvalid item number.\n");
        return;
    }

    for (int i = number - 1; i < count - 1; i++) {
        items[i] = items[i + 1];
    }

    count--;
    saveItems();
    printf("\nItem removed successfully.\n");
}

int main(void) {
    int choice = 0;
    loadItems();

    while (choice != 6) {
        showMenu();
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nPlease enter a number from 1 to 6.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1: reportItem(1); break;
            case 2: reportItem(2); break;
            case 3: searchItem(); break;
            case 4: viewItems(); break;
            case 5: removeItem(); break;
            case 6: printf("\nThank you for using Campus Finder!\n"); break;
            default: printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}
