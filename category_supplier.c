#include "category_supplier.h"

void category_supplier_management()
{
  int choice;
  do
  {
    printf("\nCategory and Supplier Management\n");
    printf("1.Add Category\n2.View Categories\n3.Update Category\n4.Delete Category\n");
    printf("5.Add Supplier\n6.View Suppliers\n7.Update Supplier\n8.Delete Supplier\n9.Back to main manu\n");
    printf("Choose your option: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      addcategory();
      break;
    case 2:
      viewcategories();
      break;
    case 3:
      updatecategory();
      break;
    case 4:
      deletecategory();
      break;
    case 5:
      addsupplier();
      break;
    case 6:
      viewsupplier();
      break;
    case 7:
      updatesupplier();
      break;
    case 8:
      deletesupplier();
      break;
    case 9:
      printf("Returning to main menu...\n");
      break;
    default:
      printf("Invalid option,please try again!\n");
    }
  } while (choice != 9);
}

void addcategory()
{
  Category ct;
  printf("Enter Category ID: ");
  scanf("%s", ct.categoryID);
  printf("Enter Category Name: ");
  scanf("%s", ct.categoryName);
  FILE *c = fopen("category.txt", "a");
  if (!c)
  {
    printf("Unable to open the file!\n");
    return;
  }
  fprintf(c, "%s,%s\n", ct.categoryID, ct.categoryName);
  fclose(c);
  printf("Category added succesfully!\n");
}

void viewcategories()
{
  Category ct;
  char line[100];
  FILE *c = fopen("category.txt", "r");
  if (!c)
  {
    printf("Unable to open this file!\n");
    return;
  }
  printf("-------- Category List --------\n");
  printf("%-10s | %-20s\n", "ID", "Name");
  printf("-------------------------------\n");
  while (fgets(line, sizeof(line), c))
  {
    sscanf(line, "%[^,],%s", ct.categoryID, ct.categoryName);
    printf("%-10s | %-20s\n", ct.categoryID, ct.categoryName);
  }
  fclose(c);
  printf("\nPress Enter to return to the menu...");
  getchar();
  getchar();
}

void deletecategory()
{
  char id[5], line[100], currentid[10];
  int found = 0;
  printf("Enter category ID to delete: ");
  scanf("%s", id);
  FILE *c = fopen("category.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  if (!c || !temp)
  {
    printf("File error\n");
    return;
  }
  while (fgets(line, sizeof(line), c))
  {
    sscanf(line, "%[^,]", currentid);
    if (strcmp(id, currentid) == 0)
    {
      found = 1;
      continue;
    }
    fputs(line, temp);
  }
  fclose(c);
  fclose(temp);
  if (found)
  {
    remove("category.txt");
    rename("temp.txt", "category.txt");
    printf("Category deleted succesfully!\n");
  }
  else
  {
    remove("temp.txt");
    printf("Category was not found!\n");
  }
}

void updatecategory()
{
  char id[5], newname[50], line[100];
  int found = 0;
  Category ct;
  printf("Enter Category ID to update: ");
  scanf(" %s", id);
  FILE *c = fopen("category.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  if (!c || !temp)
  {
    printf("file error\n");
    return;
  }
  while (fgets(line, sizeof(line), c))
  {
    sscanf(line, "%[^,],%s", ct.categoryID, ct.categoryName);
    if (strcmp(id, ct.categoryID) == 0)
    {
      printf("Enter new Category Name: ");
      scanf("%s", &newname);
      fprintf(temp, "%s,%s\n", ct.categoryID, newname);
      found = 1;
    }
    else
    {
      fputs(line, temp);
    }
  }
  fclose(c);
  fclose(temp);
  if (found)
  {
    remove("category.txt");
    rename("temp.txt", "category.txt");
    printf("Category updated succesfully");
  }
  else
  {
    remove("temp.txt");
    printf("Category ID not found!\n");
  }
}

void addsupplier()
{
  Supplier s;
  printf("Enter Supplier ID : ");
  scanf(" %s", s.supplierID);
  printf("Enter Supplier Name : ");
  scanf(" %s", s.suppliername);
  printf("Enter the contact number: ");
  scanf(" %s", s.contact);
  FILE *sp = fopen("supplier.txt", "a");
  if (!sp)
  {
    printf("Error open file!\n");
    return;
  }
  fprintf(sp, "%s,%s,%s\n", s.supplierID, s.suppliername, s.contact);
  fclose(sp);
  printf("Supplier added succesfully");
}

void viewsupplier()
{
  Supplier s;
  char line[100];
  FILE *sp = fopen("supplier.txt", "r");
  if (!sp)
  {
    printf("Error open file\n");
    return;
  }
  printf("-------- Supplier List --------\n");
  printf("%-10s | %-20s | %-30s\n", "ID", "Name", "Contact");
  printf("--------------------------------------------------------------\n");
  while (fgets(line, sizeof(line), sp))
  {
    sscanf(line, "%[^,],%[^,],%s", s.supplierID, s.suppliername, s.contact);
    printf("%-10s | %-20s | %-30s\n", s.supplierID, s.suppliername, s.contact);
  }
  fclose(sp);
  printf("Press enter to return menu....");
  getchar();
  getchar();
}

void deletesupplier()
{
  char id[10], line[100], currentID[10];
  int found = 0;
  printf("Enter the Supplier ID to delete: ");
  scanf(" %s", id);
  FILE *sp = fopen("supplier.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  if (!sp || !temp)
  {
    printf("Error open file!");
    return;
  }
  while (fgets(line, sizeof(line), sp))
  {
    sscanf(line, "%[^,]", currentID);
    if (strcmp(id, currentID) == 0)
    {
      found = 1;
      continue;
    }
    fputs(line, temp);
  }
  fclose(sp);
  fclose(temp);
  if (found)
  {
    remove("supplier.txt");
    rename("temp.txt", "supplier.txt");
    printf("Supplier deleted successfully\n");
  }
  else
  {
    remove("temp.txt");
    printf("Supplier not found!");
  }
}

void updatesupplier()
{
  char id[10], newspname[50], newcontact[50], line[100];
  int found = 0;
  Supplier s;
  printf("Enter Supplier id to update: ");
  scanf(" %s", id);
  FILE *sp = fopen("supplier.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  if (!sp || !temp)
  {
    printf("Error to open the file\n");
    return;
  }
  while (fgets(line, sizeof(line), sp))
  {
    sscanf(line, "%[^,],%[^,], %s", s.supplierID, s.suppliername, s.contact);
    if (strcmp(id, s.supplierID) == 0)
    {
      printf("Enter new supplier name: ");
      scanf(" %s", newspname);
      printf("Enter new supplier contct: ");
      scanf(" %s", newcontact);
      fprintf(temp, "%s,%s,%s\n", s.supplierID, newspname, newcontact);
      found = 1;
    }
    else
    {
      fputs(line, temp);
    }
  }
  fclose(sp);
  fclose(temp);
  if (found)
  {
    remove("supplier.txt");
    rename("temp.txt", "supplier.txt");
    printf("Supplier update succesfully");
  }
  else
  {
    remove("temp.txt");
    printf("Supplier ID not found!\n");
  }
}
