//部分特殊值的出错处理还没搞完，不信现在输入小数只能读取整数部分，略略略
// main.c
#include "Queue.h"
#include "Queue_.c"
#include "desk.c"

int main() {
    // 解决命令行显示中文乱码(GBK->UTF-8)
    system("chcp 65001");
    LQueue queue;
    InitLQueue(&queue);
    mainMenu(&queue);
    return 0;
}
