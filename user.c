#include "user.h"

void user()
{
  int user_choice;
  do
  {
    printf("1. Login\n2. New user? Register now!\n3. Back to main menu\nPlease choose an option: ");
    scanf("%d", &user_choice);
    switch (user_choice)
    {
    case 1:
      user_login();
      break;
    case 2:
      user_register();
      break;
    case 3:
      printf("Returning to main menu...\n");
      break;
    default:
      printf("Invalid option. Please try again\n");
      break;
    }
  } while (user_choice != 3);
}

void user_register()
{
  char username[20], contact[20], email[50];
  int password;
  printf("Enter username: ");
  scanf(" %s", username);
  printf("Please enter 3 digit password (cannot start with 0): ");
  scanf("%d", &password);
  printf("Enter contact number: ");
  scanf(" %s", contact);
  printf("Enter email address: ");
  scanf(" %s", email);
  FILE *userFile = fopen("users.txt", "a");
  if (userFile == NULL)
  {
    printf("Error opening file. Please try again.");
    return;
  }
  fprintf(userFile, "%s,%d,%s,%s\n", username, password, contact, email);
  printf("Registerred successfully!\n");
  fclose(userFile);
}

void user_login()
{
  char login_username[20];
  int login_password;
  printf("Enter your username: ");
  scanf(" %s", login_username);
  printf("Enter password (3 digits): ");
  scanf("%d", &login_password);
  User user;
  char line[256];
  FILE *userFile = fopen("users.txt", "r");
  if (userFile == NULL)
  {
    printf("Error opening file. Please try again.\n");
    return;
  }
  while (fgets(line, sizeof(line), userFile))
  {
    sscanf(line, "%[^,],%d,%[^,],%s\n", user.username, &user.password, user.contact, user.email);
    if (strcmp(login_username, user.username) == 0 && login_password == user.password)
    {
      printf("Login successful!\n");
      fclose(userFile);
      user_functions(&user);
      return;
    }
  }
  printf("Wrong username or password. Please try again.\n");
  fclose(userFile);
}

void user_functions(User *user)
{
  int user_choice;
  do
  {
    printf("1. Place an order\n2. Check unpaid orders\n3. Update user information\n4. Exit to main menu\nPlease choose an option: ");
    scanf("%d", &user_choice);
    switch (user_choice)
    {
    case 1:
      placeOrder(user);
      break;
    case 2:
      checkUnpaidOrders(user);
      break;
    case 3:
      updateInformation(user);
      break;
    case 4:
      printf("Returning to main menu...\n");
      break;
    default:
      printf("Invalid choice, Please try again.\n");
      break;
    }
  } while (user_choice != 4);
}

int getNextTransactionID()
{
  FILE *file = fopen("last_transaction_id.txt", "r+");
  int id = 1000;
  if (file == NULL)
  {
    file = fopen("last_transaction_id.txt", "w+");
    if (file == NULL)
    {
      printf("Error opening transaction ID file.\n");
      return -1;
    }
  }
  else
  {
    fscanf(file, "%d", &id);
  }
  id++;
  rewind(file);
  fprintf(file, "%d", id);
  fclose(file);
  return id;
}

