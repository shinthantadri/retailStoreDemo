#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "inventory_management.h"

#define low_threshold_amount 50

// defining callback type for stock operations
typedef void (*StockCallback)(Product *product, void *data, bool *modified);

void processStockFile(const char *filename, StockCallback callback, void *data)
{
  FILE *productFile = fopen(filename, "r");
  FILE *tempFile = fopen("temp.txt", "w");

  if (productFile == NULL || tempFile == NULL)
  {
    printf("Error opening file. Please try again.\n");
    return;
  }

  char line[256];
  bool modified = false;

  while (fgets(line, sizeof(line), productFile))
  {
    Product product;
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%[^,],%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID, product.status);

    // call the callback to perform desired stock operations
    callback(&product, data, &modified);

    if (modified)
    {
      // write the modified product to temp file
      fprintf(tempFile, "%s,%s,%s,%.2f,%d,%s,%s\n", product.productID, product.name, product.categoryID, product.price, product.quantity, product.supplierID, product.status);
      modified = false; // reset for next iteration
    }
    else
    {
      fputs(line, tempFile);
    }
  }

  fclose(productFile);
  fclose(tempFile);

  remove(filename);
  rename("temp.txt", filename);
}

void addStockCallback(Product *product, void *data, bool *modified)
{
  char *productID = (char *)data;

  if (strcmp(productID, product->productID) == 0)
  {
    int amount;
    printf("The current stock of product(%s) with ID %s is %d\n", product->name, product->productID, product->quantity);
    printf("Enter the amount of stock to add: ");
    scanf("%d", &amount);

    product->quantity += amount;
    *modified = true;

    printf("-----------------------Stock successfully updated for product %s-----------------------\n", product->productID);
  }
}

void addStock()
{
  char productID[10];
  printf("Enter the ID of the product to add stock: ");
  scanf(" %s", productID);

  processStockFile("products.txt", addStockCallback, productID);
}

