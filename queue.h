#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

struct Node {   //list entry for one delivery
    char deliveryType;
    int purchaseTime;
    int deliveryTime;
    int deliveryStartTime;
    int courierID;
    char amountOfPurchase;
    struct Node* next;
};

struct customerInfo {  //to represent one delivery outside of list/queue

    char deliveryType;
    int purchaseTime;
    int deliveryTime;
    int deliveryStartTime;
    int courierID;
    char amountOfPurchase;
};

typedef struct Node *customer;

struct listRecord {  //representing a list

    struct Node* head;
    struct Node* tail;
    int size;
};

typedef struct listRecord *customerList;

struct QueueRecord { //structure for queue
    struct Node *front;
    struct Node *rear;
    int size;
};

typedef struct QueueRecord *queue;
//required functions
void makeEmptyQueue(queue);
void enqueue(queue,customer);
void dequeue(queue);
void newCustomer(struct Node*,queue);

#endif // QUEUE_H_INCLUDED
