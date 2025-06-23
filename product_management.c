#include "product_management.h"

void product_management()
{
  int product_option;

  do
  {
    printf("Product Management selected.\n1. Add Product\n2. Update Product\n3. Delete Product\n4. View Products\n5. Filter by Category\n6. Filter by Supplier\n7. Back to Main Menu\nWhat would you like to do?: ");
    scanf("%d", &product_option);

    switch (product_option)
    {
    case 1:
      addProduct();
      break;

    case 2:
      updateProduct();
      break;

    case 3:
      deleteProduct();
      break;

    case 4:
      viewProducts();
      break;

    case 5:
      filterproductbycategory();
      break;

    case 6:
      filterproductbysupplier();
      break;

    case 7:
      printf("Returning to Main Menu...\n");
      break;

    default:
      printf("Invalid option. Please try again.\n");
      break;
    }
  } while (product_option != 7);
}

bool productIdExist(char *productId)
{
  FILE *pFile = fopen("products.txt", "r");
  char line[256];
  Product p;

  while (fgets(line, sizeof(line), pFile))
  {
    sscanf(line, "%[^,],", p.productID);

    if (strcmp(productId, p.productID) == 0)
    {
      fclose(pFile);
      return false;
    }
  }

  fclose(pFile);
  return true;
}

bool categoryIdExist(char *categoryId)
{
  FILE *cFile = fopen("category.txt", "r");
  char line[256];

  Category c;
  while (fgets(line, sizeof(line), cFile))
  {
    sscanf(line, "%[^,],", c.categoryID);

    if (strcmp(categoryId, c.categoryID) == 0)
    {
      fclose(cFile);
      return true;
    }
  }

  fclose(cFile);
  return false;
}

bool supplierIdExist(char *supplierId)
{
  FILE *sFile = fopen("supplier.txt", "r");
  char line[256];

  Supplier s;
  while (fgets(line, sizeof(line), sFile))
  {
    sscanf(line, "%[^,],", s.supplierID);

    if (strcmp(supplierId, s.supplierID) == 0)
    {
      fclose(sFile);
      return true;
    }
  }

  fclose(sFile);
  return false;
}

void addProduct()
{
  Product newProduct;

  printf("Enter product id: ");
  scanf(" %s", newProduct.productID);

  if (!productIdExist(newProduct.productID))
  {
    printf("-----------------Product Id already Exist. Please choose another one.------------------\n");
    return;
  }

  printf("Enter product name (Please do not use spaces as the system is not designed for it, use _ instead): ");
  scanf(" %s", newProduct.name);

  printf("Enter quantity: ");
  scanf("%d", &newProduct.quantity);

  printf("Enter categoryID: ");
  scanf(" %s", newProduct.categoryID);

  if (!categoryIdExist(newProduct.categoryID))
  {
    printf("Category ID does not exist. Please try again.\n");
    return;
  }

  printf("Enter supplierID: ");
  scanf(" %s", newProduct.supplierID);

  if (!supplierIdExist(newProduct.supplierID))
  {
    printf("Supplier ID does not exist. Please try again.\n");
    return;
  }

  printf("Enter product price: ");
  scanf("%f", &newProduct.price);

  strcpy(newProduct.status, "active");

  // open the products.txt file and add the product
  FILE *file = fopen("products.txt", "a");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  fprintf(file, "%s,%s,%s,%.2f,%d,%s,%s\n", newProduct.productID, newProduct.name, newProduct.categoryID, newProduct.price, newProduct.quantity, newProduct.supplierID, newProduct.status);
  printf("Product added successfully.\n");
  fclose(file);
}

void deleteProduct()
{
  char productIDToDelete[10];
  bool found = false;

  printf("Enter the id of product you want to delete: ");
  scanf(" %s", productIDToDelete);

  FILE *file = fopen("products.txt", "r");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  FILE *temp = fopen("temp.txt", "w");

  char line[256];

  while (fgets(line, sizeof(line), file))
  {
    char current_id[10];
    sscanf(line, "%[^,]", current_id);

    if (strcmp(productIDToDelete, current_id) == 0)
    {
      found = true;
      continue;
    }

    fputs(line, temp);
  }

  fclose(temp);
  fclose(file);

  if (found)
  {
    remove("products.txt");
    rename("temp.txt", "products.txt");

    printf("The product with id %s has been successfully deleted!\n", productIDToDelete);
  }
  else
  {
    remove("temp.txt");
    printf("The product ID does not exist. Please try again");
  }
}

