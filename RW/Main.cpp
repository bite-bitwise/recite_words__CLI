/*
#include "headers/preset.h"
#include "headers/menu.h"
#include <algorithm>

#include "Class/Settings.cpp"
#include "Class/File.cpp"
#include "Class/WordClass.cpp"

using std::any_of;
bool operator==(WordClass &w1, WordClass &w2)
{
    return !w1.word_lower.compare(w2.word_lower);
}

int main()
{
    Settings setting("Data/settings.txt");
    if (setting.thisIsTheFirstTimeUsing)
    {
        v_firstMeet();
        string username;
        cin >> username;
        setting.username = username;
        cleanUp();

        // note 第一次让用户自己配置文件
        setting.updateSettings();
    }
    v_welcome(setting.username);

    string filename;
    int practiceTime;
    if (setting.autoOpen)
        filename = setting.lastOpen;
    else
    {
        v_askForFilename();
        cin >> filename;
    }
    if (setting.autoAddSuffix)
        filename += setting.filenameSuffix;
    if (setting.enableUsingDefaultPT)
        practiceTime = setting.defaultPracticeTimes;
    else
    {
        v_askForPracticeTime();
        cin >> practiceTime;
    }

    vector<WordClass> wc_vec;
    filename = "rw.csv";
    cout << filename << endl;
    WordBook wd(filename, WORDBOOK, wc_vec, practiceTime);

    vector<WordClass> fa_vec;
    WordBook wf("Data/familiar.csv", FAMILIAR, fa_vec);

    vector<WordClass> uf_vec;
    WordBook wuf("Data/unfamiliar.csv", UNFAMILIAR, uf_vec);

    // for (us i = 0; i < wc_vec.size(); i++)
    // {
    //     uf_vec.at(i).coutString();
    // }
    cout << "___________________________________" << endl;
    // for (us i = 0; i < uf_vec.size(); i++)
    // {
    //     uf_vec.at(i).coutString();
    // }
    cout << "___________________________________" << endl;
    // for (us i = 0; i < fa_vec.size(); i++)
    // {
    //     uf_vec.at(i).coutString();
    // }
    cout << "___________________________________" << endl;

    // for (int i = 0; i < wc_vec.size(); i++)
    // {
    //     for (int j = 0; j < uf_vec.size(); j++)
    //     {
    //         if (!wc_vec.at(j).word_lower.compare(uf_vec.at(j).word_lower))
    //         {
    //             wc_vec.at(j).practiceTimes += 2;
    //         }
    //     }

    //     for (int j = 0; j < fa_vec.size(); j++)
    //     {
    //         if (!wc_vec.at(j).word_lower.compare(uf_vec.at(j).word_lower))
    //         {
    //             wc_vec.at(j).practiceTimes = 0;
    //         }
    //     }
    // }

    // for (us i = 0; i < wc_vec.size(); i++)
    // {
    //     uf_vec.at(i).coutString();
    // }

    pause();
}

*/