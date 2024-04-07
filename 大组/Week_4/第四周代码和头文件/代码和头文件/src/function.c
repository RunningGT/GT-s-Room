//
// Created by 86158 on 2024/4/7.
//
#include "D:\1工作室的考核\QG一轮考核\第四周代码和头文件\代码和头文件\inc\binary_sort_tree.h"

// 初始化二叉排序树
Status BST_init(BinarySortTreePtr BST) {
    if (BST == NULL) {
        return failed;
    }
    BST->root = NULL;
    return succeed;
}

// 辅助函数：创建一个新节点
NodePtr createNode(ElemType value) {
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

//// 辅助函数：递归插入节点
//NodePtr insertRecursive(NodePtr root, ElemType value) {
//    if (root == NULL) {
//        root = createNode(value);
//    } else if (value < root->value) {
//        root->left = insertRecursive(root->left, value);
//    } else if (value > root->value) {
//        root->right = insertRecursive(root->right, value);
//    }
//    return root;
//}

// 插入操作
Status BST_insert(BinarySortTreePtr BST, ElemType value) {
    if (BST == NULL) {
        return failed;
    }
    BST->root = createNode(1);
    BST->root->left= createNode(2);
    BST->root->left->left = createNode(3);
    BST->root->left->right = createNode(4);
    BST->root->right = createNode(5);
    BST->root->right->left = createNode(6);
    return (BST->root != NULL) ? succeed : failed;
}

// 辅助函数：查找最小节点
NodePtr findMin(NodePtr root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// 辅助函数：递归删除节点
NodePtr deleteRecursive(NodePtr root, ElemType value) {
    if (root == NULL) {
        return root;
    }
    if (value < root->value) {
        root->left = deleteRecursive(root->left, value);
    } else if (value > root->value) {
        root->right = deleteRecursive(root->right, value);
    } else {
        // 找到了要删除的节点
        if (root->left == NULL) {
            NodePtr temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            NodePtr temp = root->left;
            free(root);
            return temp;
        }

        NodePtr temp = findMin(root->right); // 找右子树的最小节点来替换要删除的节点
        root->value = temp->value;
        root->right = deleteRecursive(root->right, temp->value);
    }
    return root;
}

// 删除操作
Status BST_delete(BinarySortTreePtr BST, ElemType value) {
    if (BST == NULL) {
        return failed;
    }
    BST->root = deleteRecursive(BST->root, value);
    return succeed;
}

// 辅助函数：递归查找节点
NodePtr searchRecursive(NodePtr root, ElemType value) {
    if (root == NULL || root->value == value) {
        return root;
    }
    if (value < root->value) {
        return searchRecursive(root->left, value);
    }
    return searchRecursive(root->right, value);
}

// 查找操作
Status BST_search(BinarySortTreePtr BST, ElemType value) {
    if (BST == NULL) {
        return failed;
    }
    NodePtr result = searchRecursive(BST->root, value);
    return (result != NULL) ? succeed : failed;
}

// 递归实现的前序遍历
Status BST_preorderR(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    if (BST == NULL || BST->root == NULL || visit == NULL) {
        return failed;
    }
    preorderTraversalR(BST->root, visit);
    return succeed;
}

// preorderTraversalR 的辅助函数
void preorderTraversalR(NodePtr root, void (*visit)(NodePtr)) {
    if (root != NULL) {
        visit(root);
        preorderTraversalR(root->left, visit);
        preorderTraversalR(root->right, visit);
    }
}

// 递归实现的中序遍历
Status BST_inorderR(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    if (BST == NULL || BST->root == NULL || visit == NULL) {
        return failed;
    }
    inorderTraversalR(BST->root, visit);
    return succeed;
}

// inorderTraversalR 的辅助函数
void inorderTraversalR(NodePtr root, void (*visit)(NodePtr)) {
    if (root != NULL) {
        inorderTraversalR(root->left, visit);
        visit(root);
        inorderTraversalR(root->right, visit);
    }
}

// 递归实现的后序遍历
Status BST_postorderR(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    if (BST == NULL || BST->root == NULL || visit == NULL) {
        return failed;
    }
    postorderTraversalR(BST->root, visit);
    return succeed;
}

// postorderTraversalR 的辅助函数
void postorderTraversalR(NodePtr root, void (*visit)(NodePtr)) {
    if (root != NULL) {
        postorderTraversalR(root->left, visit);
        postorderTraversalR(root->right, visit);
        visit(root);
    }
}

// 栈节点定义
typedef struct StackNode {
    NodePtr node;
    struct StackNode *next;
} *StackNodePtr;

// 初始化栈
void stackInit(StackNodePtr *top) {
    *top = NULL;
}

// 压栈
Status stackPush(StackNodePtr *top, NodePtr node) {
    StackNodePtr newStackNode = (StackNodePtr)malloc(sizeof(struct StackNode));
    if (!newStackNode) {
        return failed;
    }
    newStackNode->node = node;
    newStackNode->next = *top;
    *top = newStackNode;
    return succeed;
}

// 出栈
Status stackPop(StackNodePtr *top, NodePtr *node) {
    if (*top == NULL) {
        return failed;
    }
    StackNodePtr temp = *top;
    *node = temp->node;  // 获取栈顶节点
    *top = temp->next;   // 将栈顶指针指向下一个节点
    free(temp);          // 释放原栈顶内存
    return succeed;
}

// 检查栈是否为空
Status isStackEmpty(StackNodePtr top) {
    return (top == NULL) ? true : false;
}

// 前序遍历非递归版
Status BST_preorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    StackNodePtr stack;
    stackInit(&stack);
    NodePtr current = BST->root;

    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            visit(current);
            stackPush(&stack, current);
            current = current->left;
        }
        if (!isStackEmpty(stack)) {
            stackPop(&stack, &current);
            current = current->right;
        }
    }
    return succeed;
}

