#pragma once

#include "../headers/preset.h"

#include <fstream>

using std::ifstream;
using std::ios;
using std::ofstream;

class Settings
{
public:
    string FILENAME;

    string username;

    string lastOpen;
    bool autoOpen = true;
    bool autoAddSuffix = true;
    string filenameSuffix;
    int defaultPracticeTimes = 3;
    bool enableUsingDefaultPT = false;

    bool thisIsTheFirstTimeUsing = true;

private:
    string cleanUselessChar(string str)
    {
        string newStr = "";
        if (!str.empty())
        {
            char s;
            for (int i = 0; i < str.size(); i++)
            {
                s = str.at(i);
                if (s != ' ' && s != ';')
                {
                    newStr += s;
                }
            }
        }

        // cout << newStr << endl;
        return newStr;
    }

    bool isTrue(string str)
    {
        return (!str.compare("true")) || (!str.compare("True"));
    }

    int toInteger(string str)
    {
        int n = 0;
        for (unsigned short i = 0; i < str.size(); i++)
        {
            n = str.at(i) - '0' + 10 * n;
        }
        return n;
    }

public:
    Settings() {}
    Settings(string settingsFilename)
    {
        FILENAME = settingsFilename;
        ifstream fin;
        fin.open(settingsFilename, ios::in);
        string str;
        while (getline(fin, str))
        {
            if (str.find('[') != str.npos && str.at(0) != '#')
            {
                string subStr = cleanUselessChar(str.substr(str.find(':') + 1));
                switch (str.at(1) - '0')
                {
                case 1:
                    username = subStr;
                    break;
                case 2:
                    autoOpen = isTrue(subStr);
                    break;
                case 3:
                    autoAddSuffix = isTrue(subStr);
                    break;
                case 4:
                    filenameSuffix = subStr;
                    break;
                case 5:
                    defaultPracticeTimes = toInteger(subStr);
                    break;
                case 6:
                    enableUsingDefaultPT = isTrue(subStr);
                    break;
                case 7:
                    thisIsTheFirstTimeUsing = isTrue(subStr);
                    break;
                case 8:
                    lastOpen = subStr;
                    break;

                default:
                    break;
                }
            }
        }
    }
    void updateSettings()
    {
        string setStr = "";
        cout << setStr << endl;
    }

    ~Settings() {}
};
