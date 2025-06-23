#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "product_management.h"

#include "common.h"

void user();
void user_login();
void user_register();
void user_functions(User *user);
void placeOrder(User *user);
void checkUnpaidOrders(User *user);
void updateInformation(User *user);
int getNextTransactionID();

#endif
