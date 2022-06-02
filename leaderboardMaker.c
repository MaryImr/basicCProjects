//
//  main.c
//  leaderboardMaker
//
//  Created by Maryam Imran on 12/11/2021.
//  Please Note that this file was created as an xcode project on a macbook air M1 and works perfectly from both the IDE and the terminal/command line
//  Alao note that the text files considered for this program did not have an extra line before EOF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct Champion{                    //structure to store data for a single champion
    char name[15];
    double expectedWinRate;         //double not float because some values may be int
    int NumberOfBattles;
    int NumberOfWins;
    double ActualWinRate;          //same explanation an above for double
    double ExpectationSkew;        //same explanation an above for double
};

struct Battle{                        //structure to store data for every battle. This later used to computed statistics
    char champion_one[15];
    char champion_two[15];
    char winner[15];
};

struct Champion* initializeChampions (char filename[15], int *size) {    //address of size is sent from the main function
                                                                           //so that it can directly be modified
    struct Champion *list;            //to store chapions initial data
    int i;
    char ch;
    list = (struct Champion *)malloc(*size * sizeof(struct Champion));   //memory allocation
    
    FILE *outFile;
    outFile = fopen(filename,"r");
    
    if (outFile == NULL) {    //checking if file is found
        printf("File not opened successfully!\n");
        exit(1);
    }
    
    ch = fgetc(outFile);
    fseek(outFile,-1L,SEEK_CUR);     //moving cursor back to start of line
    
    for(i=0; ch!=EOF; i++) {
        if(i >= *size) {     //if array needs another block of memory
            *size += 1;
            list = (struct Champion*)realloc(list, *size);
        }
        
        fscanf(outFile,"%s",&list[i].name);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%lf",&list[i].expectedWinRate);
        
        //printf("\n---%lf---\n",list[i].expectedWinRate);
        
        list[i].ActualWinRate = 0;          //initializing statistics that need to be computed
        list[i].ExpectationSkew = 0;
        list[i].NumberOfBattles = 0;
        list[i].NumberOfWins = 0;
        
        ch = fgetc(outFile);        //to check if the next character in the file is EOF
                                    //please note that when I ran my program on a windows device, sometimes reading the file through the fgetc or fscanf profram was causing crashes.
    }
    fclose(outFile);
    return list;
}

void getBattleData(struct Champion *myChamps, int noOfChamps, char battlesFile[15]) {
    
    struct Battle *allBattles;       //to store all battles
    int size = 0, i, j;
    char ch;
    allBattles = (struct Battle *)malloc(size * sizeof(struct Battle));   //memory allocation
    
    FILE *outFile;
    outFile = fopen(battlesFile,"r");
    
    if (outFile == NULL) {        //checking if file found
        printf("File not opened successfully!\n");
        exit(1);
    }
    
    ch = fgetc(outFile);
    fseek(outFile,-1L,SEEK_CUR);
    
    for(i=0; ch!=EOF; i++) {
        if(i >= size) {
            size++;
            allBattles = (struct Battle*)realloc(allBattles, size);
        }
        
        while(ch != ' ') {      //bypassing space character
            ch = fgetc(outFile);
        }
        
        fscanf(outFile,"%s",&allBattles[i].champion_one);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%s",&allBattles[i].champion_two);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%s",&allBattles[i].winner);
        
        //printf("\n---%lf---\n",list[i].expectedWinRate);
        
        ch = fgetc(outFile);       //checkinf for EOF character
        
    }
    fclose(outFile);
    
    for(i=0; i<size; i++) {                  //assigning some statistics
        for(j=0; j<noOfChamps; j++) {
            if(strcmp(allBattles[i].champion_one,myChamps[j].name) == 0) {
                myChamps[j].NumberOfBattles++;
            }
            if(strcmp(allBattles[i].champion_two,myChamps[j].name) == 0) {
                myChamps[j].NumberOfBattles++;
            }
            if(strcmp(allBattles[i].winner,myChamps[j].name) == 0) {
                myChamps[j].NumberOfWins++;
            }
        }
    }
    
    //free(allBattles);
    
}

void computeWinRate (struct Champion *myChamps, int noOfChamps) {
    
    int i;
    double winRateRatio;
    
    for(i=0; i<noOfChamps; i++) {     //computing remaining statistics
        myChamps[i].ActualWinRate = (float)myChamps[i].NumberOfWins/(float)myChamps[i].NumberOfBattles;
        
        winRateRatio = myChamps[i].ActualWinRate/myChamps[i].expectedWinRate;
        
        myChamps[i].ExpectationSkew = fabs(winRateRatio - 1);
    }
    
}

int leftChildIndex(int i) {    //calculating left child index of a parent for a heap
    return (2*i);
}

int rightChildIndex(int i) {     //calculating right child index of a parent for a heap
    return (2*i) + 1;
}

