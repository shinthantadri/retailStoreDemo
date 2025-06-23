#include <stdio.h>
#include <stdlib.h>

#include "product_management.h"
#include "inventory_management.h"
#include "category_supplier.h"
#include "transaction_management.h"
#include "user.h"

void printWelcomeMessage()
{
  printf("\n");
  printf("******************************************************\n");
  printf("*                                                    *\n");
  printf("*        W E L C O M E   T O   T H E                 *\n");
  printf("*                                                    *\n");
  printf("*          A P U   R E T A I L   S T O R E           *\n");
  printf("*                                                    *\n");
  printf("******************************************************\n");
  printf("\n");
}

void system_manager()
{
  char username[20], admin[20];
  int password, adminPassword;

  printf("Enter username: ");
  scanf(" %s", username);

  printf("Enter password: ");
  scanf("%d", &password);

  FILE *file = fopen("managers.txt", "r");
  if (file == NULL)
  {
    printf("Error opening file. Please try again.\n");
    return;
  }

  fscanf(file, "%[^,],%d\n", admin, &adminPassword);
  if (strcmp(username, admin) == 0 && password == adminPassword)
  {
    printf("Login successful!\n");

    int option;

    do
    {
      printf("1. Product Management\n2. Inventory Management\n3. Category and Supplier Management\n4. Transaction Management\n5. Exit to menu\nPlease choose your option: ");
      scanf("%d", &option);

      switch (option)
      {
      case 1:
        product_management();
        break;

      case 2:
        stock_management();
        break;

      case 3:
        category_supplier_management();
        break;

      case 4:
        transaction_management();
        break;

      case 5:
        printf("Returning to main menu...\n");
        return;

      default:
        printf("Invalid option. Please try again.\n");
        break;
      }
    } while (option != 5);
  }
  else
  {
    printf("Wrong username or password. Please try again.\n");
    return;
  }
}

int main()
{
  int main_menu_option;

  do
  {
    printWelcomeMessage();
    printf("1. User\n2. System manager\n3. Exit\nHow would you like to proceed?: ");
    scanf("%d", &main_menu_option);

    switch (main_menu_option)
    {
    case 1:
      user();
      break;

    case 2:
      system_manager();
      break;

    case 3:
      printf("Exiting the program. Goodbye!\n");
      return 0;

    default:
      printf("Invalid option. Please try again.\n");
      break;
    }

  } while (main_menu_option != 3);
  return 0;
}