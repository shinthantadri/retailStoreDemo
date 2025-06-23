#include "transaction_management.h"

void transaction_management()
{
  int choice;
  do
  {
    printf("\nTranscation Management Menu\n");
    printf("1. View Transcations\n");
    printf("2. Delete Transaation\n");
    printf("3. Update Transaction\n");
    printf("4. Back to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      view_transaction();
      break;
    case 2:
      delete_transaction();
      break;
    case 3:
      update_transaction();
      break;
    case 4:
      printf("Returning to main menu...\n");
      break;
    default:
      printf("Invalid option. try again please\n");
    }
  } while (choice != 4);
}

void view_transaction()
{
  FILE *tr = fopen("transactions.txt", "r");
  if (!tr)
  {
    printf("Error opening the file!\n");
    return;
  }
  char line[265];
  Transaction t;
  printf("----------------------------------------------------------------------------\n");
  printf("| %-13s | %-15s | %-15s | %-15s | %-15s |\n", "TransactionID", "Name", "Total", "Status", "Date");
  printf("----------------------------------------------------------------------------\n");
  while (fgets(line, sizeof(line), tr))
  {
    sscanf(line, "%d,%[^,],%f,%[^,],%s\n", &t.transactionID, t.username, &t.total, t.paidStatus, t.date);
    printf("| %-13d | %-15s | %10.2f | %-15s | %-15s |\n", t.transactionID, t.username, t.total, t.paidStatus, t.date);
  }
  fclose(tr);
  printf("\nPress Enter to return to the menu...");
  getchar();
  getchar();
}

void delete_transaction()
{
  char line[256];
  int id, currentID;
  int found = 0;
  printf("Enter Transaction ID to delete: ");
  scanf("%d", &id);
  FILE *tr = fopen("transactions.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  if (!tr || !temp)
  {
    printf("Error opening the file\n");
    return;
  }
  while (fgets(line, sizeof(line), tr))
  {
    sscanf(line, "%d,", &currentID);
    if (id == currentID)
    {
      found = 1;
      continue;
    }
    fputs(line, temp);
  }
  fclose(tr);
  fclose(temp);
  if (found)
  {
    remove("transactions.txt");
    rename("temp.txt", "transactions.txt");
    printf("Deleted successfully!\n");
  }
  else
  {
    remove("temp.txt");
    printf("TransactionID not found!\n");
  }
}

void update_transaction()
{
  char line[256];
  int found = 0, id;
  Transaction t;
  printf("Enter TranscationID to update: ");
  scanf("%d", &id);
  FILE *tr = fopen("transactions.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  if (!tr || !temp)
  {
    printf("Error opening the file\n");
    return;
  }
  while (fgets(line, sizeof(line), tr))
  {
    sscanf(line, "%d,%[^,],%f,%d,%s\n", &t.transactionID, t.username, &t.total, &t.paidStatus, t.date);
    if (t.transactionID == id)
    {
      printf("Enter new status (Paid/Unpaid): ");
      scanf(" %s", t.paidStatus);
      found = 1;
    }
    fprintf(temp, "%d,%s,%.2f,%s,%s\n", t.transactionID, t.username, t.total, t.paidStatus, t.date);
  }
  fclose(tr);
  fclose(temp);
  if (found)
  {
    remove("transactions.txt");
    rename("temp.txt", "transactions.txt");
    printf("Updated successfully!\n");
  }
  else
  {
    remove("temp.txt");
    printf("TransactionID not found!\n");
  }
}