void swap(struct Champion *myChamps, int a, int b) {         //simple function to swap two champion structures
    
    struct Champion temp;
    
    strcpy(temp.name, myChamps[b].name);
    temp.ActualWinRate = myChamps[b].ActualWinRate;
    temp.NumberOfWins = myChamps[b].NumberOfWins;
    temp.NumberOfBattles = myChamps[b].NumberOfBattles;
    temp.ExpectationSkew = myChamps[b].ExpectationSkew;
    temp.expectedWinRate = myChamps[b].expectedWinRate;
    
    strcpy(myChamps[b].name, myChamps[a].name);
    myChamps[b].ActualWinRate = myChamps[a].ActualWinRate;
    myChamps[b].NumberOfWins = myChamps[a].NumberOfWins;
    myChamps[b].NumberOfBattles = myChamps[a].NumberOfBattles;
    myChamps[b].ExpectationSkew = myChamps[a].ExpectationSkew;
    myChamps[b].expectedWinRate = myChamps[a].expectedWinRate;
    
    strcpy(myChamps[a].name, temp.name);
    myChamps[a].ActualWinRate = temp.ActualWinRate;
    myChamps[a].NumberOfWins = temp.NumberOfWins;
    myChamps[a].NumberOfBattles = temp.NumberOfBattles;
    myChamps[a].ExpectationSkew = temp.ExpectationSkew;
    myChamps[a].expectedWinRate = temp.expectedWinRate;
    
}

void heapify(struct Champion *myChamps, int i, int heap_size, int sortingCriteria) {
    //function to heapify an array. format followed from the psuedo code from the lecture slides. max heap creating according to the sorting criteria done
    
    int l = leftChildIndex(i);
    int r = rightChildIndex(i);
    
    int largest;
    
    switch(sortingCriteria) {
        case 1:
            
            if(l < heap_size && myChamps[l].ActualWinRate < myChamps[i].ActualWinRate)
                largest = l;
            else
                largest = i;
            
            if(r < heap_size && myChamps[r].ActualWinRate < myChamps[largest].ActualWinRate)
                largest = r;
            
            if(largest != i) {
                swap(myChamps, i, largest);
                heapify(myChamps, largest, heap_size, sortingCriteria);
            }
            
            break;
        case 2:
            
            if(l < heap_size && myChamps[l].expectedWinRate < myChamps[i].expectedWinRate)
                largest = l;
            else
                largest = i;
            
            if(r < heap_size && myChamps[r].expectedWinRate < myChamps[largest].expectedWinRate)
                largest = r;
            
            if(largest != i) {
                swap(myChamps, i, largest);
                heapify(myChamps, largest, heap_size, sortingCriteria);
            }
            
            break;
        case 3:
            
            if(l < heap_size && myChamps[l].ExpectationSkew < myChamps[i].ExpectationSkew)
                largest = l;
            else
                largest = i;
            
            if(r < heap_size && myChamps[r].ExpectationSkew < myChamps[largest].ExpectationSkew)
                largest = r;
            
            if(largest != i) {
                swap(myChamps, i, largest);
                heapify(myChamps, largest, heap_size, sortingCriteria);
            }
            
            break;
        default:
            printf("Please Enter a Valid Sorting Criteria!");
    }
    
}

void buildHeap(struct Champion *myChamps, int heap_size, int sortingCriteria) {
    //function to build a heap. format followed from the psuedo code from the lecture slides.
    int i;
    
    for(i = (heap_size/2); i > 0; i--)
        heapify(myChamps, (i-1), heap_size, sortingCriteria);  //'i-1' because the format considers the indexes from 1 to n but in reality, the indexes are from 0 to 'n-1'.

}

void printLeaderboard(int size, struct Champion *ChampionsList) {
 //function to print the leaderboeard at any time
    int i;
    
    printf("\nChampion      Battles      Win      AWR      EWR      Skew\n");
    
    for(i=0; i<size; i++) {
        printf("%s          %d           %d        %0.2lf      %0.2lf    %0.2lf\n", ChampionsList[i].name, ChampionsList[i].NumberOfBattles, ChampionsList[i].NumberOfWins, ChampionsList[i].ActualWinRate, ChampionsList[i].expectedWinRate, ChampionsList[i].ExpectationSkew);
    }
    printf("\n");
}

void heapSort(struct Champion *myChamps, int sortingCriteria, int arraySize) {
    //function to sort an array that is heapified. format followed from the psuedo code from the lecture slides.
    
    int i, heap_size = arraySize;
    
    buildHeap(myChamps, arraySize, sortingCriteria);
    
    for(i = arraySize; i > 1; i--) {
        swap(myChamps, 0, (i-1));    //same as before, psuedocode sonsiders indexes from 1 to n but in reality indexes from 0 to n-1 and hence accounted to
        heap_size --;
        heapify(myChamps, 0, heap_size, sortingCriteria);
    }
    
    printLeaderboard(arraySize, myChamps);
    
}

int main(int argv, char* argc[]) {
    
    int sortingCriteria = atoi(argc[1]);   //converting sorting criteria from a string to an int
    
    if(sortingCriteria != 1 && sortingCriteria != 2 && sortingCriteria != 3) {   //checking if valid sorting criteria sent
        printf("\nInvalid Sorting Criteria!!\n");
        return 0;
    }
    
    int numberOfChampions = 0;
    struct Champion *ChampionsList = initializeChampions(argc[2], &numberOfChampions);
    
    getBattleData(ChampionsList, numberOfChampions, argc[3]);
    computeWinRate(ChampionsList, numberOfChampions);
    
    heapSort(ChampionsList, sortingCriteria, numberOfChampions);
    
    return 0;
}



