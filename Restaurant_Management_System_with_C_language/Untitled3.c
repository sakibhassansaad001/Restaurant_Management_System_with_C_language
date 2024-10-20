#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 1000
#define MAX_ORDERS 100

struct User {
    char username[50];
    char password[50];
    char userType[50];
};

struct FoodItem {
    char name[50];
    float price;
};

struct Order {
    char username[50];
    struct FoodItem items[10];
    int itemCount;
    float totalAmount;
};

void registerUser();
int loginUser(char* username, char* password);
void saveUsers();
int loadUsers();
void viewCuisine();
void selectfood();
void placeorder();
void paymentinvoice();
void mainMenu();

void viewsellsreport();
void viewstockreport();

struct User users[MAX_USERS];
int numUsers = 0;
struct Order orders[MAX_ORDERS];
int numOrders = 0;

int main() {
    int choice;

    loadUsers();

    while (1) {
        printf("\n\n******************** Welcome to RESTORA- Food Ordering System **************** ");
        printf("\n\n1) SIGNUP\n");
        printf("2) LOGIN\n");
        printf("3) EXIT\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2: {
                char username[50], password[50];
                printf("Enter your username: ");
                scanf("%s",username);
                printf("Enter your password: ");
                scanf("%s",password);
                if (loginUser(username, password)) {
                    mainMenu();
                }
                break;
            }
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }

    }

    return 0;
}

