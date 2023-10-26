#pragma once

#include "..\headers\preset.h"
#include "WordClass.cpp"
#include "Settings.cpp"
#include <fstream>

#define WORDBOOK 1
#define FAMILIAR 2
#define UNFAMILIAR 3

using std::ifstream;
using std::ios;

class File
{
protected:
    string filename;
    bool isExisted;
    Settings setting;
    ifstream fin;

public:
    File(string filename)
    {
        // 需要自己带后缀
        fin.open(filename, ios::in);
        isExisted = fin.is_open();
    }
};

class WordBook : public File
{
private:
    int fileType;

private:
    WordClass strToWordClass(string str, int practiceTimes)
    {
        string word = "", meaning;
        for (us i = 0; i < str.size(); i++)
        {
            if (str[i] == ',')
                break;
            word += str[i];
        }
        meaning = str.substr(str.find(',') + 1);
        WordClass wd(word, meaning, practiceTimes);
        wd.coutString();
        return wd;
    }

public:
    WordBook(string filename, int type, vector<WordClass> &vec, int practiceTimes = 3) : File(filename)
    {
        fileType = type;
        if (isExisted)
        {
            cout << filename << _ << "文件存在" << endl;
            string str;
            while (getline(fin, str))
            {
                vec.push_back(strToWordClass(str, practiceTimes));
            }
            fin.close();
            cout << "-------------------" << endl;
        }
    }
};