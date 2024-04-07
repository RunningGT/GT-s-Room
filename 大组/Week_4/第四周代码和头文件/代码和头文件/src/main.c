//main.c
#include "D:\1工作室的考核\QG一轮考核\第四周代码和头文件\代码和头文件\inc\binary_sort_tree.h"
#include "function.c"
#include <stdlib.h>
#include <stdio.h>

// 辅助函数：显示节点以及其在树中的位置
void displayNodePosition(BinarySortTreePtr, ElemType);

void menu() {
    printf("\n********** 二叉排序树操作菜单 **********\n");
    printf("1. 初始化插入节点1~6（暂不支持手动插入）\n");
    printf("2. 查找节点并显示位置\n");
    printf("3. 删除节点\n");
    printf("4. 前序遍历 （递归/非递归）\n");
    printf("5. 中序遍历 （递归/非递归）\n");
    printf("6. 后序遍历 （递归/非递归）\n");
    printf("7. 层序遍历\n");
    printf("0. 退出\n");
    printf("**************************************\n");
}

int main() {
    system("chcp 65001");

    BinarySortTree BST;
    BST_init(&BST);
    int choice;
    ElemType element;
    char term;

    do {
        menu();
        printf("请输入您的选择：");
        while (scanf("%d", &choice) != 1) {
            while ((term = getchar()) != '\n' && term != EOF); // 清空缓冲区
            printf("输入无效，请重新输入您的选择：");
        }
        switch (choice) {
            case 1:
//                本来想用户直接输入数字，无奈不会搞
//                连续插入节点
//                printf("请输入要插入的节点值（空格隔开，按a结束）：");
//                while (scanf("%d", &element) == 1) {
//                    BST_insert(&BST, element);
//                }
//                while ((term = getchar()) != 'a' && term != '\n' && term != EOF); // 等待输入'a'来结束输入
                BST_insert(&BST, 0);
                BST_insert(&BST, 0);
                BST_insert(&BST, 0);
                BST_insert(&BST, 0);
                BST_insert(&BST, 0);
                BST_insert(&BST, 0);
                break;
            case 2: // 查找节点
                printf("请输入要查找的节点值：");
                scanf("%d", &element);
                displayNodePosition(&BST, element);
                break;
            case 3: // 删除节点
                printf("请输入要删除的节点值：");
                scanf("%d", &element);
                BST_delete(&BST, element);
                break;
            case 4: // 前序遍历
                BST_preorderR(&BST, printNodeValue);
                printf("\n");
                BST_preorderI(&BST, printNodeValue);
                printf("\n");
                break;
            case 5: // 中序遍历
                BST_inorderR(&BST, printNodeValue);
                printf("\n");
                BST_inorderI(&BST, printNodeValue);
                printf("\n");
                break;
            case 6: // 后序遍历
                BST_postorderR(&BST, printNodeValue);
                printf("\n");
                BST_postorderI(&BST, printNodeValue);
                printf("\n");
                break;
            case 7: // 层序遍历
                BST_levelOrder(&BST, printNodeValue);
                printf("\n");
                break;
            case 0: // 退出
                printf("退出程序。\n");
                break;
            default:
                printf("无效的选择，请重新输入。\n");
                break;
        }
        system("pause");
        system("cls");
    } while (choice != 0);

    return 0;
}

void displayNodePosition(BinarySortTreePtr BST, ElemType value) {
    if (BST_search(BST, value)) {
        printf("节点存在。\n");
        // 这里你可以添加更多逻辑来显示节点位置信息
        // 这可能涉及到修改 BST_search 函数以返回更多信息而不仅仅是存在性
    } else {
        printf("节点不存在。\n");
    }
}


