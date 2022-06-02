#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "queue.h"

void createCustomerList(customerList,int,int,int);
void sortList(customerList);
void swap(customer, customer);
void defineCustomer(int, int, int *, int *, int *, int *, char *, char *);
void toList(customerList,struct customerInfo);

#endif // LIST_H_INCLUDED
