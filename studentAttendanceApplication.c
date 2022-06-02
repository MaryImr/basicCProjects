//
//  2413284.c
//  studentAttendanceApplication
//
//  Created by Maryam Imran on 09/12/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct studentInformation {   //structure to represent a student
    
    char studentID[4];
    char name[40];
    char departmentCode[4];
};

struct hashTable {   //structure to represent each cell of the hashtable which includes a student structure and a taken flag
    
    struct studentInformation student;
    int isTaken;

};

int keyCalculator(char studentID[3]) {  //to calculate the key for a student based on id
    
    return (studentID[0] - 65 + (studentID[1] - '0') + (studentID[2] - '0'));
}

int hashOne(char studentID[3], int tableSize) {  //implementation of the first hash function
    
    int key = keyCalculator(studentID);
    return ((2*key) % tableSize);
}

int hashTwo(char studentID[3]) {   //implementation of the second hash function
    
    int key = keyCalculator(studentID);
    return (7 - (key % 7));
}

int findNextPrime(int updatedSize) {   //function to find the next prime number from a given integer
    //the function returns the given number if the number itself is prime
    int i, nextPrime = 0, toCheck = updatedSize, isPrime = 1;
    
    do {   //iterating through the given numbers and the numbers after that until a prime is found
        isPrime = 1;  //prime number flag
        for(i=2; i <= toCheck/2; i++) {   //checking for divisibility
            if(toCheck % i == 0) {
                isPrime = 0;
            }
        }
        toCheck++;
    }while(isPrime == 0);
    nextPrime = toCheck - 1;
    
    return nextPrime;
}

int quadraticProbing(int i) {   //implementation of quadratic probing
    return (i*i);
}

int doubleHashing(int i, char studentID[3]) {   //implementation of double hashing
    return (i * hashTwo(studentID));
}

int addStudent(struct studentInformation student, struct hashTable* table, int tableSize, int collisionRes) {
    //to add a student based on the parameters
    
    int res = 0, i=0, added = 0, index;
    
    if(collisionRes == 1) {  //double hashing
        
        do {    //iterating through the cells in the hash table
            index = ((hashOne(student.studentID, tableSize) + doubleHashing(i, student.studentID)) % tableSize);
            if(strcmp(table[index].student.studentID,student.studentID) == 0) {  //if the id already exists in the table
                res = 1;
                break;
            }
            else if(table[index].isTaken == 0) {   //if an empty cell is found for storage
                strcpy(table[index].student.name, student.name);
                strcpy(table[index].student.studentID, student.studentID);
                strcpy(table[index].student.departmentCode, student.departmentCode);
                added = 1;
                res = 0;
                table[index].isTaken = 1;
            }
            else {   //keep iterating
                i++;
                added = 0;
            }
        }while(added == 0);
    }
    else if(collisionRes == 2) {  //quadratic probing
        
        do {   //iterating through the cells in the hash table
            index = ((hashOne(student.studentID, tableSize) + quadraticProbing(i)) % tableSize);
            if(strcmp(table[index].student.studentID,student.studentID) == 0) {   //if the id already exists in the table
                res = 1;
                break;
            }
            else if(table[index].isTaken == 0) {   //if an empty cell is found for storage
                strcpy(table[index].student.name, student.name);
                strcpy(table[index].student.departmentCode, student.departmentCode);
                strcpy(table[index].student.studentID, student.studentID);
                added = 1;
                res = 0;
                table[index].isTaken = 1;
            }
            else {   //keep iterating
                i++;
                added = 0;
            }
        }while(added == 0);
    }
    return res;
}

void printTable(struct hashTable* table, int size) {   //to print the table
    
    int i;
    printf("\nIndex\t\tID\t\t\tName\t\t\tDepartment");
    for(i=0; i<size; i++) {
        if(table[i].isTaken == 1)   //if a student is stored
            printf("\n%d\t\t\t%s\t\t\t%s\t\t\t%s", i, table[i].student.studentID, table[i].student.name, table[i].student.departmentCode);
        else   //else just print the index
            printf("\n%d", i);
    }
    
}

int searchStudent (struct hashTable* table, int tableSize, char id[4], int collisionRes) {
    //to search a student
    int res = 0, i=0, index;
    
    if(collisionRes == 1) {  //double hashing
        
        do {   //iterating through the table
            index = ((hashOne(id, tableSize) + doubleHashing(i, id)) % tableSize);
            if(strcmp(table[index].student.studentID,id) == 0) {   //if the student is found
                res = 1;
                printf("\nName: %s", table[index].student.name);
                printf("\nDepartment: %s", table[index].student.departmentCode);
                break;
            }
            else if(table[index].isTaken == 0) {   //if an empty cell is found where the student would've been stored had it existed in the table
                res = 0;
                break;
            }
            else {   //iterating
                i++;
            }
        }while(res != 1);
    }
    else if(collisionRes == 2) {   //quadratic probing
        
        do {   //iterating through the table
            index = ((hashOne(id, tableSize) + quadraticProbing(i)) % tableSize);
            if(strcmp(table[index].student.studentID,id) == 0) {   //if the student is found
                res = 1;
                printf("\nName: %s", table[index].student.name);
                printf("\nDepartment: %s", table[index].student.departmentCode);
            }
            else if(table[index].isTaken == 0) {   //if an empty cell is found where the student would've been stored had it existed in the table
                res = 0;
                break;
            }
            else {   //iterating
                i++;
                res = 0;
            }
        }while(res != 1);
    }
    
    return res;
    
}

