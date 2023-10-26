#pragma once

#include "..\headers\function.cpp"

class WordClass
{
public:
    string word, meaning, word_lower;
    int practiceTimes = 0;
    us wordLength = 0;

public:
    WordClass() {}
    WordClass(string word, string meaning, int practiceTimes)
    {
        this->word = word;
        this->meaning = meaning;
        this->word_lower = lettersLower(word);
        this->wordLength = word.size();
        this->practiceTimes = practiceTimes;
    }

    // 检查拼写是否正确，spelled 将会被转换为小写。
    bool checkSpelled(string &spelled)
    {
        spelled = lettersLower(spelled);
        if (wordLength != spelled.size())
            return false;
        return !word_lower.compare(spelled);
    }

    // 默认单词已经写错，返回值出错位置是第几个字符（从1开始），而非下标
    us breakIn(string spelled)
    {
        for (us i = 0; i < wordLength; i++)
        {
            if (word_lower.at(i) != spelled.at(i))
            {
                return i + 1;
            }
        }
        return 0;
    }

    void coutString()
    {
        cout << word << _ << word_lower << _ << meaning << _ << practiceTimes << endl;
    }
};