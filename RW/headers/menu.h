#pragma once

/*
    本文件中所有的函数都是以 v_ 开头，切均为打印的一些内容
    以 v_ 开头，方便在其他文件中与其他函数区分
*/
#include "preset.h"
#define _space "        "

void v_firstMeet()
{
    cout << "\n\n"
         << _space << "这是你第一次使用本程序\n"
         << _space << "请输入你的用户名，方便以后我们称呼您：";
}

void v_welcome(string name)
{
    cout << "\n\n";
    cout << _space << "欢迎你！" << name << endl;
}

void v_askForFilename(){
    cout << "\n\n"
         << _space << "请输入单词本的文件名：";
}

void v_askForPracticeTime(){
    cout << "\n\n"
         << _space << "请输入单词的默认练习次数：";
}