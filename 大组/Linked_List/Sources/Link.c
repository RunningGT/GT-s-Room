//
// Created by 86158 on 2024/3/17.
//
#include <stdio.h> // 包含标准输入输出库
#include <stdlib.h> // 包含标准库，用于内存分配

// 定义单链表的节点结构
typedef struct Node {
    int data; // 节点数据
    struct Node* next; // 指向下一个节点的指针
} Node;

void initList(Node **head){
    *head = NULL;   //头结点默认下一个为NULL
}

// 创建新节点的函数
Node* newNode(int data) {
    Node *node = (Node*)malloc(sizeof(Node)); // 动态分配内存
    node->data = data; // 设置节点数据
    node->next = NULL; // 初始化下一个节点指针为NULL
    return node; // 返回新节点的指针
}

// 在链表末尾添加节点的函数
void append(Node** head, int data) {
    Node* new_node = newNode(data); // 创建新节点
    if (*head == NULL) { // 如果链表为空
        *head = new_node; // 新节点成为头节点
        return;
    }
    Node* last = *head; // 从头节点开始
    while (last->next != NULL) { // 遍历到链表末尾
        last = last->next;
    }
    last->next = new_node; // 在末尾添加新节点
}

//插入节点的函数
_Bool insertList(Node *head, int element, int index){
    if(index < 1) return 0;
    while (--index) {
        head = head->next;
        if(head == NULL) return 0;
    }
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL) return 0;   //创建一个新的结点，如果内存空间申请失败返回0
    node->data = element;   //将元素保存到新创建的结点中
    node->next = head->next;   //先让新插入的节点指向原本位置上的这个结点
    head->next = node;   //接着将前驱结点指向新的这个结点
    return 1;
}

// 交换任意两个节点数据的函数
void swapData(Node* head, int x, int y) {
    if (x == y) return; // 如果x和y相同，则不需要交换

    Node* current = head;
    Node* nodeX = NULL;
    Node* nodeY = NULL;

    // 遍历链表，找到x和y的节点
    while (current != NULL) {
        if (current->data == x) {
            nodeX = current;
        } else if (current->data == y) {
            nodeY = current;
        }
        current = current->next;
    }

    // 如果找到了x和y的节点，则交换它们的数据
    if (nodeX != NULL && nodeY != NULL) {
        int temp = nodeX->data;
        nodeX->data = nodeY->data;
        nodeY->data = temp;
    }
}

// 查找链表中点的函数
Node* findMidpoint(Node* head) {
    Node *slow_ptr = head, *fast_ptr = head; // 使用两个指针
    while (fast_ptr != NULL && fast_ptr->next != NULL && fast_ptr->next->next != NULL) { // 快指针移动速度是慢指针的两倍
        slow_ptr = slow_ptr->next; // 慢指针移动一步
        fast_ptr = fast_ptr->next->next; // 快指针移动两步
    }
    return slow_ptr; // 当快指针到达末尾时，慢指针在中点
}

// 检查链表是否有环的函数
int hasCycle(Node* head) {
    Node *slow_ptr = head, *fast_ptr = head; // 使用两个指针
    while (fast_ptr && fast_ptr->next) { // 遍历链表
        slow_ptr = slow_ptr->next; // 慢指针移动一步
        fast_ptr = fast_ptr->next->next; // 快指针移动两步
        if (slow_ptr == fast_ptr) { // 如果两指针相遇
            return 1; // 存在环
        }
    }
    return 0; // 不存在环
}

// 新链表头插法——反转链表的函数（非递归）
void reverseIterative(Node** head) {
    Node *prev = NULL, *current = *head, *next = NULL; // 使用三个指针
    while (current != NULL) { // 遍历链表
        next = current->next; // 保存下一个节点
        current->next = prev; // 反转当前节点的指针
        prev = current; // 移动prev指针
        current = next; // 移动current指针
    }
    *head = prev; // 新的头节点是prev
}

// 反转链表的函数（递归）
Node* reverseRecursive(Node* head) {
    if (head == NULL || head->next == NULL) { // 基本情况
        return head; // 返回头节点
    }
    Node* rest = reverseRecursive(head->next); // 递归反转剩余部分
    head->next->next = head; // 反转当前节点的指针
    head->next = NULL; // 设置当前节点的下一个节点为NULL
    return rest; // 返回新的头节点
}

// 打印链表的函数
void printList(Node* head) {
    while (head != NULL) { // 遍历链表
        printf("%d -> ", head->data); // 打印节点数据
        head = head->next; // 移动到下一个节点
    }
    printf("NULL\n"); // 打印链表结束
}

// 主函数，演示各种操作
int main() {
    // 解决命令行显示中文乱码(GBK->UTF-8)
    system("chcp 65001");
    Node *head;
    initList(&head); // 初始化头节点为NULL

    append(&head, 1); // 在链表末尾添加节点
    append(&head, 2);
    append(&head, 3);
    append(&head, 5);
    // 在链表中间插入节点
    if(insertList(head, 4, 3)) {
        printf("插入成功！\n");
        fflush(stdout);
    } else {
        printf("插入失败！\n");
        fflush(stdout);
    }

    printf("原始链表: "); // 打印原始链表
    printList(head);

    int a = 0, b = 0;
    printf("请输入要交换的两个节点序号（用空格隔开）：\n");
    fflush(stdout);
    scanf("%d %d",&a, &b);
    if(a>=1 && a<=5 && b>=1 && b<=5) {
        swapData(head, a, b); // 成对交换节点
        printf("交换后: "); // 打印交换后的链表
        printList(head);
    }
    else {
        printf("错误，链表不改变\n");
        fflush(stdout);
    }

    Node* midpoint = findMidpoint(head); // 查找中点
    printf("中位数: %d\n", midpoint->data); // 打印中点数据

    printf("链表成环: %s\n", hasCycle(head) ? "Yes" : "No"); // 检查是否有环

    head = reverseRecursive(head); // 递归反转链表
    printf("反转后: ");
    printList(head);

    reverseIterative(&head); // 环
    printf("反转后: ");
    printList(head);

    return 0; // 程序结束
}
