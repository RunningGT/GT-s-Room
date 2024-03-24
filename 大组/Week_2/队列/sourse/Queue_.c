//
// Created by 86158 on 2024/3/24.
//
// Queue_.c
#include "Queue.h"

void InitLQueue(LQueue *Q) {
    Q->front = Q->rear = (Node *)malloc(sizeof(Node));
    if (!Q->front) {
        printf("初始化失败，内存分配失败。\n");
        fflush(stdout);
        exit(1);
    }
    Q->front->next = NULL;
    Q->length = 0;
}

void DestoryLQueue(LQueue *Q) {
    if (IsEmptyLQueue(Q)) {
        printf("队列为空。\n");
        free(Q->front);
        Q->front = Q->rear = NULL;
        Q->length = 0;
        return;
    }

    printf("销毁队列中的元素：");
    while (!IsEmptyLQueue(Q)) {
        Node *p = Q->front->next;
        printf("%d ", *(int *)(p->data));  // 这里假设存储的数据是整型。
        Q->front->next = p->next;
        if (Q->rear == p) {
            Q->rear = Q->front;
        }
        free(p->data);  // 若data分配了内存，确保释放
        free(p);
    }
    printf("\n共销毁了 %zu 个元素。\n", Q->length);
    fflush(stdout);

    free(Q->front);
    Q->front = Q->rear = NULL;
    Q->length = 0;
}

Status IsEmptyLQueue(const LQueue *Q) {
    return Q->front == Q->rear;
}

Status GetHeadLQueue(LQueue *Q, void **e) { // 注意，这里的指针需要 double pointer
    if (IsEmptyLQueue(Q)) {
        printf("队列为空。\n");
        fflush(stdout);
        return FALSE;
    }
    Node *p = Q->front->next;
    *e = p->data; // 注意，需要使用 * 来修改传入的指针变量
    return TRUE;
}

int LengthLQueue(LQueue *Q) {
    return Q->length;
}

//入队
Status EnLQueue(LQueue *Q, void *data) {
    Node *s = (Node *)malloc(sizeof(Node));
    if (!s) {
        printf("入队失败，内存分配失败。\n");
        fflush(stdout);
        return FALSE;
    }
    s->data = malloc(sizeof(int));
    if (!s->data) {  // 检查内存分配是否成功
        free(s);
        printf("入队失败，内存分配失败。\n");
        fflush(stdout);
        return FALSE;
    }
    *(int *)(s->data) = *((int *)data);  // 复制数据到新分配的内存
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    Q->length++;
    return TRUE;
}

//出队
Status DeLQueue(LQueue *Q) {
    if (IsEmptyLQueue(Q)) {
        printf("队列为空，无法出队。\n");
        fflush(stdout);
        return FALSE;
    }
    Node *p = Q->front->next;
    Q->front->next = p->next;
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    printf("出队元素：%d。\n", *(int *)(p->data));  // 这里假设存储的数据是整型。
    fflush(stdout);
    free(p->data);  // 若data分配了内存，确保释放
    free(p);
    Q->length--;
    return TRUE;
}

//清空队列
void ClearLQueue(LQueue *Q) {
    while (!IsEmptyLQueue(Q)) {
        DeLQueue(Q);
    }
    Q->length = 0;
}

//这是遍历，英文不好
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q)) {
    if (IsEmptyLQueue(Q)) {
        printf("队列为空。\n");
        fflush(stdout);
        return FALSE;
    }
    Node *p = Q->front->next;
    while (p != NULL) {
        foo(p->data);
        p = p->next;
    }
    printf("\n");
    fflush(stdout);
    return TRUE;
}
