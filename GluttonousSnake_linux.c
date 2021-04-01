#include <stdlib.h>
#include "kbhit.h"

#define SNAKE_HAND *(map + (y * size + x)) 

int main(void)
{
    int len = 4, x = 1, y = 1, size, i;
    char c = 'S', cl = 'S', *map;

    printf("请输入地图大小:");
    scanf("%d", &size);
    size = size < 10 ? 10 : size;

    printf("\33[?25l");

    init_keyboard();

    map = calloc(size * size, sizeof(char));

    srand((unsigned)map);

    while(*(map + (i = rand() % (size * size))) != 0);
    *(map + i) = -1;

    for(; cl != 27; usleep(100000))
    {
        if(kbhit())
        {
            cl = readch();
            switch(cl)
            {
                case 'a':case 'A': if(c != 'D') c = 'A'; break;
                case 's':case 'S': if(c != 'W') c = 'S'; break;
                case 'd':case 'D': if(c != 'A') c = 'D'; break;
                case 'w':case 'W': if(c != 'S') c = 'W'; break;
            }
        }
        switch(c)
        {
            case 'A': x -= (x > 0        ? 1 : -(size - 1)); break;
            case 'D': x += (x < size - 1 ? 1 : -(size - 1)); break;
            case 'W': y -= (y > 0        ? 1 : -(size - 1)); break;
            case 'S': y += (y < size - 1 ? 1 : -(size - 1)); break;
        }

        if(SNAKE_HAND > 1 || SNAKE_HAND == -2)
            break;
        if(SNAKE_HAND == -1)
        {
            len += 1;
            while(*(map + (i = rand() % (size * size))) != 0);
            *(map + i) = -1;
        }
        else 
            for(i = 0; i < size * size; i++)
            {
                if(*(map + i) > 0)
                    *(map + i) -= 1;
            }
        SNAKE_HAND = len;

        for(i = 0; i < size * size; i++)
        {
            switch(*(map + i))
            {
                case  0: printf("\33[47m  \33[0m"); break;
                case -1: printf("\33[42m  \33[0m"); break;
                case -2: printf("\33[45m  \33[0m"); break;
                default: printf("\33[41m  \33[0m"); break;
            }
            if((i + 1) % size == 0)
                printf("\n");
        }
        printf("\33[0;0H");
    }
    printf("游戏结束\n得分:%d\n", len - 4);
    free(map);
    close_keyboard();
    return 0;
}