#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"
#include<string.h>

int AVLTReeheight(struct TreeNode *node) {
    if(node == NULL)
        return 0;
    return node->height;
}

int max(int first, int second) {
    if (first > second)
        return first;
    return second;
}

struct TreeNode* SingleRotateWithRight(struct TreeNode *node) {
    struct TreeNode *tmp1 = node->left;
    struct TreeNode *tmp2 = tmp1->right;

    tmp1->right = node;
    node->left = tmp2;

    node->height = max(AVLTReeheight(node->left),AVLTReeheight(node->right))+1;
    tmp1->height = max(AVLTReeheight(tmp1->left),AVLTReeheight(tmp1->right))+1;

    return tmp1;
}

struct TreeNode* SingleRotateWithLeft(struct TreeNode *node) {

    struct TreeNode *tmp1 = node->right;
    struct TreeNode *tmp2 = tmp1->left;

    tmp1->left = node;
    node->right = tmp2;

    node->height = max(AVLTReeheight(node->left), AVLTReeheight(node->right))+1;
    tmp1->height = max(AVLTReeheight(tmp1->left), AVLTReeheight(tmp1->right))+1;

    return tmp1;
}

struct TreeNode* makeNewNode(struct node data) {

    struct TreeNode* tmp = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    tmp->list = malloc(sizeof(struct listRecord));
    tmp->list->front = malloc(sizeof(struct listNode));
    tmp->list->rear = malloc(sizeof(struct listNode));
    tmp->list->front->data.post_ID = (char*)malloc(20*sizeof(char));
    tmp->list->front->data.post_ID = data.post_ID;
    tmp->list->front->data.permalink = (char*)malloc(40*sizeof(char));
    tmp->list->front->data.permalink  = data.permalink;
    tmp->list->front->data.totalReach = data.totalReach;
    tmp->list->front->data.engagedUsers = data.engagedUsers;
    tmp->list->front->data.type = (char*)malloc(6*sizeof(char));
    tmp->list->front->data.type = data.type;
    tmp->list->front->data.dT = data.dT;
    tmp->list->front->next = NULL;
    tmp->list->rear = tmp->list->front;
    tmp->list->size = 1;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->height = 1;
    return(tmp);
}

struct TreeNode* DoubleRotateWithLeft(struct TreeNode *tmp) {
        tmp->left = SingleRotateWithRight(tmp->left);
        return SingleRotateWithLeft(tmp);
}

struct TreeNode* DoubleRotateWithRight(struct TreeNode *tmp) {
        tmp->left = SingleRotateWithLeft(tmp->left);
        return SingleRotateWithRight(tmp);
}

struct TreeNode* insertPost(struct TreeNode* tmp, struct node data) {

    if(tmp == NULL)
        return(makeNewNode(data));

    if(data.totalReach < tmp->list->front->data.totalReach) {
        tmp->left = insertPost(tmp->left, data);
        if(AVLTReeheight(tmp->left) - AVLTReeheight(tmp->right) == 2) {
            if(data.totalReach < tmp->left->list->front->data.totalReach)
                tmp = SingleRotateWithRight(tmp);
            else
                tmp = DoubleRotateWithRight(tmp);
        }
    }
    else if(data.totalReach > tmp->list->front->data.totalReach) {
        tmp->right = insertPost(tmp->right, data);
        if(AVLTReeheight(tmp->right) - AVLTReeheight(tmp->left) == 2) {
            if(data.totalReach > tmp->right->list->front->data.totalReach)
                tmp = SingleRotateWithLeft(tmp);
            else
                tmp = DoubleRotateWithLeft(tmp);
        }
    }
    else if(data.totalReach == tmp->list->front->data.totalReach) {
        tmp->list->rear->next = malloc(sizeof(struct listNode));
        tmp->list->rear->next->data.post_ID = (char*)malloc(20*sizeof(char));
        tmp->list->rear->next->data.post_ID = data.post_ID;
        tmp->list->rear->next->data.permalink = (char*)malloc(40*sizeof(char));
        tmp->list->rear->next->data.permalink  = data.permalink;
        tmp->list->rear->next->data.totalReach = data.totalReach;
        tmp->list->rear->next->data.engagedUsers = data.engagedUsers;
        tmp->list->rear->next->data.type = (char*)malloc(6*sizeof(char));
        tmp->list->rear->next->data.type = data.type;
        tmp->list->rear->next->data.dT = data.dT;
        tmp->list->rear = tmp->list->rear->next;
        tmp->list->rear->next = NULL;
        tmp->list->size++;
    }

