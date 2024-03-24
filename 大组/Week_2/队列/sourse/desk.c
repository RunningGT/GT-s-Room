//
// Created by 86158 on 2024/3/24.
//
//desk.c
#include "Queue.h"

void mainMenu(LQueue *queue) {
    int option;
    do {
        printf("\n请选择链式队列的基本功能：\n");
        fflush(stdout);
        printf("1. 初始化队列\n");
        fflush(stdout);
        printf("2. 入队\n");
        fflush(stdout);
        printf("3. 出队\n");
        fflush(stdout);
        printf("4. 查看队头元素\n");
        fflush(stdout);
        printf("5. 检查队列是否为空\n");
        fflush(stdout);
        printf("6. 清空队列\n");
        fflush(stdout);
        printf("7. 销毁队列\n");
        fflush(stdout);
        printf("8. 遍历队列\n");
        fflush(stdout);
        printf("9. 队列长度\n");
        fflush(stdout);
        printf("10. 退出\n");
        fflush(stdout);
        printf("请输入您的选择（1-10）：");
        fflush(stdout);
        while (scanf("%d", &option) != 1 || option < 1 || option > 10) { // 检查是否成功读取一个整数
            printf("无效的选项，请输入一个介于1到10之间的整数：\n");
            fflush(stdout);
            while (getchar() != '\n'); // 清除错误的输入直到下一个换行符
        }
        handleOption(queue, option);
        printf("按任意键继续...\n");
        fflush(stdout);
        system("pause");
        system("cls");
    } while (option != 10);
}


void handleOption(LQueue *queue, int option) {
    int data;
    int *dataptr;
    switch (option) {
        case 1:
            InitLQueue(queue);
            printf("队列已初始化。\n");
            fflush(stdout);
            break;
        case 2:
            printf("请输入要入队的元素：");
            fflush(stdout);
            while (scanf("%d", &data) != 1) {
                printf("输入无效，请输入一个整数：");
                fflush(stdout);
                while (getchar() != '\n');  // 清除错误的输入直到下一个换行符
            }
            dataptr = (int*)malloc(sizeof(int));  // 动态分配内存
            *dataptr = data;  // 存入数据
            if (dataptr && EnLQueue(queue, dataptr)) {
                printf("元素 %d 已入队。\n", data);
                fflush(stdout);
            }
            else {
                printf("入队失败。\n");
                fflush(stdout);
                free(dataptr); // 如果入队失败，释放先前分配的内存
            }
            break;
        case 3:
            printf("元素 ");
            if (DeLQueue(queue)) {
                printf("已出队。\n");
                fflush(stdout);
            } else {
                printf("队列为空，无法出队。\n");
                fflush(stdout);
            }
            break;
        case 4:
            if (!IsEmptyLQueue(queue)) {
                int *head;
                if (GetHeadLQueue(queue, (void**)&head))  // 注意传递指针的地址
                    printf("队头元素为：%d\n", *head);
                else
                    printf("获取队头元素失败。\n");
            } else {
                printf("队列为空，无队头元素。\n");
            }
            fflush(stdout);
            break;
        case 5:
            if (IsEmptyLQueue(queue))
                printf("队列为空。\n");
            else
                printf("队列非空。\n");
            fflush(stdout);
            break;
        case 6:
            ClearLQueue(queue);
            printf("队列已清空。\n");
            fflush(stdout);
            break;
        case 7:
            DestoryLQueue(queue);
            printf("队列已销毁。\n");
            fflush(stdout);
            break;
        case 8:
            TraverseLQueue(queue, LPrint);
            break;
        case 9:
            printf("队列长度为：%d\n", LengthLQueue(queue));
            fflush(stdout);
            break;
        case 10:
            printf("程序结束。\n");
            fflush(stdout);
            break;
        default:
            printf("无效的选项，请重新输入。\n");
            fflush(stdout);
            break;
    }
}

void LPrint(void *q) {
    int *data = (int *)q;
    printf("%d ", *data);
}