void updateProduct()
{
  char productIDToUpdate[10];
  bool found = false;

  printf("Enter the ID of the product you want to update: ");
  scanf(" %s", productIDToUpdate);

  FILE *file = fopen("products.txt", "r");
  if (file == NULL)
  {
    printf("Error opening file,\n");
    return;
  }

  FILE *temp = fopen("temp.txt", "w");

  Product product;
  char line[256];

  while (fgets(line, sizeof(line), file))
  {
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%[^,],%s", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID, product.status);

    if (strcmp(productIDToUpdate, product.productID) == 0)
    {
      found = true;

      int choice;
      printf("1. Product ID\n2. Name\n3. CategoryID\n4. Price\n5. Quantity\n6. SupplierID\n7. Status\n8. Exit to main menu\nPlease enter your choice: ");
      scanf("%d", &choice);

      switch (choice)
      {
      case 1:
        printf("Enter the new ID: ");
        scanf(" %s", product.productID);

        if (!productIdExist(product.productID))
        {
          printf("-----------------Product Id already Exist. Please choose another one.------------------\n");
          break;
        }
        break;

      case 2:
        printf("Enter the new name: ");
        scanf(" %s", product.name);
        break;

      case 3:
        printf("Enter the new category ID: ");
        scanf(" %s", product.categoryID);
        if (!categoryIdExist(product.categoryID))
        {
          printf("Category ID does not exist. Please try again.\n");
          break;
        }
        break;

      case 4:
        printf("Enter the new price: ");
        scanf("%f", &product.price);
        break;

      case 5:
        printf("Enter new quantity ");
        scanf("%d", &product.quantity);
        break;

      case 6:
        printf("Enter the new supplier ID: ");
        scanf(" %s", product.supplierID);
        if (!supplierIdExist(product.supplierID))
        {
          printf("Supplier ID does not exist. Please try again.\n");
          break;
        }
        break;

      case 7:
        printf("Enter the product status(active/discontinued) - case sensitive : ");
        scanf(" %s", product.status);
        if (strcmp(product.status, "discontinued") == 0)
        {
          product.quantity = 0;
        };
        break;

      case 8:
        printf("Exiting to Menu...");
        fclose(file);
        fclose(temp);
        remove("temp.txt");
        return;
      }

      fprintf(temp, "%s,%s,%s,%.2f,%d,%s,%s\n", product.productID, product.name, product.categoryID, product.price, product.quantity, product.supplierID, product.status);
      continue;
    }
    fputs(line, temp);
  }

  fclose(file);
  fclose(temp);

  if (found)
  {
    remove("products.txt");
    rename("temp.txt", "products.txt");
    printf("--------------The product has been successfully updated!-------------\n");
  }
  else
  {
    remove("temp.txt");
    printf("Error: The product ID does not exist. Please try again.\n");
  }
}

void viewProducts()
{
  Product product;
  char line[256];

  FILE *file = fopen("products.txt", "r");

  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  // Table Header
  printf("------------------------------------------------------------------------------------------\n");
  printf("| %-8s | %-20s | %-10s | %-8s | %-8s | %-10s | %-15s |\n",
         "ItemID", "Name", "CategoryID", "Price", "Stock", "SupplierID", "Status");
  printf("------------------------------------------------------------------------------------------\n");

  while (fscanf(file, "%[^,],%[^,],%[^,],%f,%d,%[^,],%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID, product.status) != EOF)
  {
    printf("| %-8s | %-20s | %-10s | %8.2f | %-8d | %-10s | %-15s |\n",
           product.productID,
           product.name,
           product.categoryID,
           product.price,
           product.quantity,
           product.supplierID,
           product.status);
  }
  printf("------------------------------------------------------------------------------------------\n");

  fclose(file);
}

void filterproductbycategory()
{
  char categoryID[10];
  Product p;
  char line[256];
  int found = 0;

  printf("Enter Category ID to filter (e.g 01): ");
  scanf("%s", categoryID);

  FILE *pr = fopen("products.txt", "r");
  if (!pr)
  {
    printf("Error opening file!");
    return;
  }

  printf("------------------------------------------------------------------------------------------\n");
  printf("| %-8s | %-20s | %-10s | %-8s | %-8s | %-10s | %-15s |\n", "ItemID", "Name", "CategoryID", "Price", "Stock", "SupplierID", "Status");
  printf("------------------------------------------------------------------------------------------\n");

  while (fgets(line, sizeof(line), pr))
  {
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%[^,],%s", p.productID, p.name, p.categoryID, &p.price, &p.quantity, p.supplierID, p.status);

    if (strcmp(p.categoryID, categoryID) == 0)
    {
      printf("| %-8s | %-20s | %-10s | %8.2f | %-8d | %-10s | %-15s |\n", p.productID, p.name, p.categoryID, p.price, p.quantity, p.supplierID, p.status);
      found = 1;
    }
  }

  if (!found)
  {
    printf("Nothing found!");
  }
  fclose(pr);
  printf("Press Enter to return...");
  getchar();
  getchar();
}

void filterproductbysupplier()
{
  char supplierID[10];
  Product p;
  char line[256];
  int found = 0;

  printf("Enter Supplier ID to filter (e.g 101): ");
  scanf("%s", supplierID);

  FILE *pr = fopen("products.txt", "r");
  if (!pr)
  {
    printf("Error opening file!");
    return;
  }

  printf("------------------------------------------------------------------------------------------\n");
  printf("| %-8s | %-20s | %-10s | %-8s | %-8s | %-10s | %-15s |\n", "ItemID", "Name", "CategoryID", "Price", "Stock", "SupplierID", "Status");
  printf("------------------------------------------------------------------------------------------\n");

  while (fgets(line, sizeof(line), pr))
  {
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%[^,],%s", p.productID, p.name, p.categoryID, &p.price, &p.quantity, p.supplierID, p.status);

    if (strcmp(p.supplierID, supplierID) == 0)
    {
      printf("| %-8s | %-20s | %-10s | %8.2f | %-8d | %-10s | %-15s |\n", p.productID, p.name, p.categoryID, p.price, p.quantity, p.supplierID, p.status);
      found = 1;
    }
  }

  if (!found)
  {
    printf("Nothing found!");
  }
  fclose(pr);
  printf("Press Enter to return...");
  getchar();
  getchar();
}