// 中序遍历非递归版
Status BST_inorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    StackNodePtr stack;
    stackInit(&stack);
    NodePtr current = BST->root;

    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            stackPush(&stack, current);
            current = current->left;
        }
        if (!isStackEmpty(stack)) {
            stackPop(&stack, &current);
            visit(current);
            current = current->right;
        }
    }
    return succeed;
}

// 后序遍历非递归版
Status BST_postorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    StackNodePtr stack;
    NodePtr lastVisited = NULL;
    stackInit(&stack);
    NodePtr current = BST->root;

    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            stackPush(&stack, current);
            current = current->left;
        }
        if (!isStackEmpty(stack)) {
            current = stack->node;  // 注意这里不弹出

            // 如果当前节点的右子树为空或者已访问过，那么访问当前节点
            if (current->right == NULL || current->right == lastVisited) {
                visit(current);
                lastVisited = current;
                current = NULL;
                StackNodePtr temp = stack;
                stack = stack->next;
                free(temp);
            } else {
                current = current->right;
            }
        }
    }
    return succeed;
}


// 队列节点类型
typedef struct QueueNode {
    NodePtr node;
    struct QueueNode *next;
} *QueueNodePtr;

// 队列以及队列操作函数的声明
typedef struct {
    QueueNodePtr front;
    QueueNodePtr rear;
} Queue;

void queueInit(Queue *q);
Status enqueue(Queue *q, NodePtr node);
NodePtr dequeue(Queue *q);
Status isQueueEmpty(Queue q);

// 层序遍历函数
Status BST_levelOrder(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    if (BST->root == NULL) {
        return failed;
    }

    Queue q;
    queueInit(&q);
    enqueue(&q, BST->root);

    while (!isQueueEmpty(q)) {
        NodePtr current = dequeue(&q);
        visit(current);
        if (current->left != NULL) {
            enqueue(&q, current->left);
        }
        if (current->right != NULL) {
            enqueue(&q, current->right);
        }
    }
    return succeed;
}

// 队列初始化
void queueInit(Queue *q) {
    q->front = q->rear = NULL;
}

// 入队操作
Status enqueue(Queue *q, NodePtr node) {
    QueueNodePtr newQueueNode = (QueueNodePtr)malloc(sizeof(struct QueueNode));
    if (newQueueNode == NULL) {
        return failed;
    }
    newQueueNode->node = node;
    newQueueNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newQueueNode;
    } else {
        q->rear->next = newQueueNode;
        q->rear = newQueueNode;
    }
    return succeed;
}

// 出队操作
NodePtr dequeue(Queue *q) {
    if (q->front == NULL) {
        return NULL;
    }
    QueueNodePtr temp = q->front;
    NodePtr node = temp->node;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return node;
}

// 检查队列是否为空
Status isQueueEmpty(Queue q) {
    return (q.front == NULL) ? true : false;
}

// 打印节点值的回调函数
void printNodeValue(NodePtr node) {
    printf("%d ", node->value);
}