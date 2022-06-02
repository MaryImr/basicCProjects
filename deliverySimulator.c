#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list.h"
#include <string.h>
#include<time.h>

void parseInput(char **,int *, int *, int *, int *);
void initialiseSimulator(queue,int *, int);
int courierAvailable(int *,int);
void toTasks(int,struct customerInfo*,struct Node*);
void reportStatistics(customerList, int, int, int, int, int, int);

int main(int argc, char **argv)
{
    srand(time(NULL));
    int noOfCustomers, noOfCouriers, maxPurchaseTime, maxDeliveryTime;
    customerList list;
    list = malloc(sizeof(struct listRecord));

    parseInput(argv,&noOfCustomers,&noOfCouriers,&maxPurchaseTime,&maxDeliveryTime);
    createCustomerList(list,noOfCustomers,maxPurchaseTime,maxDeliveryTime);
    list->size = noOfCustomers;

    queue customerQueue; //queue to hold delivery waiting for their turn during the simulation
    int *courierStatus; //array to hold status of each courier
    customerQueue = malloc(sizeof(struct QueueRecord));
    makeEmptyQueue(customerQueue);
    courierStatus = (int *)malloc(noOfCouriers*sizeof(int));
    initialiseSimulator(customerQueue,courierStatus,noOfCouriers);

    customerList listDone;  //list to keep patients once they have been served
    listDone = malloc(sizeof(struct listRecord));
    listDone->size = noOfCustomers;
    listDone->head = NULL;
    listDone->tail = listDone->head;

    int clock = 0, i, j, customersServed = 0, status = 0, totalPeopleInQueue = 0, totalTimeInQueue = 0, maxTimeInQueue=0;
    struct customerInfo *currentTasks;  //array to keep record of current customers being served by all couriers
    if(!(currentTasks = (struct customerInfo*)calloc(noOfCouriers,sizeof(struct customerInfo)))) {
        printf("\nMemory Allocation Failed!");
        exit(1);
    }

    //in case you want to view the list of customers generated
    /*customer t;
    for(t=list->head; t!=NULL; t=t->next) {
        printf("type: %c purchase time: %d delivery time: %d delivery start: %d courier id: %d amount: %c\n",t->deliveryType,t->purchaseTime,t->deliveryTime,t->deliveryStartTime,t->courierID,t->amountOfPurchase);
    }*/

    for(;customersServed != noOfCustomers;clock++) {  //start of simulation
        status = courierAvailable(courierStatus,noOfCouriers); //to check if a courier is available
        if(status == 1 && list->head != NULL) {
            if(list->head->purchaseTime <= clock) {
                if(customerQueue->front == NULL) {
                    list->head->deliveryStartTime = clock;  //assigning starting time for delivery
                    for(i=0; i<noOfCouriers; i++) {  //finding available courier
                        if(courierStatus[i] == 1) {
                            list->head->courierID = i+1;  //assigning courier(+1 in order to start courier ids from 1, not 0)
                            courierStatus[i] = 0;
                            break;  //terminating search after available courier found
                        }
                    }

                    toTasks(i,currentTasks,list->head);  //moving customer to array of ongoing tasks
                    list->head = list->head->next;  //moving list head to the next customer in line
                }
                else if(list->head != NULL){   //in case there are already customers in queue
                    newCustomer(list->head,customerQueue);  //adding customer to queue
                    totalPeopleInQueue++;  //incrementing total people added to queue
                    list->head = list->head->next;  //moving list head to the next customer in line
                }
            }
        }
        else if(list->head != NULL){  //in case no courier is available but list still has more elements and head of list arrival time coincides with the clock

            if(list->head->purchaseTime <= clock) {
                newCustomer(list->head,customerQueue);  //adding customer to queue
                totalPeopleInQueue++;   //incrementing total people added to queue
                list->head = list->head->next;   //moving list head to the next customer in line
            }
        }
        status = courierAvailable(courierStatus,noOfCouriers);  //checking status of couriers again
        if(status == 1 && customerQueue->front != NULL) {  //if courier available and queue has customer(s)
            if(customerQueue->front->purchaseTime <= clock) {
                customerQueue->front->deliveryStartTime = clock;  //assigning start time
                for(i=0; i<noOfCouriers; i++) {  //searching for and assigning available courier
                    if(courierStatus[i] == 1) {
                        customerQueue->front->courierID = i+1;
                        courierStatus[i] = 0;
                        break;
                    }
                }
                toTasks(i,currentTasks,customerQueue->front);  //moving customer from queue to ongoing tasks array
                totalTimeInQueue += customerQueue->front->deliveryStartTime - customerQueue->front->purchaseTime; //incrementing total time spent in queue by everyone
                if(customerQueue->front->deliveryStartTime - customerQueue->front->purchaseTime > maxTimeInQueue)  //checking if current customer spent the max amount of time in queue
                    maxTimeInQueue = customerQueue->front->deliveryStartTime - customerQueue->front->purchaseTime;
                dequeue(customerQueue);  //removing customer from queue, putting next customer in queue at the front
            }
        }

        for(j=0; j<noOfCouriers; j++) {
            if(clock == currentTasks[j].deliveryStartTime + currentTasks[j].deliveryTime && clock!=0) {  //checking if the service duration of any ongoing task has finished so that it can be removed and a new customer can be served
                courierStatus[currentTasks[j].courierID - 1] = 1;  //restoring courier status to available
                toList(listDone,currentTasks[j]);  //adding completed customer task to the final list
                customersServed++;  //number of customers served incremented
                currentTasks[j].purchaseTime = NULL;  //re-initializing the ongoing task statuses
                currentTasks[j].amountOfPurchase = NULL;
                currentTasks[j].deliveryType = NULL;
                currentTasks[j].deliveryStartTime = NULL;
                currentTasks[j].deliveryTime = NULL;
                currentTasks[j].courierID = NULL;
            }
        }
    }

    reportStatistics(listDone,noOfCouriers,noOfCustomers,clock,maxTimeInQueue,totalTimeInQueue,totalPeopleInQueue);  //reporting final statistics
    return 0;
}

