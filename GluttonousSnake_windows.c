#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

int main(void)
{
    int len = 4, x = 1, y = 1, size, i;
    //蛇长, x轴, y轴, 地图大小, 临时变量;
    char c = 'S', cl = 'S', * map, string[29];
    //移动方向, 输入缓冲, 地图指针, 控制台命令;
    HANDLE newHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //获取句柄
    COORD pos = { 0, 0 };
    //设置光标位置
    CONSOLE_CURSOR_INFO cur = { 1, 0 };
    SetConsoleCursorInfo(newHandle, &cur);
    //设置光标属性, 大小:1, 可见性:FALES

    //蛇身大于1 其数值为存活时间, 食物为-1, 墙为-2(未设置), 空地为0

    printf("请输入地图大小(10~255):");
    scanf_s("%d", &size);
    size = size < 10 ? 10 : size; //如果不足10就强制转化

    map = calloc(size * size, sizeof(char)); //设置地图

    srand((unsigned)map); //随机种

    sprintf_s(string, sizeof(string), "mode con: lines=%d cols=%d", size, size * 2); //命令设置

    system(string); //窗口设置

    while (*(map + (i = rand() % (size * size))) != 0); //在空地上放置食物
    *(map + i) = -1;

    for (; 1; Sleep(100))
    {
        if (_kbhit())
        {
            cl = _getch();
            switch (cl)
            {
            case 'a': case 'A': if (c != 'D') c = 'A'; break; //防止与原动作冲突
            case 's': case 'S': if (c != 'W') c = 'S'; break;
            case 'd': case 'D': if (c != 'A') c = 'D'; break;
            case 'w': case 'W': if (c != 'S') c = 'W'; break;
            }
        }
        switch (c)
        {
        case'A': x -= (x > 0 ? 1 : -(size - 1)); break; //移动
        case'D': x += (x < (size - 1) ? 1 : -(size - 1)); break;
        case'W': y -= (y > 0 ? 1 : -(size - 1)); break; //向下为正, 所以是减
        case'S': y += (y < (size - 1) ? 1 : -(size - 1)); break;
        }

        if (*(map + (y * size + x)) > 1 || *(map + (y * size + x)) == -2) //吃到自己或墙
            break;
        if (*(map + (y * size + x)) == -1) //吃到食物
        {
            len += 1;
            while (*(map + (i = (rand() % (size * size)))) != 0); //重设食物
            *(map + i) = -1;
        }
        else
            for (i = 0; i < size * size; i++) //空地
            {
                if (*(map + i) > 0) {
                    *(map + i) -= 1;
                }
            }
        *(map + (y * size + x)) = len; //更新头

        for (i = 0; i < size * size; i++)
        {
            switch (*(map + i)) //染色
            {
            case  0: SetConsoleTextAttribute(newHandle, 240); break; //240:白色, 160:绿色, 136:灰色, 192:红色
            case -1: SetConsoleTextAttribute(newHandle, 160); break;
            case -2: SetConsoleTextAttribute(newHandle, 136); break;
            default: SetConsoleTextAttribute(newHandle, 192); break;
            }
            printf("  ");
        }
        SetConsoleCursorPosition(newHandle, pos); //将光标归回(0,0), 防止刷新时闪烁
    }
    printf("Game Over\nPoints: %d\n", len - 4);
    system("pause");
    return 0;
}
/*
*贪吃蛇2.1
*在VC中可用
*给蛇. 食物. 墙与地图上色
*参考 https://github.com/RainbowRoad1/Cgame/tree/master/GluttonousSnake
*新手, 第一次写游戏, 还请多多指教
*calloc():申请一片内存, 并初始化, 返回指向这片内存的指针.                          在stdlib.h中
*sprintf():将字符串赋值给指针.                                                   在stdio.h中
*_kbhit():检测键盘输入, 若有输入, 返回1, 否则0. 为非阻塞型函数.                    在conio.h中
*GetStdHandle()获取句柄.                                                        在windows.h中
*SetConsoleTextAttributr()设置颜色                                              在windows.h中
*SetConsoleCurorPosition()设置光标位置                                          在windows.h中
*SerConsoleCursorInfo()设置光标属性                                              在windows.h
*/