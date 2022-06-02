#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

struct dateTime {
    int day;
    int month;
    int year;
    int minutes;
    int hours;
};

struct node {
    char *post_ID;
    char *permalink;
    int totalReach;
    int engagedUsers;
    char *type;
    struct dateTime dT;
};

struct listNode {
    struct node data;
    struct listNode* next;
};

struct listRecord {
    struct listNode *front;
    struct listNode *rear;
    int size;
};

struct TreeNode {
    struct listRecord *list;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;

};

int AVLTReeheight(struct TreeNode *);
int max(int, int);
struct TreeNode* SingleRotateWithRight(struct TreeNode *);
struct TreeNode* SingleRotateWithLeft(struct TreeNode *);
struct TreeNode* makeNewNode(struct node);
struct TreeNode* insertPost(struct TreeNode*, struct node);
struct TreeNode* readData(char *);
void displayPosts(struct TreeNode *);
struct listRecord *mostReach(struct TreeNode *);
void mostEngaged(struct TreeNode *);
int highestEngaged(struct TreeNode *);
void printMostEngaged(struct TreeNode *, int);
struct TreeNode* DoubleRotateWithLeft(struct TreeNode *);
struct TreeNode* DoubleRotateWithRight(struct TreeNode *tmp);

#endif // AVLTREE_H_INCLUDED