int newTableSize(int oldTableSize) {   //calculating new table size based on the old one
    int size = oldTableSize*2;
    return findNextPrime(size);
}

int main(int argc, const char * argv[]) {
    
    int collisionResolutionType, tableSize = 11, menuChoice, i, addRes, searchRes, studentsAdded = 0, oldSize;
    float loadFactor;
    char searchID[4];
    struct studentInformation tempStudent;
    
    struct hashTable* attendanceList;
    attendanceList = (struct hashTable*) malloc(tableSize * (sizeof(struct hashTable)));   //allocating initial memory to hash table
    
    for(i=0; i<tableSize; i++)      //initializig all taken flags to zero
        attendanceList[i].isTaken = 0;
    
     
    do {    //to get user's preferred collision resolution method
        printf("Which collision resoution technique do you want us to apply?\n");
        printf("   1)Double Hashing\n");
        printf("   2)Quadratic Probing\n");
        printf("\nYour Choice: ");
        scanf("%d", &collisionResolutionType);
        
        if(collisionResolutionType != 1 && collisionResolutionType != 2)
            printf("\nPlease select a valid option!\n");
        
    }while(collisionResolutionType != 1 && collisionResolutionType != 2);
    
    do{     //loop for menu until exit selected
        
        printf("\n\nPlease Select an Option!\n");
        printf("   1)Add a student\n");
        printf("   2)Search a student\n");
        printf("   3)Print Table\n");
        printf("   4)Exit\n");
        printf("Your choice: ");
        scanf("%d",&menuChoice);
        
        if(menuChoice == 4) {
            printf("\nProgram Exited! Goodbye!\n\n");
        }
        else if (menuChoice == 1) {    //to add new student
            printf("\nEnter unique identifier: ");
            scanf("%s",&tempStudent.studentID);
            printf("Enter name: ");   //please input name without a space between name and surname because scanf stops at space
            scanf("%s",&tempStudent.name);
            printf("Enter department: ");
            scanf("%s",&tempStudent.departmentCode);
            
            addRes = addStudent(tempStudent, attendanceList, tableSize, collisionResolutionType);
            
            if(addRes == 0) {
                printf("\n%s has been registered!", tempStudent.name);
                studentsAdded++;
            }
            else {
                printf("\nStudent with this ID has already been added! Please provide a unique ID!");
            }
            
            loadFactor = (float)studentsAdded/(float)tableSize;
            if(loadFactor > 0.5) {   //rehashing
                oldSize = tableSize;
                tableSize = newTableSize(tableSize);
                attendanceList = realloc(attendanceList, tableSize);  //increasing memory
                for(i=oldSize; i<tableSize; i++) {
                    attendanceList[i].isTaken = 0;  //setting all the new cells' taken flags to 0
                }
                
                for(i=0; i<oldSize; i++) {  //re-adding all teh values, please note their is some slight problem happening when reallocation is done //above. It results in the first student added to the hashtable to be lost after rehashing
                    if(attendanceList[i].isTaken == 1) {
                        attendanceList[i].isTaken = 0;
                        strcpy(tempStudent.name,attendanceList[i].student.name);
                        strcpy(tempStudent.studentID,attendanceList[i].student.studentID);
                        strcpy(tempStudent.departmentCode,attendanceList[i].student.departmentCode);
                        strcpy(attendanceList[i].student.name, "");
                        strcpy(attendanceList[i].student.studentID, "");
                        strcpy(attendanceList[i].student.departmentCode, "");
                        addRes = addStudent(tempStudent, attendanceList, tableSize, collisionResolutionType);
                    }
                }
            }
        }
        else if (menuChoice == 2) {  //searching
            printf("\nEnter unique identifier: ");
            scanf("%s",&searchID);
            searchRes = searchStudent(attendanceList, tableSize, searchID, collisionResolutionType);
            
            if(searchRes == 0) {
                printf("\nStudent not found!");
            }
            
        }
        else if (menuChoice == 3) {   //printing
            printTable(attendanceList, tableSize);
        }
        else {  //invalid choice
            printf("\nPlease select a valid choice!");
        }
        
    }while(menuChoice != 4);
    
    return 0;
    
}
