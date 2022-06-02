#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node{         //node for the list
    char scanpath[300];
    struct node *next;
};

struct listRec {      //list record
    struct Node *head;
    struct Node *tail;
    int size;
};

createScanpathList (char *filename, struct listRec *list) {

    char scanpath[300];
    struct Node *tmp;

    FILE *outFile;
    outFile = fopen(filename, "r");

    if (outFile == NULL) {    //checking if file is found
        printf("File not opened successfully!\n");
        exit(1);
    }

    int i=0;
    char ch;

    do{
        fscanf(outFile, "%s", scanpath);
        ch = fgetc(outFile);

        tmp = malloc(sizeof(struct Node));
        strcpy(tmp->scanpath, scanpath);
        tmp->next = NULL;

        if(i == 0) {
            list->head = tmp;
            list->tail = list->head;
            list->head->next = NULL;
            list->tail->next = NULL;
        }
        else {
            list->tail->next = tmp;
            list->tail = list->tail->next;
            list->tail->next = NULL;
        }

        i++;
        list->size++;

    }while(ch != EOF);

    fclose(outFile);

}

void searchPattern(char *T, char *P, int d, int q) {   //algorithm taken from assignment pdf


    int N = strlen(T);
    int M = strlen(P);

    int i, j, p = 0, t = 0, h = 1, k;

    for (i = 0; i < M-1; i++)
        h = (h*d)%q;

    for (i = 0; i < M; i++){
        p = (d*p + P[i])%q;
        t = (d*t + T[i])%q;
    }


    for (i = 0; i <= N - M; i++) {
        if ( p == t ) {

            for (j = 0; j < M; j++) {
                if (T[i+j] != P[j])
                    break;
            }

            if (j == M && T[i+M] != ']') {
                for(k=N-1; k>=i; k--) {
                    T[k+1] = T[k];
                }
                T[i] = '[';

                for(k=N; k>=(i+M+1); k--) {
                    T[k+1] = T[k];
                }
                T[i+M+1] = ']';
                searchPattern(T, P, d, q); //search the rest of the list for any more occurances of the pattern. Have to recall because original string edited with [] now.
            }
        }

        if ( i < N-M ) {
            t = (d*(t - T[i]*h) + T[i+M])%q;

            if (t < 0)
            t = (t + q);
        }
    }
}

void printStats(struct listRec *peopleWithAutismList, struct listRec *peopleWithoutAutismList) {

    int ctrStr = 0, ctrIns = 0, i, check = 0, maxAOIfreq, maxAOIfreqIndex;
    struct Node *tmp;

    int AOIFrequencies[10];
    for(i=0; i<10; i++)
        AOIFrequencies[i] = 0;

    printf("\nDetected patterns for people with autism:");
    for(tmp = peopleWithAutismList->head; tmp != NULL; tmp = tmp->next) {
        check = 0;
        for(i=0; i<strlen(tmp->scanpath); i++) {
            if(tmp->scanpath[i] == '[') {
                if(i != 0)
                    AOIFrequencies[tmp->scanpath[i-1] - '0']++;
                if(check == 0) {
                    ctrStr++;
                    check = 1;
                }
                ctrIns++;
            }
        }
        if(check == 1)
            printf("\n%d. %s", ctrIns, tmp->scanpath);
    }

    maxAOIfreq = 0;
    maxAOIfreqIndex = 0;

    for(i=0; i<10; i++) {
        if(AOIFrequencies[i] > maxAOIfreq) {
            maxAOIfreq = AOIFrequencies[i];
            maxAOIfreqIndex = i;
        }
    }

    if(ctrStr != 0) {
        printf("\n%d patterns detected in %d scanpaths", ctrIns, ctrStr);
        printf("\nThe most frequent AOI before the pattern is/are %d\n",maxAOIfreqIndex);
    }
    else
        printf("\nNone");


    for(i=0; i<10; i++)
        AOIFrequencies[i] = 0;

    ctrStr = 0, ctrIns = 0, check = 0;
    printf("\nDetected patterns for people without autism:");
    for(tmp = peopleWithoutAutismList->head; tmp != NULL; tmp = tmp->next) {
        check = 0;
        for(i=0; i<strlen(tmp->scanpath); i++) {
            if(tmp->scanpath[i] == '[') {
                if(i != 0)
                    AOIFrequencies[tmp->scanpath[i-1] - '0']++;
                if(check == 0) {
                    ctrStr++;
                    check = 1;
                }
                ctrIns++;
            }
        }
        if(check == 1)
            printf("\n%d. %s", ctrIns, tmp->scanpath);
    }

    maxAOIfreq = 0;
    maxAOIfreqIndex = 0;

    for(i=0; i<10; i++) {
        if(AOIFrequencies[i] > maxAOIfreq) {
            maxAOIfreq = AOIFrequencies[i];
            maxAOIfreqIndex = i;
        }
    }

    if(ctrStr != 0) {
        printf("\n%d patterns detected in %d scanpaths", ctrIns, ctrStr);
        printf("\nThe most frequent AOI before the pattern is/are %d\n",maxAOIfreqIndex);
    }
    else
        printf("\nNone");

}

int main() {

    struct listRec *peopleWithAutismList;
    struct listRec *peopleWithoutAutismList;

    peopleWithAutismList = (struct listRec *)malloc(sizeof(struct listRec));
    peopleWithoutAutismList = (struct listRec *)malloc(sizeof(struct listRec));

    char filenameAutism[100], filenameWithoutAutism[100], toSearch[101];

    printf("Enter the file name for people with autism: ");
    scanf("%s", filenameAutism);

    printf("Enter the file name for people without autism: ");
    scanf("%s", filenameWithoutAutism);

    //was for testing on mac since developed on mac
    //strcpy(filenameAutism, "/Users/maryamimran/Documents/5thSemester/CNG315/Assignments/Assignment4/peoplewithautism.txt");
    //strcpy(filenameWithoutAutism, "/Users/maryamimran/Documents/5thSemester/CNG315/Assignments/Assignment4/peoplewithoutautism.txt");

    createScanpathList(filenameAutism, peopleWithAutismList);
    createScanpathList(filenameWithoutAutism, peopleWithoutAutismList);

    printf("Enter the pattern: ");
    scanf("%s", toSearch);

    struct Node *tmp;

    for(tmp = peopleWithAutismList->head; tmp != NULL; tmp = tmp->next) {
        searchPattern(tmp->scanpath, toSearch, 10, 11);
    }

    for(tmp = peopleWithoutAutismList->head; tmp != NULL; tmp = tmp->next) {
        searchPattern(tmp->scanpath, toSearch, 10, 11);
    }

    printStats(peopleWithAutismList, peopleWithoutAutismList);

    return 0;
}
