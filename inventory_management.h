#ifndef INVENTORY_MANAGEMENT_H
#define INVENTORY_MANAGEMENT_H

#include "common.h"

// Function prototypes
void stock_management();
void addStock();
void removeStock();
void updateStock();
void deleteStock();
void alertStock();
void generateInventoryReport();
void generateActive();
void generateDiscontinued();

// Callback type for stock operations
typedef void (*StockCallback)(Product *product, void *data, bool *modified);

// Helper functions
void processStockFile(const char *filename, StockCallback callback, void *data);
void addStockCallback(Product *product, void *data, bool *modified);
void deleteStockCallback(Product *product, void *data, bool *modified);
void updateStockCallback(Product *product, void *data, bool *modified);
void removeStockCallback(Product *product, void *data, bool *modified);

#endif