#include<stdlib.h>
#include<stdio.h>
#include "queue.h"
#include<string.h>


void makeEmptyQueue (queue q) { //function to make an empty queue
    q->size = 0;
    struct Node *tmp;
    tmp = malloc(sizeof(struct Node));
    q->front = tmp;
    q->front->next = NULL;
    q->rear = q->front;
    q->rear->next = NULL;
}

void enqueue (queue q, customer temp) {  //to add elements to a queue
    q->size++;
    if (q->front->next == NULL) {
        q->front->next = temp;
        q->rear = q->front->next;
        q->rear->next = NULL;
        q->front->next->next = NULL;
    }
    else {
        q->rear->next = temp;
        q->rear = q->rear->next;
        q->rear->next = NULL;
    }
}

void dequeue(queue q) {  //to remove elements from a queue
    struct Node *temp;
    if(q->front == NULL) { //empty queue
        return;
    }
    else {
        temp = q->front;
        q->front = q->front->next;
        if(q->front == NULL) {
            q->rear = NULL;
        }
        free(temp);
    }
    q->size --;
}

void newCustomer(struct Node* tmp, queue myQueue) {  //adding new customers to queue

    int i;
    customer person;
    if(!(person = malloc(sizeof(struct Node)))) {
        printf("\nMemory Allocation Failed!");
        exit(1);
    }

    person->purchaseTime = tmp->purchaseTime;
    person->amountOfPurchase = tmp->amountOfPurchase;
    person->deliveryType = tmp->deliveryType;
    person->deliveryStartTime = tmp->deliveryStartTime;
    person->deliveryTime = tmp->deliveryTime;
    person->courierID = tmp->courierID;
    person->next = NULL;

    if(myQueue->front == NULL) {  //if there is no customer in queue already
        myQueue->front = person;
        myQueue->rear = myQueue->front;
        myQueue->front->next = NULL;
        myQueue->rear->next = NULL;
        myQueue->size++;
    }
    else {  //if queue already has customers
        customer current;
        current = myQueue->front;
        if(person->deliveryType == 'F') {  //if new customer has free delivery, add to end of list
            myQueue->rear->next = person;
            myQueue->rear = myQueue->rear->next;
            myQueue->rear->next = NULL;
            myQueue->size++;
        }
        if(person->deliveryType == 'E') {  //if express delivery
            if(current->deliveryType == 'E') {  //if first delivery in queue is express
                for(i=1;i<myQueue->size;i++) {  //traverse until the end of express delivery reached or end of list reached
                    if(current->next->deliveryType == 'E') {
                        current = current->next;
                    }
                    else
                        break;
                }
                person->next = current->next;
                current->next = person;
                if(i==myQueue->size) {  //reassigning rear in case list end is reached
                    myQueue->rear = current->next;
                    myQueue->rear->next = NULL;
                }
            }
            else {  //in case already present elements in list are not express delivery
                person->next = myQueue->front;  //express delivery added to front of list
                myQueue->front = person;
            }
            myQueue->size++;  //queue size incremented
        }
        if(person->deliveryType == 'S') { //in case new delivery is standard type
            if(current->deliveryType == 'F') {  //if already existing delivery at front is free
                person->next = myQueue->front;  //then standard type added to front of list
                myQueue->front = person;
            }
            if(current->deliveryType == 'S') {  //if already existing delivery at front is standard too
                for(i=1;i<myQueue->size;i++) {  //then traversing until end of standard delivery reached
                    if(current->next->deliveryType == 'S') {
                        current = current->next;
                    }
                    else
                        break;
                }
                person->next = current->next;
                current->next = person;
                if(i==myQueue->size) {  //reassigning rear in case end of list reached
                    myQueue->rear = current->next;
                    myQueue->rear->next = NULL;
                }
            }
            if(current->deliveryType == 'E') {  //in case already existing customer in front of queue is a express
                for(i=1;i<myQueue->size;i++) {  //traversing until end of both express and standard cases in list reached or until list ends
                    if(current->next->deliveryType == 'E' || current->next->deliveryType == 'S') {
                        current = current->next;
                    }
                    else
                        break;
                }
                person->next = current->next;
                current->next = person;
                if(i==myQueue->size) {   //reassigning rear
                    myQueue->rear = current->next;
                    myQueue->rear->next = NULL;
                }
            }
            myQueue->size++;  //incrementing queue size
        }
    }

}