void placeOrder(User *user)
{
  float total = 0;
  int choice;
  char productID[10];
  Product product;
  bool found = false;
  int quantity;
  char line[256];
  char paidStatus[10];
  int paid;
  char date[20];
  int transactionID;

  time_t t = time(NULL);
  struct tm *currentTime = localtime(&t);
  sprintf(date, "%02d-%02d-%04d", currentTime->tm_mday, currentTime->tm_mon + 1, currentTime->tm_year + 1900);

  do
  {
    printf("1. Add item\n2. Checkout\n3. Return to menu\nPlease choose an option: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      printf("Enter product ID: ");
      scanf(" %s", productID);
      FILE *productsFile = fopen("products.txt", "r");
      FILE *tempFile = fopen("temp.txt", "w");
      if (productsFile == NULL || tempFile == NULL)
      {
        printf("Error opening file. Please try again.\n");
        return;
      }
      bool insufficientStock = false;
      while (fgets(line, sizeof(line), productsFile))
      {
        sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%[^,],%s", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID, product.status);
        if (strcmp(productID, product.productID) == 0 && strcmp(product.status, "active") == 0)
        {
          found = true;
          printf("Enter quantity: ");
          scanf("%d", &quantity);
          if (quantity > product.quantity)
          {
            printf("Please order with less quantity.\n");
            insufficientStock = true;
            break;
          }
          total += product.price * quantity;
          product.quantity -= quantity;
          fprintf(tempFile, "%s,%s,%s,%.2f,%d,%s,%s\n", product.productID, product.name, product.categoryID, product.price, product.quantity, product.supplierID, product.status);
        }
        else
        {
          fputs(line, tempFile);
        }
      }
      fclose(productsFile);
      fclose(tempFile);
      if (!found)
      {
        remove("temp.txt");
        printf("The product ID does not exist or it was discontinued. Please try again.\n");
      }
      else if (insufficientStock)
      {
        printf("Insufficient stock. Cart not updated.\n");
      }
      else
      {
        remove("products.txt");
        rename("temp.txt", "products.txt");
        printf("Item successfully added to cart.\n");
      }
      break;
    case 2:
      if (!total)
      {
        printf("Please add an item first to checkout.\n");
        return;
      }
      transactionID = getNextTransactionID();
      printf("Total amount is %.2f\n", total);
      printf("Do you want to pay now? (Enter 1 to pay now or 0 to pay later): ");
      scanf("%d", &paid);
      if (paid)
      {
        strcpy(paidStatus, "Paid");
      }
      else
      {
        strcpy(paidStatus, "Unpaid");
      }
      FILE *transactionsFile = fopen("transactions.txt", "a");
      if (transactionsFile == NULL)
      {
        printf("Error opening file. Please try again.\n");
        return;
      }
      fprintf(transactionsFile, "%d,%s,%.2f,%s,%s\n", transactionID, user->username, total, paidStatus, date);
      printf("Transaction successfully recorded.\n");
      fclose(transactionsFile);
      break;
    case 3:
      if (total != 0)
      {
        printf("Please checkout first.\n");
        break;
      }
      printf("Returning to main menu...\n");
      return;
    default:
      printf("Invalid option. Please try again.\n");
      break;
    }
  } while (choice != 2);
}

void checkUnpaidOrders(User *user)
{
  printf("Please wait while we check for your unpaid orders...\n");
  bool haveUnpaid = false;
  FILE *file = fopen("transactions.txt", "r");
  if (file == NULL)
  {
    printf("Error opening file. Please try again.\n");
    return;
  }
  char line[256];
  typedef struct
  {
    int transactionID;
    char username[20];
    float total;
    char paidStatus[10];
    char date[50];
  } Transaction;
  Transaction curTransaction;
  printf("\n%-15s %-15s %-15s %-10s\n", "Transaction ID", "Total Amount (RM)", "Status", "Date");
  printf("--------------------------------------------------------------\n");
  while (fgets(line, sizeof(line), file))
  {
    sscanf(line, "%d,%[^,],%f,%[^,],%s\n", &curTransaction.transactionID, curTransaction.username, &curTransaction.total, curTransaction.paidStatus, curTransaction.date);
    if (strcmp(user->username, curTransaction.username) == 0 && strcmp(curTransaction.paidStatus, "Unpaid") == 0)
    {
      haveUnpaid = true;
      printf("%-15d %-15.2f %-15s %-10s\n", curTransaction.transactionID, curTransaction.total, curTransaction.paidStatus, curTransaction.date);
    }
  }
  fclose(file);
  if (!haveUnpaid)
  {
    printf("You have no UNPAID orders for now.\n");
  }
}

void updateInformation(User *user)
{
  int choice;
  FILE *userFile = fopen("users.txt", "r");
  FILE *tempFile = fopen("temp.txt", "w");
  bool modified = false;
  if (userFile == NULL || tempFile == NULL)
  {
    printf("Error opening file. Please try again.\n");
    return;
  }
  char line[256];
  char currentUsername[20];
  while (fgets(line, sizeof(line), userFile))
  {
    sscanf(line, "%[^,]", currentUsername);
    if (strcmp(currentUsername, user->username) == 0)
    {
      printf("1. Username\n2. Password\n3. Contact Number\n4. Email address\n5. Exit to menu\nChoose which one to update: ");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        printf("Enter new username: ");
        scanf(" %s", user->username);
        break;
      case 2:
        printf("Enter new password (3 digit pin and cannot start with 0): ");
        scanf("%d", &user->password);
        break;
      case 3:
        printf("Enter new contact number: ");
        scanf(" %s", user->contact);
        break;
      case 4:
        printf("Enter new email address: ");
        scanf(" %s", user->email);
        break;
      case 5:
        printf("Returing to menu...\n");
        break;
      default:
        printf("Invalid option. Please try again\n");
        break;
      }
      fprintf(tempFile, "%s,%d,%s,%s\n", user->username, user->password, user->contact, user->email);
      modified = true;
    }
    else
    {
      fputs(line, tempFile);
    }
  }
  fclose(userFile);
  fclose(tempFile);
  if (modified)
  {
    remove("users.txt");
    rename("temp.txt", "users.txt");
    printf("Information successfully updated!\n");
  }
  else
  {
    remove("temp.txt");
    printf("No changeds were made.\n");
  }
}
