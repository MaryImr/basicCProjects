//Maryam Imran 2413284
//the project zip file has a txt file for posts in case that is causing a problem!

#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"
#include<string.h>


void fileToArray(struct node *arr, char *filename, int fileSize) {  //to transfer data from file to an array

    int ctr, i;
    char temp, tmpArr[150];
    FILE *outFile;
    outFile = fopen(filename,"r");
    if(outFile == NULL) {
        printf("File did not open successfully!");
        exit(1);
    }
    temp = fgetc(outFile);
    for(i=0;i<fileSize;i++) {
        for(ctr=0; ctr<150; ctr++)
            tmpArr[ctr] = 0;
        for(ctr=0; temp != '\n' && temp != EOF; ctr++) {
            tmpArr[ctr] = temp;
            temp = fgetc(outFile);
        }
        arr[i].post_ID = (char*)malloc(20*sizeof(char));
        arr[i].permalink = (char*)malloc(40*sizeof(char));
        arr[i].type = (char*)malloc(6*sizeof(char));
        strcpy(arr[i].post_ID,strtok(tmpArr,";"));
        strcpy(arr[i].permalink,strtok(NULL,";"));
        arr[i].totalReach = atoi(strtok(NULL,";"));
        arr[i].engagedUsers = atoi(strtok(NULL,";"));
        strcpy(arr[i].type,strtok(NULL,";"));
        arr[i].dT.day = atoi(strtok(NULL,"/"));
        arr[i].dT.month = atoi(strtok(NULL,"/"));
        arr[i].dT.year = atoi(strtok(NULL," "));
        arr[i].dT.hours = atoi(strtok(NULL,":"));
        arr[i].dT.minutes = atoi(strtok(NULL,";"));
        temp = fgetc(outFile);
    }
    fclose(outFile);
}

int countLines(char *filename) {  //to count lines in the file

    int lines = 0;
    char temp;
    FILE *outFile;
    outFile = fopen(filename,"r");
    if(outFile == NULL) {
        printf("File did not open successfully!");
        exit(1);
    }
    do{
        temp = fgetc(outFile);
        if(temp == '\n' || temp == EOF)
            lines++;
    }
    while(temp!=EOF);
    fclose(outFile);
    return lines;
}


int main(int argc, char **argv) {

    struct TreeNode* tree;
    tree = readData(argv[1]); //for this to work as intended, please make sure the data for a single post is stored in a single line in the "insta.txt" file

    printf("\nData Processed:");
    printf("\n===============");
    displayPosts(tree);

    struct listRecord *tmp = mostReach(tree);
    struct listNode *t;
    printf("\n\nMaximum Total Reach:");
    printf("\n======================");
    for(t=tmp->front; t!=NULL; t=t->next)
        printf("\nPost ID: %s\nPermalink: %s\nType: %s\nPosted: %d/%d/%d %d:%d\nTotal Reach: %d\nEngaged users: %d\n"
               ,t->data.post_ID,t->data.permalink,t->data.type,t->data.dT.day,t->data.dT.month,t->data.dT.year,t->data.dT.hours,
               t->data.dT.minutes,t->data.totalReach,t->data.engagedUsers);

    mostEngaged(tree);

    return 0;
}