    tmp->height = 1 + max(AVLTReeheight(tmp->left),AVLTReeheight(tmp->right));

    return tmp;
}

struct TreeNode* readData(char *filename) {

    struct node *posts;
    int lines = countLines(filename), i;
    posts = (struct node*)malloc(lines*sizeof(struct node));
    fileToArray(posts,filename,lines);

    struct TreeNode* root = NULL;
    for(i=0; i<lines; i++)
        root = insertPost(root,posts[i]);

    return root;
}

void displayPosts(struct TreeNode *tree) {

    if(tree==NULL)
        return;
    displayPosts(tree->left);
    struct listNode *t;
    for(t = tree->list->front; t!=NULL; t = t->next) {
        printf("\nPost ID: %s\nTotal Reach: %d Engaged users: %d",t->data.post_ID,t->data.totalReach,t->data.engagedUsers);
    }
    displayPosts(tree->right);
}

struct listRecord *mostReach(struct TreeNode *tree) {  //Complexity: O(N). This is because of in-order traversal in my method. It could
                                                            //have been more efficient if I had used level order traversal.
    struct listRecord *l;  //to store largest list on left side
    struct listRecord *r;  //to store largest list on right side
    struct listRecord *m = tree->list;  //to store largest list overall

    if(tree->left != NULL) {  //traversing left child
        l = mostReach(tree->left);
        if(l->front->data.totalReach > m->front->data.totalReach)
            m = l;
    }

    if(tree->right != NULL) {   //traversing right side
        r = mostReach(tree->right);
        if(r->front->data.totalReach > m->front->data.totalReach)
            m = r;
    }

    return m;  //returning largest list
}

int highestEngaged(struct TreeNode *tree) {
    int highestLeft = 0;
    int highestRight = 0;
    int highest = 0;

    if(tree->left == NULL && tree->right == NULL) {
        struct listNode *t;
        for(t = tree->list->front; t!=NULL; t = t->next) {
            if(t->data.engagedUsers > highest)
                highest = t->data.engagedUsers;
        }
    }

    if(tree->left != NULL) {
        highestLeft = highestEngaged(tree->left);
        if(highestLeft > highest)
            highest = highestLeft;
    }

    if(tree->right != NULL) {
        highestRight = highestEngaged(tree->right);
        if(highestRight > highest)
            highest = highestRight;
    }

    return highest;
}

void printMostEngaged(struct TreeNode *tree, int highest) {

    if(tree->left != NULL)
        printMostEngaged(tree->left, highest);

    struct listNode *t;
    for(t = tree->list->front; t!=NULL; t = t->next)
        if(t->data.engagedUsers == highest) {
            printf("\nPost ID: %s\nPermalink: %s\nType: %s\nPosted: %d/%d/%d %d:%d\nTotal Reach: %d\nEngaged users: %d\n"
                   ,t->data.post_ID,t->data.permalink,t->data.type,t->data.dT.day,t->data.dT.month,t->data.dT.year,t->data.dT.hours,
                   t->data.dT.minutes,t->data.totalReach,t->data.engagedUsers);
    }

    if(tree->right != NULL)
        printMostEngaged(tree->right, highest);
}

void mostEngaged(struct TreeNode *tree) { //Complexity O(N). Again because of in-order traversal withing the highestEngaged function as well as the printMostEngaged function.
    int highest;                          //would have been more efficient if I had implemented this with level-order traversal
    highest = highestEngaged(tree);  //find the highest number of users within the posts
    printf("\n\nMaximum Engaged Users:");
    printf("\n========================");
    printMostEngaged(tree, highest); //finds the posts with the given number of users and prints them
}
