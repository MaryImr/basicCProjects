//Maryam Imran 2413284
//PA1 Solution
//If program crashes before loading teams list, please check format of teams file!

#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct dateTime {  //to store date_time stamp of a team record
    int day;
    int month;
    int year;
    int hour;
    int minute;
};

struct Node {  //info for one team to be stored in a list
    int id;
    char *name;
    char status;
    int points;
    int score;
    int goals;
    struct dateTime date_time;
    struct Node *next;
};

struct lineOfFile {   //info for one team to be used as an array
    int id;
    char *name;
    char status;
    int points;
    int score;
    int goals;
    struct dateTime date_time;
};

struct listRecord {   //details of a list
    struct Node *head;
    struct Node *tail;
    int size;
};

typedef struct Node *ptr;
typedef ptr position;
typedef struct listRecord *list;

int countLines(char filename[15]) {    //function to count the total lines in a file
                                       //here it serves the purpose of giving the program the total number of teams to be loaded to the list
    int lines=0;
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
    while (temp != EOF);
    fclose(outFile);

    return lines;
}

void fileToArray(struct lineOfFile *ptr, char filename[15], int fileSize) {   //to load data from the file to an array

    int ctr, i;
    char temp;
    FILE *outFile;
    outFile = fopen(filename,"r");
    if(outFile == NULL) {
        printf("File did not open successfully!");
        exit(1);
    }

    for(i=0;i<fileSize;i++) {

        ptr[i].name = (char*)calloc(50,sizeof(char));
        fscanf(outFile,"%d",&ptr[i].id);
        fseek(outFile,1L,SEEK_CUR);         //all fseek statements in this function are to jump over the ; in the line of the file
        temp = fgetc(outFile);
        for(ctr = 0; temp != ';'; ctr++) {
            ptr[i].name[ctr] = temp;
            temp = fgetc(outFile);
        }
        fscanf(outFile,"%c",&ptr[i].status);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%d",&ptr[i].points);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%d",&ptr[i].score);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%d",&ptr[i].goals);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%d",&ptr[i].date_time.day);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%d",&ptr[i].date_time.month);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%d",&ptr[i].date_time.year);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%d",&ptr[i].date_time.hour);
        fseek(outFile,1L,SEEK_CUR);
        fscanf(outFile,"%d",&ptr[i].date_time.minute);
        fseek(outFile,1L,SEEK_CUR);
    }
    fclose(outFile);
}

