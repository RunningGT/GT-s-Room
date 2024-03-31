//main.c
#include "head.h"
#include "desk.c"
#include "function.c"

int main() {
    // 解决命令行显示中文乱码(GBK->UTF-8)
    system("chcp 65001");
    // 显示主菜单，让用户选择操作
    showDesk();

    return 0;
}