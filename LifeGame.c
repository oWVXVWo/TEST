#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "kbhit.h"

#define ADD1 *(str + (y - 1) * length + (x - 1))
#define ADD2 *(str + (y - 1) * length + (x    ))
#define ADD3 *(str + (y - 1) * length + (x + 1))
#define ADD4 *(str + (y    ) * length + (x + 1))
#define ADD5 *(str + (y + 1) * length + (x + 1))
#define ADD6 *(str + (y + 1) * length + (x    ))
#define ADD7 *(str + (y + 1) * length + (x - 1))
#define ADD8 *(str + (y    ) * length + (x - 1))

#define BLACK_BG "\33[40m" 
#define WHITE_BG "\33[47m"
#define NONE "\33[0m"

/*
*	ADD1	ADD2	ADD3
*	ADD8	cell	ADD4
*	ADD7	ADD6	ADD5
*/

int length, width;
//地图长， 地图宽

int CountCell(char *str, int x, int y) //计数
{
	int sum = 0;
	int xMax = length - 1;
	int yMax = width - 1;

	if (x == 0 && y == 0) //第一行第一列
		sum += ADD4 + ADD5 + ADD6;
	else if (x == xMax && y == 0) //第一行最后一列
		sum += ADD8 + ADD7 + ADD6;
	else if (x == 0 && y == yMax) //最后一行第一列
		sum += ADD2 + ADD3 + ADD4;
	else if (x == xMax && y == yMax) //最后一行最后一列
		sum += ADD1 + ADD2 + ADD8;
	else if (x == 0) //第一列
		sum += ADD2 + ADD3 + ADD4 + ADD5 + ADD6;
	else if (x == xMax) //最后一列
		sum += ADD1 + ADD2 + ADD6 + ADD7 + ADD8;
	else if (y == 0) //第一行
		sum += ADD4 + ADD5 + ADD6 + ADD7 + ADD8;
	else if (y == yMax) //最后一行
		sum += ADD1 + ADD2 + ADD3 + ADD4 + ADD8;
	else //中部
		sum += ADD1 + ADD2 + ADD3 + ADD4 + ADD5 + ADD6 + ADD7 + ADD8;

	return sum;
}

void DrawMap(char *str, int size) //绘制
{
	int i;
	for (i = 1; i <= size; i++)
	{
		printf("%s  "NONE, *(str + i) ? WHITE_BG : BLACK_BG);

		if (i % length == 0)
		{
			printf("\n");
		}
	}

	return;
}

int main(void)
{
	int i, cell, x, y;
	//循环变量， 细胞数， x， y
	char *map, *mapcp, ch;
	//指向地图， 指向地图缓冲, 临时变量

	printf("游戏中按ESC退出");
	printf("输入地图长:");
	scanf("%d", &length);
	printf("输入地图宽:");
	scanf("%d", &width);

	map = calloc(sizeof(char), length * width);
	mapcp = calloc(sizeof(char), length * width);

	srand((unsigned)map);

	init_keyboard(); //初始化函数kbhit()

	for (i = 0; i < length * width; i++) //随机为地图赋值
	{
		*(map + i) = rand() % 2;
	}

	printf("\33[?25l"); //隐藏光标

	while (ch != 27)
	{
		printf("\33[0;0H"); //光标跳转
		printf("\33[2J"); //清屏
		for (y = 0; y < width; y++) //双循环遍历&赋值
		{
			for (x = 0; x < length; x++)
			{
				cell = CountCell(map, x, y);

				*(mapcp + y * length + x) =
					(cell == 3) || ((cell == 2) && *(map + y * length + x));
			}
		}

		for (i = 0; i < length * width; i++) //拷贝临时地图
		{
			*(map + i) = *(mapcp + i);
		}

		DrawMap(map, length * width);

		if(kbhit())
		{
			ch = readch();
		}

		usleep(100000);
	}

	close_keyboard(); //关闭函数kbhit()
	free(map);
	free(mapcp);
	return 0;
}