void deleteStockCallback(Product *product, void *data, bool *modified)
{
  char *productID = (char *)data;
  char choice;

  if (strcmp(productID, product->productID) == 0)
  {
    printf("The current stock of product(%s) with ID %s is %d\n", product->name, product->productID, product->quantity);
    printf("Do you want to set it to 0? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y')
    {
      product->quantity = 0;
      *modified = true;

      printf("-----------------------Stock successfully removed for product %s-----------------------\n", product->productID);
    }
    else if (choice == 'n')
    {
      return;
    }
    else
    {
      printf("Invalid option.\n Please try again\n");
    }
  }
}

void deleteStock()
{
  char productID[10];
  printf("Enter the ID of the product to remove stock: ");
  scanf(" %s", productID);
  processStockFile("products.txt", deleteStockCallback, productID);
}

void updateStockCallback(Product *product, void *data, bool *modified)
{
  char *productID = (char *)data;

  if (strcmp(productID, product->productID) == 0)
  {
    int amount;
    printf("The current stock of product(%s) with ID %s is %d\n", product->name, product->productID, product->quantity);
    printf("Enter the amount of stock to update: ");
    scanf("%d", &amount);

    product->quantity = amount;
    *modified = true;

    printf("-----------------------Stock successfully updated for product %s-----------------------\n", product->productID);
  }
}

void updateStock()
{
  char productID[10];
  printf("Enter the ID of the product to update stock: ");
  scanf(" %s", productID);
  processStockFile("products.txt", updateStockCallback, productID);
}

void removeStockCallback(Product *product, void *data, bool *modified)
{
  char *productID = (char *)data;

  if (strcmp(productID, product->productID) == 0)
  {
    int amount = product->quantity + 1;
    printf("The current stock of product(%s) with ID %s is %d\n", product->name, product->productID, product->quantity);

    while (amount > product->quantity)
    {
      printf("Enter the amount of stock to remove: ");
      scanf("%d", &amount);
    }

    product->quantity -= amount;
    *modified = true;

    printf("-----------------------Stock successfully removed for product %s-----------------------\n", product->productID);
  }
}

void removeStock()
{
  char productID[10];
  printf("Enter the ID of the product to remove stock: ");
  scanf(" %s", productID);
  processStockFile("products.txt", removeStockCallback, productID);
}

void alertStock()
{
  printf("These are the products that are low on amount (<=%d).\n", low_threshold_amount);
  FILE *productFile = fopen("products.txt", "r");

  if (productFile == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  char line[256];
  Product product;

  // Table Header
  printf("--------------------------------------------\n");
  printf("| %-10s | %-20s | %-8s |\n", "ProductID", "Product Name", "Quantity");
  printf("--------------------------------------------\n");

  while (fgets(line, sizeof(line), productFile))
  {
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%[^,],%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID, product.status);
    if (product.quantity <= low_threshold_amount)
    {
      printf("| %-10s | %-20s | %-8d |\n", product.productID, product.name, product.quantity);
    }
  }
  printf("---------------------------------------------\n");
  fclose(productFile);
}

void generateInventoryReport()
{
  // Table Header
  printf("------------------------------------------------------------------------------------------\n");
  printf("%-10s | %-15s | %-10s | %-15s \n", "ProductID", "Product_Name", "Current Stock", "Status");
  printf("------------------------------------------------------------------------------------------\n");

  FILE *productFile = fopen("products.txt", "r");

  if (productFile == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  char line[256];
  Product product;
  while (fgets(line, sizeof(line), productFile))
  {
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%[^,],%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID, product.status);
    printf("| %-10s | %-15s | %-10d | %-15s \n", product.productID, product.name, product.quantity, product.status);
  }
  printf("--------------------------------------------------------------------------------------\n");
  fclose(productFile);
}

void generateActive()
{
  // Table Header
  printf("------------------------------------------------------------------------------------------\n");
  printf("%-10s | %-15s | %-10s\n", "ProductID", "Product_Name", "Current Stock");
  printf("------------------------------------------------------------------------------------------\n");

  FILE *productFile = fopen("products.txt", "r");

  if (productFile == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  char line[256];
  Product product;
  while (fgets(line, sizeof(line), productFile))
  {
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%[^,],%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID, product.status);

    if (strcmp(product.status, "active") == 0)
    {
      printf("| %-10s | %-15s | %-10d |\n", product.productID, product.name, product.quantity);
    }
  }
  printf("--------------------------------------------------------------------------------------\n");
  fclose(productFile);
}

void generateDiscontinued()
{
  // Table Header
  printf("------------------------------------------------------------------------------------------\n");
  printf("%-10s | %-15s | %-10s\n", "ProductID", "Product_Name", "Current Stock");
  printf("------------------------------------------------------------------------------------------\n");

  FILE *productFile = fopen("products.txt", "r");

  if (productFile == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  char line[256];
  Product product;
  while (fgets(line, sizeof(line), productFile))
  {
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%[^,],%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID, product.status);

    if (strcmp(product.status, "discontinued") == 0)
    {
      printf("| %-10s | %-15s | %-10d |\n", product.productID, product.name, product.quantity);
    }
  }
  printf("--------------------------------------------------------------------------------------\n");
  fclose(productFile);
}

void stock_management()
{
  int stock_choice;
  do
  {
    printf("Stock management selected.\n");
    printf("1. Add stock\n2. Remove stock\n3. Update stock\n4. delete stock(set it to 0)\n5. Alert low stock products\n6. Custom threshold Management\n7. Inventory Report All Products\n8. Inventory Report Active Products\n9. Inventory Report Discontinued Products\n10. Exit to main menu\n Please enter your choice: ");
    scanf("%d", &stock_choice);

    switch (stock_choice)
    {
    case 1:
      addStock();
      break;

    case 2:
      removeStock();
      break;

    case 3:
      updateStock();
      break;

    case 4:
      deleteStock();
      break;

    case 5:
      alertStock();
      break;

      // case 6:
      //   customThreshold();
      //   break;

    case 7:
      generateInventoryReport();
      break;

    case 8:
      generateActive();
      break;

    case 9:
      generateDiscontinued();
      break;

    case 10:
      printf("Returning to the main menu...\n");
      break;

    default:
      printf("Invalid option. Please try again.\n");
      break;
    }
  } while (stock_choice != 10);
}