#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef int E;

struct ListNode {
    E element;
    struct ListNode *next;
};

typedef struct ListNode *Node;

//"Postfix" 是“后缀”表示法
//"Infix"   是“中缀”表示法
void initStack(Node head);
int pushStack(Node head, E element);
int isEmptyLStack(Node head);
E getTopLStack(Node head);
int clearLStack(Node head);
int destroyLStack(Node *head);
int LStackLength(Node head);
void infixToPostfix(char* infix, char* postfix);
int evaluatePostfix(char* postfix);

#endif // STACK_H
