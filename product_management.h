#ifndef PRODUCT_MANAGEMENT_H
#define PRODUCT_MANAGEMENT_H

#include "common.h"

// Function prototypes
void product_management();
void addProduct();
void viewProducts();
void deleteProduct();
void updateProduct();
void filterproductbycategory();
void filterproductbysupplier();

// Helper functions
bool productIdExist(char *productId);
bool categoryIdExist(char *categoryId);
bool supplierIdExist(char *supplierId);

#endif