#include "stack.h"

void displayMainMenu() {
    printf("\n请选择链栈的基本功能：\n");
    fflush(stdout);
    printf("1. 初始化栈\n");
    fflush(stdout);
    printf("2. 入栈(逐个元素）\n");
    fflush(stdout);
    printf("3. 出栈（逐个元素）\n");
    fflush(stdout);
    printf("4. 判断栈是否为空\n");
    fflush(stdout);
    printf("5. 得到栈顶元素\n");
    fflush(stdout);
    printf("6. 清空栈\n");
    fflush(stdout);
    printf("7. 销毁栈\n");
    fflush(stdout);
    printf("8. 检测栈长度\n");
    fflush(stdout);
    printf("9. 四则运算求值\n");
    fflush(stdout);
    printf("10. 退出\n");
    fflush(stdout);
    printf("请输入您的选择（1-10）：");
}

void handleOption(Node head, int option,char* infix, char* postfix, int* result) {
    E element, topElement;
    int outcome;
    switch (option) {
        case 1:
            initStack(head);
            printf("栈已初始化。\n");
                fflush(stdout);
            break;
        case 2:
            printf("请输入要入栈的元素：");
            fflush(stdout);
            scanf("%d", &element);
            pushStack(head, element);
            printf("元素已入栈。\n");
            fflush(stdout);
            break;
        case 3:
            element = popStack(head);
            if(element != -1)
                printf("出栈的元素为：%d\n", element);
            else
                printf("栈为空，无法出栈。\n");
            fflush(stdout);
            break;
        case 4:
            outcome = isEmptyLStack(head);
            if (outcome)
                printf("栈为空。\n");
            else
                printf("栈非空。\n");
            fflush(stdout);
            break;
        case 5:
            topElement = getTopLStack(head);
            if(topElement != -1)
                printf("栈顶元素为：%d\n", topElement);
            else
                printf("栈为空，无栈顶元素。\n");
            fflush(stdout);
            break;
        case 6:
            clearLStack(head);
            printf("栈已清空。\n");
            fflush(stdout);
            break;
        case 7:
            destroyLStack(&head);
            printf("栈已销毁。\n");
            fflush(stdout);
            break;
        case 8:
            outcome = LStackLength(head);
            printf("栈的长度为：%d\n", outcome);
            fflush(stdout);
            break;
        case 9:
            printf("请输入中缀表达式：");
            scanf("%s", infix);
            infixToPostfix(infix, postfix);
            *result = evaluatePostfix(postfix);
            printf("表达式的结果是：%d\n", *result);
            break;
        case 10:
            printf("程序结束。\n");
            fflush(stdout);
            break;
        default:
            printf("无效的选项，请重新输入。\n");
            fflush(stdout);
    }
}

