#include "stack.h"
#include "desk.c"
#include "stack_.c"

int main() {
    // 解决命令行显示中文乱码(GBK->UTF-8)
    system("chcp 65001");

    struct ListNode headNode;
    Node head = &headNode;
    initStack(head);

    char infix[100], postfix[100];
    int result, option;

    do {
        system("cls");
        displayMainMenu();
        if(scanf("%d", &option) == 1) {
            handleOption(head, option, infix, postfix, &result);
        } else {
            printf("无效输入，请输入数字1-10。\n");
            while(getchar() != '\n');  // 清除缓冲区
        }
        printf("按任意键继续...\n");
        system("pause");
        system("cls");
    } while (option != 10);

    return 0;
}