void reportStatistics(customerList myList, int noOfCouriers, int noOfcustomers, int totalTime, int maxWaitingTime, int totalTimeInQueue,int totalPeopleInQueue) {

    int i, tot, E=0, F=0, S=0, A=0, B=0;
    int *courierStats[noOfCouriers];
    double averageWaitingTime=0;
    customer t;
    if(maxWaitingTime != 0)  //if max waiting time is 0, that means total people in queue was zero. Division by 0 gives error in c so this condition
        averageWaitingTime = ((float)totalTimeInQueue/(float)totalPeopleInQueue);  //if max time in queue is 0, then so is the average time
    for(i=0;i<noOfCouriers;i++) { //to analyze courier statistics
        tot=0;
        for(t = myList->head; t!=NULL; t = t->next) {
            if(t->courierID == i+1)
                tot++;
            courierStats[i] = tot;
        }
    }
    for(t = myList->head; t!=NULL; t = t->next) {  //to analyze delivery type statistics
        if(t->deliveryType == 'E')
            E++;
        else if(t->deliveryType == 'F')
            F++;
        else if(t->deliveryType == 'S')
            S++;
    }
    for(t = myList->head; t!=NULL; t = t->next) {  //to analyze amount customer paid for delivery statistics
        if(t->amountOfPurchase == 'A')
            A++;
        else
            B++;
    }

    printf("\n\n**************Delivery Statistics**************\n");
    printf("\nThe number of couriers: %d",noOfCouriers);
    printf("\nThe number of customers: %d",noOfcustomers);
    printf("\nNumber of customers for each delivery type:");
    printf("\n      Express: %d",E);
    printf("\n      Standard: %d",S);
    printf("\n      Free: %d",F);
    printf("\nNumber of patients for each courier:");
    for(i=0;i<noOfCouriers;i++) {
        printf("\n      Courier %d: %d",i+1,courierStats[i]);
    }
    printf("\nCompletion time: %d",totalTime-1);
    printf("\nAverage time spent in the queue: %0.1lf",averageWaitingTime);
    printf("\nMaximum waiting time: %d",maxWaitingTime);
    if(A > B)
        printf("\nPopular purchase: A");
    else if(A == B)
        printf("\nPopular purchase: Equal");
    else
        printf("\nPopular purchase: B");

    printf("\n\n\n");
}


void toTasks(int i, struct customerInfo *currentTasks, struct Node *tmp) {  //adding a patient to ongoing tasks array

    currentTasks[i].purchaseTime = tmp->purchaseTime;
    currentTasks[i].deliveryType = tmp->deliveryType;
    currentTasks[i].deliveryStartTime = tmp->deliveryStartTime;
    currentTasks[i].deliveryTime = tmp->deliveryTime;
    currentTasks[i].courierID = tmp->courierID;
    currentTasks[i].amountOfPurchase = tmp->amountOfPurchase;
}

int courierAvailable(int *courierStatus, int couriers) {  //checking availability of courier(s)

    int i=0, res=0;
    do {
        if(courierStatus[i] == 1) {
            res = 1;
        }
        i++;
    }
    while(i<couriers);
    return res;
}

void initialiseSimulator(queue customerQueue,int *courierArray, int couriers) {  //initialize simulator conditions

    int i;

    customerQueue->front = NULL;
    customerQueue->rear = NULL;
    customerQueue->rear = customerQueue->front;
    customerQueue->size = 0;

    for(i=0; i<couriers; i++) {
        courierArray[i] = 1;
    }
}

void parseInput(char **argv,int *noOfCustomers, int *noOfCouriers, int *maxPurchaseTime, int *maxDeliveryTime) {  //to assign correct input values to variables

    *noOfCustomers = atoi(argv[1]);
    *noOfCouriers = atoi(argv[2]);
    *maxPurchaseTime = atoi(argv[3]);
    *maxDeliveryTime = atoi(argv[4]);
}
