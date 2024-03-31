// desk.c
#include "head.h"

void showDesk() {
    int choice;
    int dataSize; // 储存数据量的大小
    int sortRepeat; // 排序重复次数
    int sortType;  // 排序类型选择

    do {
        printf("\n----- 排序算法测试菜单 -----\n");
        fflush(stdout); // 刷新输出缓冲区
        printf("1. 输入并测试小数据量排序性能（大小必须在 100 到 2000 之间）：\n");
        fflush(stdout);
        printf("2. 输入并测试大数据量排序性能（大小必须在 10000 到 200000 之间）：\n");
        fflush(stdout);
        printf("3. 退出程序\n");
        fflush(stdout);
        printf("请输入您的选择：");
        fflush(stdout);
        scanf("%d", &choice);

        // 增加的新功能
        if (choice == 1 || choice == 2) {
            printf("请输入数据量的大小：");
            fflush(stdout);
            scanf("%d", &dataSize);

            // 修正的数值限制
            if (choice == 1 && (dataSize < 100 || dataSize > 2000)) {
                printf("小数据量的大小必须在 100 到 2000 之间。\n");
                continue;  // 跳过本轮循环，重新显示菜单
            }

            if (choice == 2 && (dataSize < 10000 || dataSize > 200000)) {
                printf("大数据量的大小必须在 10000 到 200000 之间。\n");
                continue;  // 跳过本轮循环，重新显示菜单
            }

            printf("请选择: 1.选择单种排序并保存结果 2.比较所有排序不保存结果: ");
            fflush(stdout);
            scanf("%d", &sortType);

            if (sortType == 2) {
                printf("请输入排序重复次数：");
                fflush(stdout);
                scanf("%d", &sortRepeat);
            }
        }

        switch (choice) {
            case 1:
                if (sortType == 1) {
                    performTest("小数据量排序测试", dataSize, true, 0);
                } else if (sortType == 2) {
                    performTest("小数据量排序测试", dataSize, false, sortRepeat);
                }
                break;
            case 2:
                if (sortType == 1) {
                    performTest("大数据量排序测试", dataSize, true, 0);
                } else if (sortType == 2) {
                    performTest("大数据量排序测试", dataSize, false, sortRepeat);
                }
                break;
            case 3:
                printf("退出程序...\n");
                fflush(stdout);
                break;
            default:
                printf("无效的选择，请输入1到3之间的数字。\n");
                fflush(stdout);
                break;
        }
    } while (choice != 3);
}

// 帮助函数，用于生成随机整数，并保存到文件
void generateTestData(const char* filename, int length) {
    int *arr = (int*)malloc(sizeof(int) * length);
    if (!arr) {
        fprintf(stderr, "内存分配失败。\n");
        return;
    }

    // 随机数生成
    for (int i = 0; i < length; i++) {
        arr[i] = rand() % 10000; // 生成0到9999之间的随机数
    }

    // 写入文件
    writeArrayToFile(filename, arr, length);

    free(arr); // 释放分配的内存
}

void performTest(const char* testDescription, int length, int saveResult, int repeatCount) {
    int *data = (int*)malloc(sizeof(int) * length);
    if (!data) {
        fprintf(stderr, "内存分配失败。\n");
        return;
    }

    // 读取数据
    readArrayFromFile("test_data.txt", data, length);

    printf("\n--- 正在进行%s ---\n", testDescription);
    fflush(stdout);

    // 分别为每种排序方法声明一个用来记录总时间的变量
    double totalTimeBubble = 0.0, totalTimeInsert = 0.0, totalTimeMerge = 0.0, totalTimeQuick = 0.0, totalTimeCount = 0.0, totalTimeRadix = 0.0;

    // 用户选择执行一种排序并保存结果
    if (saveResult) {
        printf("请选择一个排序算法执行并保存结果:\n");
        fflush(stdout);
        printf("1. 普通冒泡排序\n");
        fflush(stdout);
        printf("2. 优化冒泡排序1\n");
        fflush(stdout);
        printf("3. 优化冒泡排序2\n");
        fflush(stdout);
        printf("4. 优化冒泡排序3\n");
        fflush(stdout);
        printf("5. 归并排序\n");
        fflush(stdout);
        printf("6. 快速排序\n");
        fflush(stdout);
        printf("7. 插入排序\n");
        fflush(stdout);
        printf("8. 计数排序\n");
        fflush(stdout);
        printf("9. 基数排序\n");
        fflush(stdout);
        printf("请输入您的选择（1-9）：");
        fflush(stdout);
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: testSort(bubbleSort, data, length, "普通冒泡排序"); break;
            case 2: testSort(bubbleSortOptimized1, data, length, "优化冒泡排序1"); break;
            case 3: testSort(bubbleSortOptimized2, data, length, "优化冒泡排序2"); break;
            case 4: testSort(bubbleSortOptimized3, data, length, "优化冒泡排序3"); break;
            case 5: testSort(mergeSortAdapter, data, length, "归并排序"); break;
            case 6: testSort(quickSortAdapter, data, length, "快速排序"); break;
            case 7: testSort(insertSort, data, length, "插入排序"); break;
            case 8: testSort(countSort, data, length, "计数排序"); break;
            case 9: testSort(radixCountSort, data, length, "基数排序"); break;
            default: printf("请输入（1-9）!无效的选择!\n"); break;
        }
    }
    else {
            // 比较所有排序算法但不保存结果
            for (int i = 0; i < repeatCount; ++i) {
                // 每次重复测试时记得复制原始数据
                int *copy = (int*)malloc(sizeof(int) * length);
                memcpy(copy, data, sizeof(int) * length);

                // 执行所有测试并计算每种排序的总用时
                totalTimeBubble += testSort(bubbleSort, copy, length, "普通冒泡排序");
                totalTimeInsert += testSort(insertSort, copy, length, "插入排序");
                totalTimeMerge += testSort(mergeSortAdapter, copy, length, "归并排序");
                totalTimeQuick += testSort(quickSortAdapter, copy, length, "快速排序");
                totalTimeCount += testSort(countSort, copy, length, "计数排序");
                totalTimeRadix += testSort(radixCountSort, copy, length, "基数排序");

                printf("\n嘟嘟~~第%d次排序已完成~~\n\n", i+1);
                fflush(stdout);
                free(copy);
            }
            // 打印每种排序的总时间
            printf("普通冒泡排序总时间：%lf 秒\n", totalTimeBubble);
            printf("插入排序总时间：%lf 秒\n", totalTimeInsert);
            printf("归并排序总时间：%lf 秒\n", totalTimeMerge);
            printf("快速排序总时间：%lf 秒\n", totalTimeQuick);
            printf("计数排序总时间：%lf 秒\n", totalTimeCount);
            printf("基数排序总时间：%lf 秒\n", totalTimeRadix);
        }

    // 释放内存
    free(data);

    printf("--- 测试结束%s ---\n", testDescription);
}
