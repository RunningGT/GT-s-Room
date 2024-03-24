// Queue_.h
#ifndef QUEUE__H_INCLUDED
#define QUEUE__H_INCLUDED

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct LQueue {
    Node *front;
    Node *rear;
    size_t length;
} LQueue;

typedef enum {
    FALSE = 0,
    TRUE = 1
} Status;

//各种声明来袭
void InitLQueue(LQueue *Q);
void DestoryLQueue(LQueue *Q);
Status IsEmptyLQueue(const LQueue *Q);
Status GetHeadLQueue(LQueue *Q, void **e);
int LengthLQueue(LQueue *Q);
Status EnLQueue(LQueue *Q, void *data);
Status DeLQueue(LQueue *Q);
void ClearLQueue(LQueue *Q);
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q));
void LPrint(void *q);
void handleOption(LQueue *queue, int option);
void mainMenu(LQueue *queue);

#endif