void initialiseTeams (char filename[15],struct listRecord *myList) {   //to load the teams from file to list through an array

    int size,i;
    struct lineOfFile *tmpArray;

    size = countLines(filename);
    myList->size = size;
    tmpArray = (struct lineOfFile*)malloc(size*sizeof(struct lineOfFile));
    fileToArray(tmpArray,filename,size);

    position tmp;
    for(i=0;i<size;i++) {
        tmp = malloc(sizeof(position));
        tmp->name = (char*)malloc(50*sizeof(char));
        tmp->id = tmpArray[i].id; tmp->name = tmpArray[i].name; tmp->goals = tmpArray[i].goals; tmp->points = tmpArray[i].points;
        tmp->score = tmpArray[i].score; tmp->status = tmpArray[i].status; tmp->date_time.day = tmpArray[i].date_time.day; tmp->date_time.month = tmpArray[i].date_time.month; tmp->date_time.year = tmpArray[i].date_time.year;
        tmp->date_time.hour = tmpArray[i].date_time.hour; tmp->date_time.minute = tmpArray[i].date_time.minute;
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
}

void addTeam(list myList, struct lineOfFile data) {    //to add a new team to the list

    data.id = myList->tail->id + 1;
    position tmp;
    tmp = malloc(sizeof(position));
    tmp->name = (char*)malloc(50*sizeof(char));
    tmp->id = data.id;  tmp->goals = data.goals;
    tmp->name = data.name;  tmp->points = data.points;
    tmp->score = data.score; tmp->status = data.status; tmp->date_time.day = data.date_time.day;
    tmp->date_time.month = data.date_time.month; tmp->date_time.year = data.date_time.year;
    tmp->date_time.hour = data.date_time.hour; tmp->date_time.minute = data.date_time.minute;
    tmp->next = NULL;
    myList->tail->next = tmp;
    myList->tail = myList->tail->next;
    myList->tail->next = NULL;
    myList->size++;
    tmp = NULL;
    free(tmp);
}

void deleteTeam(list myList, int idToDelete) {    //function to delete a team from the list

    position tmp;
    tmp = myList->head;
    while(tmp->next != NULL && tmp->next->id != idToDelete && tmp->id != idToDelete)
        tmp = tmp->next;
    if(myList->tail == tmp->next) {
        myList->tail = tmp;
    }

    if(myList->size != 1 && tmp->next == NULL)
        printf("Team with ID %d does not exist.",idToDelete);
    else if(tmp->id != idToDelete) {
        position accountToDelete;
        accountToDelete = tmp->next;
        tmp->next = tmp->next->next;
        myList->size--;
        printf("Team with ID %d has been deleted successfully.",idToDelete);
    }
    else {
        position accountToDelete;
        accountToDelete = myList->head;
        myList->head = myList->head->next;
        myList->size--;
        printf("Team with ID %d has been deleted successfully.",idToDelete);
    }
    if(myList->size == 0)
        myList->tail = myList->head;
}

void displayTeams(list myList) {   //to display the teams

    position tmp;
    printf("\nTeams in your database:");
    printf("\n--------------------------");
    for(tmp = myList->head; tmp!=NULL; tmp = tmp->next) {
        printf("\n\nID: %d",tmp->id);
        printf("\nTeam Name: %s",tmp->name);
        printf("\nTeam Status: %c",tmp->status);
        printf("\nTeam Points: %d",tmp->points);
        printf("\nTeam Score: %d",tmp->score);
        printf("\nNumber of team goals: %d",tmp->goals);
        printf("\nDate: %d/%d/%d",tmp->date_time.day,tmp->date_time.month,tmp->date_time.year);
        printf("\nTime: %d:%d",tmp->date_time.hour,tmp->date_time.minute);
    }
}

int searchTeams(list myList, char *arr, int task) {  //to search a team

    position tmp;
    int decision=0, i;

    arr[0] = toupper(arr[0]);  //accounting for name of team put in any format, e.g. Galatasaray, galatasaray, GALATASARAY
    for(i=1; arr[i] != NULL; i++)       //all name formats are converted to Galatasaray
        arr[i] = tolower(arr[i]);

    for(tmp = myList->head; tmp!=NULL; tmp=tmp->next) {
        if (strcmp(tmp->name, arr) == 0) {
            decision = 1;  //this indicates that the searched team has been found
            if(task == 1) {
                printf("\nID: %d",tmp->id);
                printf("\nTeam Name: %s",tmp->name);
                printf("\nTeam Status: %c",tmp->status);
                printf("\nTeam Points: %d",tmp->points);
                printf("\nTeam Score: %d",tmp->score);
                printf("\nNumber of team goals: %d",tmp->goals);
                printf("\nDate: %d/%d/%d",tmp->date_time.day,tmp->date_time.month,tmp->date_time.year);
                printf("\nTime: %d:%d",tmp->date_time.hour,tmp->date_time.minute);
            }
        }
    }
    return decision;
}

void Overwrite(char filename[15], list myList) {  //to overwrite the file contents with the latest list

    position tmp;
    FILE *inFile;
    inFile = fopen(filename,"w");
    if(inFile == NULL) {
        printf("File did not open successfully!");
        exit(1);
    }
    for(tmp = myList->head; tmp!=NULL; tmp = tmp->next) {
        if(tmp->next == NULL)  //last line of file
            fprintf(inFile,"%d;%s;%c;%d;%d;%d;%d/%d/%d %d:%d",tmp->id,tmp->name,tmp->status,tmp->points,tmp->score,tmp->goals,tmp->date_time.day,tmp->date_time.month,tmp->date_time.year,tmp->date_time.hour,tmp->date_time.minute);
        else {   //other lines of file
            fprintf(inFile,"%d;%s;%c;%d;%d;%d;%d/%d/%d %d:%d\n",tmp->id,tmp->name,tmp->status,tmp->points,tmp->score,tmp->goals,tmp->date_time.day,tmp->date_time.month,tmp->date_time.year,tmp->date_time.hour,tmp->date_time.minute);
        }
    }

    fclose(inFile);
}

int createFavouriteList (list teamList, struct listRecord *favouriteList, int id, position toTransfer) {  //to create favorite teams list

    position tmp;
    for(tmp = favouriteList->head; tmp != NULL; tmp = tmp->next) {  //in case team is already added to the list
        if(tmp->id == id)
            return 2;
    }

    int decision = 0;
    for(tmp = teamList->head; tmp != NULL; tmp = tmp->next) {
        if(tmp->id == id) {   //when required team found
            decision = 1;
            toTransfer = malloc(sizeof(struct Node));
            toTransfer->name = (char*)malloc(50*sizeof(char));
            toTransfer->id = tmp->id;
            toTransfer->name = tmp->name;
            toTransfer->goals = tmp->goals;
            toTransfer->points = tmp->points;
            toTransfer->score = tmp->score;
            toTransfer->status = tmp->status;
            toTransfer->date_time.day = tmp->date_time.day;
            toTransfer->date_time.month = tmp->date_time.month;
            toTransfer->date_time.year = tmp->date_time.year;
            toTransfer->date_time.hour = tmp->date_time.hour;
            toTransfer->date_time.minute = tmp->date_time.minute;
            toTransfer->next = NULL;
            favouriteList->size++;

            if(favouriteList->head == NULL) {
                favouriteList->head = toTransfer;
                favouriteList->tail = favouriteList->head;
                favouriteList->head->next = NULL;
                favouriteList->tail->next = NULL;
            }
            else {
                favouriteList->tail->next = toTransfer;
                favouriteList->tail = favouriteList->tail->next;
                favouriteList->tail->next = NULL;
            }
            printf("Team with id %d has been added to the list!!",id);
        }
    }

    return decision;
}

int main () {

    list teams, favouriteTeams;
    position toTransfer;
    favouriteTeams = (list)malloc(sizeof(list));
    favouriteTeams->head = NULL; favouriteTeams->size = 0;
    favouriteTeams->tail = NULL;
    teams = (list)malloc(sizeof(list));
    initialiseTeams("Teams.txt",teams);
    printf("\nThe Teams.txt file has been loaded successfully");

    time_t ti = time(NULL);
    struct tm t = *localtime(&ti);
    srand(time(NULL));

    int userChoice, idToDelete, idOfFavTeam, decision, i;
    char *toSearch;
    struct lineOfFile toAdd;

    do{
        printf("\n\n-----MENU-----\n\n\n");
        printf("1. Add Team\n");
        printf("2. Delete Team\n");
        printf("3. Print Teams\n");
        printf("4. Search Teams\n");
        printf("5. Create Favorite Team List\n");
        printf("6. Exit\n\n");
        printf("Enter your option: "); scanf("%d",&userChoice);

        if(userChoice == 6)
            printf("\nGoodbye!\n\n");
        else if (userChoice < 1 || userChoice > 6)
            printf("\nPlease enter a valid option!!\n");
        else if (userChoice == 1) {
            toAdd.name = (char*)malloc(50*sizeof(char));
            printf("\nEnter name of team: "); scanf("%s",toAdd.name);
            fflush(stdin);
            printf("Enter status of the team: "); scanf("%c",&toAdd.status);
            printf("Enter points of the team: "); scanf("%d",&toAdd.points);
            printf("Enter score of the team: "); scanf("%d",&toAdd.score);
            printf("Enter number of team goals: "); scanf("%d",&toAdd.goals);
            toAdd.date_time.day = t.tm_mday;
            toAdd.date_time.month = t.tm_mon+1;
            toAdd.date_time.year = t.tm_year+1900;
            toAdd.date_time.hour = t.tm_hour;
            toAdd.date_time.minute = t.tm_min;

            toAdd.name[0] = toupper(toAdd.name[0]);  //converting name to standard form (Galatasaray)
            for(i=1; toAdd.name[i] != NULL; i++)
                toAdd.name[i] = tolower(toAdd.name[i]);

            int status=0;
            position temp;
            for(temp=teams->head ; temp!=NULL ; temp = temp->next) {
                if(strcmp(toAdd.name,temp->name) == 0)  //team already exists in the list
                   status = 1;
            }
            if(status == 1)
                printf("\nThis team already exists in the database!");
            else {
                addTeam(teams,toAdd);
                printf("The team has been added!!");
            }
        }
        else if (userChoice == 2) {
            if(teams->size == 0)  //empty list
                printf("\nNo more teams left to delete!!");
            else {
                printf("\nEnter the ID of the team you want to delete: ");
                scanf("%d",&idToDelete);
                deleteTeam(teams,idToDelete);
            }
        }
        else if (userChoice == 3) {
            displayTeams(teams);
        }
        else if (userChoice == 4) {
            toSearch = (char*)malloc(50*sizeof(char));
            printf("\nEnter Team name: "); scanf("%s",&*toSearch);
            if(searchTeams(teams,toSearch,1)==0) //team not found
                printf("There is no team with this name in the database!!!!");
        }
        else if (userChoice == 5) {
            printf("\nEnter team ID you want to add to your favorite list: ");
            scanf("%d",&idOfFavTeam);
            decision = createFavouriteList(teams,favouriteTeams,idOfFavTeam,toTransfer);
            if(decision == 0)  //team not found
                printf("\nTeam with ID %d does not exist in team list!!!!",idOfFavTeam);
            else if(decision == 2)  //team already exists
                printf("\nTeam with this id already exists in the favourite teams list!!");
        }
    }
    while(userChoice != 6);

    Overwrite("favouriteTeams.txt",favouriteTeams);  //overwriting files
    Overwrite("Teams.txt",teams);

    return 0;
}






















/*  //to print
    position tmp;
    for(tmp=teams->head ; tmp!=NULL ; tmp = tmp->next) {
        printf("\n%d;%s;%c;%d;%d;%d;%d/%d/%d %d:%d",tmp->id,tmp->name,tmp->status,tmp->points,tmp->score,tmp->goals,tmp->date_time.day,tmp->date_time.month,tmp->date_time.year,tmp->date_time.hour,tmp->date_time.minute);
    } */












/*  //for add option
    struct lineOfFile toAdd;
    toAdd.name = (char*)malloc(50*sizeof(char));
    printf("Enter name of team: "); scanf("%s",toAdd.name);
    fflush(stdin);
    printf("Enter status of team: "); scanf("%c",&toAdd.status);
    printf("Enter points of team: "); scanf("%d",&toAdd.points);
    printf("Enter score of team: "); scanf("%d",&toAdd.score);
    printf("Enter goals of team: "); scanf("%d",&toAdd.goals);
    toAdd.date_time.day = t.tm_mday;
    toAdd.date_time.month = t.tm_mon+1;
    toAdd.date_time.year = t.tm_year+1900;
    toAdd.date_time.hour = t.tm_hour;
    toAdd.date_time.minute = t.tm_min;
     int status=0;
    position temp;
    for(temp=teams->head ; temp!=NULL ; temp = temp->next) {
        if(strcmp(toAdd.name,temp->name) == 0)
           status = 1;
    }
    if(status == 1)
        printf("\nEnter another team!");
    else
        addTeam(teams,toAdd);*/


