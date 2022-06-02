#include<stdlib.h>
#include<stdio.h>
#include "list.h"
#include<string.h>

void defineCustomer(int maxPurchaseTime, int maxDeliveryTime, int *purchaseTime, int *deliveryStartTime, int *deliveryTime, int *courierID, char *deliveryType, char *amountOfPurchase) {
//to define a list, come up with random stats
    int decision;

    *courierID = 0;
    *deliveryStartTime = 0;
    *deliveryTime = rand()%maxDeliveryTime+1;
    *purchaseTime = rand()%maxPurchaseTime;

    decision = (rand()%3+1);
    if (decision == 1)
        *deliveryType = 'F';
    else if (decision == 2)
        *deliveryType = 'S';
    else
        *deliveryType = 'E';

    decision = (rand()%1000+1);
    if(decision >= 500)
        *amountOfPurchase = 'A';
    else
        *amountOfPurchase = 'B';
}

void swap(customer a, customer b) {  //to swap 2 nodes of a list

    int purchaseTime, deliveryTime, deliveryStartTime, courierID;
    char deliveryType, amountOfPurchase;

    purchaseTime = a->purchaseTime; a->purchaseTime = b->purchaseTime; b->purchaseTime = purchaseTime;
    deliveryTime = a->deliveryTime; a->deliveryTime = b->deliveryTime; b->deliveryTime = deliveryTime;
    deliveryStartTime = a->deliveryStartTime; a->deliveryStartTime = b->deliveryStartTime; b->deliveryStartTime = deliveryStartTime;
    courierID = a->courierID; a->courierID = b->courierID; b->courierID = courierID;
    deliveryType = a->deliveryType; a->deliveryType = b->deliveryType; b->deliveryType = deliveryType;
    amountOfPurchase = a->amountOfPurchase; a->amountOfPurchase = b->amountOfPurchase; b->amountOfPurchase = amountOfPurchase;
}

void sortList(customerList myList) {  //to sort a list in ascending order based on arrival time

    customer current, index;
    current = myList->head;
    index = myList->head->next;
    int status;
    do {
        status = 0;
        for(;index != NULL;) {
            if(index->purchaseTime < current->purchaseTime) {
                swap(index,current);
                status = 1;
            }
            current = current->next;
            index = index->next;
        }
        current = myList->head;
        index = myList->head->next;
    }
    while(status == 1);
}

void createCustomerList(customerList myList, int noOfCustomers, int maxPurchaseTime, int maxDeliveryTime) {  //to create the customer list for required number of customers randomly

    int i;
    int purchaseTime, deliveryTime, deliveryStartTime, courierID;
    char deliveryType, amountOfPurchase;

    customer tmp;
    for(i=0; i<noOfCustomers; i++) {
        defineCustomer(maxPurchaseTime,maxDeliveryTime,&purchaseTime,&deliveryStartTime,&deliveryTime,&courierID,&deliveryType,&amountOfPurchase);
        tmp = malloc(sizeof(struct Node));

        tmp->purchaseTime = purchaseTime;
        tmp->amountOfPurchase = amountOfPurchase;
        tmp->deliveryType = deliveryType;
        tmp->deliveryStartTime = deliveryStartTime;
        tmp->deliveryTime = deliveryTime;
        tmp->courierID = courierID;
        tmp->next = NULL;
        if(i==0) {
            myList->head = tmp;
            myList->tail = myList->head;
            myList->head->next = NULL;
            myList->tail->next = NULL;
        }
        else {
            myList->tail->next = tmp;
            myList->tail = myList->tail->next;
            myList->tail->next = NULL;
        }
    }
    sortList(myList);  //in ascending order based on arrival time
}

void toList(customerList myList, struct customerInfo y) {  //adding customer to final list once served

    customer tmp;
    if(!(tmp = malloc(sizeof(struct Node)))) {
        printf("\nmemory not allocated correctly\n");
        exit(1);
    }

    tmp->purchaseTime = y.purchaseTime;
    tmp->deliveryType = y.deliveryType;
    tmp->deliveryStartTime = y.deliveryStartTime;
    tmp->deliveryTime = y.deliveryTime;
    tmp->courierID = y.courierID;
    tmp->amountOfPurchase = y.amountOfPurchase;
    tmp->next = NULL;
    if(myList->head == NULL) {
            myList->head = tmp;
            myList->tail = myList->head;
            myList->head->next = NULL;
            myList->tail->next = NULL;
        }
        else {
            myList->tail->next = tmp;
            myList->tail = myList->tail->next;
            myList->tail->next = NULL;
        }
}
