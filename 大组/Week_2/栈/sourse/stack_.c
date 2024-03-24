//真不知道popStack函数有啥问题，找了半天呜呜
#include "stack.h"

void initStack(Node head) {
    head->next = NULL;
}

int pushStack(Node head, E element) {
    Node node = (Node)malloc(sizeof(struct ListNode));
    if (node == NULL) return 0;
    node->next = head->next;
    node->element = element;
    head->next = node;
    return 1;
}

int isEmptyLStack(Node head){
    return head->next == NULL;
}

E getTopLStack(Node head) {
    // 取栈顶
    if (isEmptyLStack(head)) return -1;
    return head->next->element;
}

int popStack(Node head) {
    // 空栈出栈
    if (isEmptyLStack(head)) return -1;
    Node top = head->next;
    head->next = top->next;
    E e = top->element;
    free(top);
    return e;
}

int clearLStack(Node head){
    while (!isEmptyLStack(head)){
        popStack(head);
    }
    return 1;
}

int destroyLStack(Node *head) {
    clearLStack(*head);
    free(*head);
    *head = NULL;
    return 1;
}

int LStackLength(Node head) {
    int length = 0;
    Node current = head->next;
    while (current) {
        length++;
        current = current->next;
    }
    return length;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 比较操作符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 中缀表达式转后缀表达式
void infixToPostfix(char* infix, char* postfix) {
    // 初始化栈
    struct ListNode stackHead;
    Node stack = &stackHead;
    initStack(stack);

    int i = 0, j = 0;
    char c, t;

    while ((c = infix[i++]) != '\0') {
        if (c == '(') {
            // 左括号直接入栈！！
            pushStack(stack, c);
        } else if (c == ')') {
            // 右括号则弹出栈元素直到遇到左括号~
            while (!isEmptyLStack(stack) && getTopLStack(stack) != '(') {
                postfix[j++] = popStack(stack);
            }
            popStack(stack);
        } else if (isOperator(c)) {
            // 操作符需要比较其优先级
            while (!isEmptyLStack(stack) && precedence(getTopLStack(stack)) >= precedence(c)) {
                postfix[j++] = popStack(stack);
            }
            pushStack(stack, c);
        } else {
            // 操作数直接输出到后缀表达式
            postfix[j++] = c;
        }
    }

    // 弹出栈中剩余的操作符
    while (!isEmptyLStack(stack)) {
        postfix[j++] = popStack(stack);
    }

    postfix[j] = '\0';
}

// 计算后缀表达式的结果
int evaluatePostfix(char* postfix) {
    // 初始化栈
    struct ListNode stackHead;
    Node stack = &stackHead;
    initStack(stack);

    int i = 0;
    char c;
    int val1, val2;

    while ((c = postfix[i++]) != '\0') {
        if (isOperator(c)) {
            // 操作符——>弹出两个元素计算
            val2 = popStack(stack);
            val1 = popStack(stack);
            switch (c) {
                case '+': pushStack(stack, val1 + val2); break;
                case '-': pushStack(stack, val1 - val2); break;
                case '*': pushStack(stack, val1 * val2); break;
                case '/': pushStack(stack, val1 / val2); break;
            }
        } else {
            // 如果是操作数，则直接入栈
            pushStack(stack, c - '0'); // 将字符转换为整数
        }
    }

    // 最终结果在栈顶
    return popStack(stack);
}


