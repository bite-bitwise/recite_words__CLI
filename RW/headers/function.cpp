#pragma once

#include <conio.h>
#include "preset.h"

bool equals(string str1, string str2)
{
    return !str1.compare(str2);
}

// 字符串中字母大写转小写
string lettersLower(string str)
{
    for (us i = 0; i < str.size(); i++)
    {
        if (str.at(i) >= 'A' && str.at(i) <= 'Z')
        {
            str.at(i) += 32;
        }
    }
    return str;
}

// 字符串中字母小写转大写
string lettersUpper(string str)
{
    for (us i = 0; i < str.size(); i++)
    {
        if (str.at(i) >= 'a' && str.at(i) <= 'z')
        {
            str.at(i) -= 32;
        }
    }
    return str;
}

// 输出炫彩：红
string RED(string s)
{
    return "\033[0m\033[1;31m" + s + "\033[0m";
}

string GREEN(string s)
{
    return "\033[0m\033[1;32m" + s + "\033[0m";
}

string YELLOW(string s)
{
    return "\033[0m\033[1;33m" + s + "\033[0m";
}

string BLUE(string s)
{
    return "\033[0m\033[1;34m" + s + "\033[0m";
}


// 一个只能输入整数的函数
int integerOnly(void)
{
    int bit;
    char integer[20]; // 防止某些人玩坏了，所以数组长度搞大点
    us index = 0;

    while (true)
    {
        bit = _getch();
        if (bit == 8)
        {
            if (index > 0)
            {
                index--;
                integer[index] = 0;
                cout << "\b \b";
            }
            else
                continue;
        }
        else if (bit == 13)
        {
            warp();
            break;
        }
        else
        {
            if (bit >= '0' && bit <= '9')
            {
                integer[index++] = bit;
                cout << bit;
            }
        }
    }

    sscanf_s(integer, "%d", &bit);
    return bit;
}