void mainMenu() {
    int choice;

    while (1) {
        printf("\n\n1) VIEW CUISINE\n");
        printf("2) SELECT FOOD\n");
        printf("3) PLACE ORDER\n");
        printf("4) VIEW PAYMENT INVOICE\n");
        printf("5) LOGOUT\n");
        printf("6) EXIT\n");


        if (strcmp(users[numUsers-1].userType, "Manager") == 0) {
            printf("7) VIEW SELLS REPORT\n");
            printf("8) VIEW STOCK REPORT\n");
        }

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewCuisine();
                break;
            case 2:
                selectfood();
                break;
            case 3:
                placeorder();
                break;
            case 4:
                paymentinvoice();
                break;
            case 5:
                return;
            case 6:
                exit(0);
            case 7:
                if (strcmp(users[numUsers-1].userType, "Manager") == 0) {
                    viewsellsreport();
                } else {
                    printf("Invalid choice. Please try again.\n");
                }
                break;
            case 8:
                if (strcmp(users[numUsers-1].userType, "Manager") == 0) {
                    viewstockreport();
                } else {
                    printf("Invalid choice. Please try again.\n");
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void registerUser() {
    printf("Enter a username: ");
    scanf("%s", users[numUsers].username);

    printf("Enter a password: ");
    scanf("%s", users[numUsers].password);

    printf("Enter your user type (Manager or Seller): ");
    scanf("%s", users[numUsers].userType);

    numUsers++;

    saveUsers();
}

int loginUser(char* username, char* password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void saveUsers() {
    FILE* fp;

    if (strcmp(users[numUsers-1].userType, "Manager") == 0) {
        fp = fopen("managers.txt", "a");
    } else if (strcmp(users[numUsers-1].userType, "Seller") == 0) {
        fp = fopen("Sellers.txt", "a");
    }

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(fp, "%s %s %s\n", users[numUsers-1].username, users[numUsers-1].password, users[numUsers-1].userType);

    fclose(fp);
}

int loadUsers() {
    FILE* fp;
    char filename[50];
    char username[50], password[50], userType[50];


    strcpy(filename, "managers.txt");
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s.\n", filename);
        return 0;
    }

    while (fscanf(fp, "%s %s %s", username, password, userType) != EOF) {
        strcpy(users[numUsers].username, username);
        strcpy(users[numUsers].password, password);
        strcpy(users[numUsers].userType, userType);
        numUsers++;
    }

    fclose(fp);


    strcpy(filename, "Sellers.txt");
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s.\n", filename);
        return 0;
    }

    while (fscanf(fp, "%s %s %s", username, password, userType) != EOF) {
        strcpy(users[numUsers].username, username);
        strcpy(users[numUsers].password, password);
        strcpy(users[numUsers].userType, userType);
        numUsers++;
    }

    fclose(fp);

    return 1;
}

void viewCuisine() {
    int choice;
    while (1) {
        printf("\n\n1) VIEW ITALIAN CUISINE\n");
        printf("2) VIEW CHINESE CUISINE\n");
        printf("3) VIEW INDIAN CUISINE\n");
        printf("4) GO BACK TO MAIN MENU\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                FILE* fp = fopen("italian_cuisine.txt", "r");
                if (fp == NULL) {
                    printf("Could not open the file for viewing Italian cuisine.\n");
                } else {
                    char line[100];
                    while (fgets(line, sizeof(line), fp) != NULL) {
                        printf("%s", line);
                    }
                    fclose(fp);
                }
                break;
            }
            case 2: {
                FILE* fp = fopen("chinese_cuisine.txt", "r");
                if (fp == NULL) {
                    printf("Could not open the file for viewing Chinese cuisine.\n");
                } else {
                    char line[100];
                    while (fgets(line, sizeof(line), fp) != NULL) {
                        printf("%s", line);
                    }
                    fclose(fp);
                }
                break;
            }
            case 3: {
                FILE* fp = fopen("indian_cuisine.txt", "r");
                if (fp == NULL) {
                    printf("Could not open the file for viewing Indian cuisine.\n");
                } else {
                    char line[100];
                    while (fgets(line, sizeof(line), fp) != NULL) {
                        printf("%s", line);
                    }
                    fclose(fp);
                }
                break;
            }
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void selectfood() {
    int cuisineChoice, foodChoice, quantity;
    struct FoodItem selectedFood;

    printf("\n\nSelect Cuisine Type:\n");
    printf("1) ITALIAN CUISINE\n");
    printf("2) CHINESE CUISINE\n");
    printf("3) INDIAN CUISINE\n");
    printf("Enter your choice: ");
    scanf("%d", &cuisineChoice);

    switch (cuisineChoice) {
        case 1: {
            printf("\n\nSelect Food Item:\n");
            printf("1) Pizza - $10\n");
            printf("2) Pasta - $8\n");
            printf("3) Lasagna - $12\n");
            printf("4) Risotto - $14\n");
            printf("Enter your choice: ");
            scanf("%d", &foodChoice);

            switch (foodChoice) {
                case 1:
                    strcpy(selectedFood.name, "Pizza");
                    selectedFood.price = 10.0;
                    break;
                case 2:
                    strcpy(selectedFood.name, "Pasta");
                    selectedFood.price = 8.0;
                    break;
                case 3:
                    strcpy(selectedFood.name, "Lasagna");
                    selectedFood.price = 12.0;
                    break;
                case 4:
                    strcpy(selectedFood.name, "Risotto");
                    selectedFood.price = 14.0;
                    break;
                default:
                    printf("Invalid choice.\n");
                    return;
            }
            break;
        }
        case 2: {
            printf("\n\nSelect Food Item:\n");
            printf("1) Fried Rice - $8\n");
            printf("2) Sweet and Sour Chicken - $10\n");
            printf("3) Kung Pao Chicken - $12\n");
            printf("4) Wonton Soup - $6\n");
            printf("Enter your choice: ");
            scanf("%d", &foodChoice);

            switch (foodChoice) {
                case 1:
                    strcpy(selectedFood.name, "Fried Rice");
                    selectedFood.price = 8.0;
                    break;
                case 2:
                    strcpy(selectedFood.name, "Sweet and Sour Chicken");
                    selectedFood.price = 10.0;
                    break;
                case 3:
                    strcpy(selectedFood.name, "Kung Pao Chicken");
                    selectedFood.price = 12.0;
                    break;
                case 4:
                    strcpy(selectedFood.name, "Wonton Soup");
                    selectedFood.price = 6.0;
                    break;
                default:
                    printf("Invalid choice.\n");
                    return;
            }
            break;
        }
        case 3: {
            printf("\n\nSelect Food Item:\n");
            printf("1) Biryani - $12\n");
            printf("2) Butter Chicken - $10\n");
            printf("3) Samosa - $4\n");
            printf("4) Naan - $2\n");
            printf("Enter your choice: ");
            scanf("%d", &foodChoice);

            switch (foodChoice) {
                case 1:
                    strcpy(selectedFood.name, "Biryani");
                    selectedFood.price = 12.0;
                    break;
                case 2:
                    strcpy(selectedFood.name, "Butter Chicken");
                    selectedFood.price = 10.0;
                    break;
                case 3:
                    strcpy(selectedFood.name, "Samosa");
                    selectedFood.price = 4.0;
                    break;
                case 4:
                    strcpy(selectedFood.name, "Naan");
                    selectedFood.price = 2.0;
                    break;
                default:
                    printf("Invalid choice.\n");
                    return;
            }
            break;
        }
        default:
            printf("Invalid cuisine choice.\n");
            return;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    for (int i = 0; i < quantity; i++) {
        orders[numOrders].items[orders[numOrders].itemCount] = selectedFood;
        orders[numOrders].itemCount++;
        orders[numOrders].totalAmount += selectedFood.price;
    }

    printf("Food item added to order.\n");
}

void placeorder() {
    printf("Enter your username to confirm order: ");
    scanf("%s", orders[numOrders].username);

    printf("Order placed successfully.\n");
    numOrders++;
}

void paymentinvoice() {
    printf("\n\n******************** PAYMENT INVOICE ********************\n");

    for (int i = 0; i < numOrders; i++) {
        printf("Order by %s\n", orders[i].username);
        printf("Items:\n");
        for (int j = 0; j < orders[i].itemCount; j++) {
            printf("%s - $%.2f\n", orders[i].items[j].name, orders[i].items[j].price);
        }
        printf("Total Amount: $%.2f\n", orders[i].totalAmount);
        printf("--------------------------------------------------\n");
    }
}

void viewsellsreport() {
    float totalSales = 0;

    printf("\n\n******************** SELLS REPORT ********************\n");

    for (int i = 0; i < numOrders; i++) {
        totalSales += orders[i].totalAmount;
    }

    printf("Total Sales: $%.2f\n", totalSales);
}

void viewstockreport() {
    printf("\n\n******************** STOCK REPORT ********************\n");


    printf("Italian Cuisine Stock:\n");
    printf("Pizza: 20\n");
    printf("Pasta: 30\n");
    printf("Lasagna: 15\n");
    printf("Risotto: 10\n");

    printf("\nChinese Cuisine Stock:\n");
    printf("Fried Rice: 25\n");
    printf("Sweet and Sour Chicken: 20\n");
    printf("Kung Pao Chicken: 15\n");
    printf("Wonton Soup: 30\n");

    printf("\nIndian Cuisine Stock:\n");
    printf("Biryani: 10\n");
    printf("Butter Chicken: 25\n");
    printf("Samosa: 50\n");
    printf("Naan: 100\n");
}
