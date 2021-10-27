#include "systemTimer.h"

// PUBLIC_TIMER8 PublicTimer8;
PUBLIC_TIMER16 PublicTimer16;

/***********************************************************************
* systemTimer(void)
*
* 这是一个以10ms为单位的滴答系统时钟
*
* 作者：
************************************************************************/
void systemTimer(void)
{
    //add your code please.

    if(PublicTimer16.MenuDly16.Timer16Count)    //菜单定时器
    {
        PublicTimer16.MenuDly16.Timer16Count--;

        if(!PublicTimer16.MenuDly16.Timer16Count)
        {
            PublicTimer16.MenuDly16.Timer16Flag = true;
        }
    }
}

void Delay_ms(unsigned short time)
{
    unsigned short temp;

    temp = time;

    while(temp --)
    {
        Delay1ms();
    }
}

/*禁止编译器优化该模块*/
// #pragma OPTIMIZE(0)

void Delay1ms()		//@11.0592.000MHz
{
    unsigned char i, j;

    i = 11;
    j = 190;

    do
    {
        while (--j);
    }
    while (--i);
}

