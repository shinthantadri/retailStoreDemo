#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define low_threshold_amount 50

// Product struct
typedef struct
{
  char productID[10];
  char name[50];
  char categoryID[10];
  float price;
  int quantity;
  char supplierID[10];
  char status[20];
} Product;

typedef struct
{
  char categoryID[5];
  char categoryName[50];
} Category;

typedef struct
{
  char supplierID[5];
  char suppliername[50];
  char contact[50];
} Supplier;

typedef struct
{
  char username[20];
  char contact[100];
  char email[50];
  int password;
} User;

typedef struct
{
  int transactionID;
  char username[20];
  float total;
  char paidStatus[10];
  char date[50];
} Transaction;

#endif