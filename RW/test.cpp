#include "headers/preset.h"
#include "headers/menu.h"
#include <algorithm>

#include "Class/Settings.cpp"
#include "Class/File.cpp"
#include "Class/WordClass.cpp"
#include "headers/function.cpp"

void charger(vector<WordClass> &v1, vector<WordClass> &v2, int v2_Type)
{
    // charger!
    // 别问我为什么起这个名字，问就是 求生之路2 玩多了
    for (auto &i : v1)
    {
        for (auto &j : v2)
        {
            if (!(i.word_lower.compare(j.word_lower)))
            {
                cout << i.word_lower << _ << j.word_lower << _;
                cout << "匹配成功！" << endl;

                if (v2_Type == FAMILIAR)
                {
                    i.practiceTimes = 0;
                }
                if (v2_Type == UNFAMILIAR)
                {
                    i.practiceTimes += 2;
                }
            }
        }
    }
}

string input(){
    cout << GREEN("       [输入] ");
    string str;
    getline(cin, str);
    cout << str << endl;
    return str;
}

bool isCommand(string str)
{
    return str[0] == 47;
}

int main()
{
    Settings setting("Data/settings.txt");
    // cout << setting.FILENAME << endl;
    // cout << setting.autoOpen << endl;
    // cout << setting.filenameSuffix << endl;
    // cout << setting.lastOpen << endl;
    //
    // if (setting.thisIsTheFirstTimeUsing)
    // {
    //     v_firstMeet();
    //     cout << setting.username << endl;
    //     string username;
    //     cin >> username;
    //     setting.username = username;
    //     cleanUp();
    //
    //     // note 第一次让用户自己配置文件
    //     setting.updateSettings();
    // }
    // v_welcome(setting.username);
    //
    // string filename;
    // int practiceTime;
    // if (setting.autoOpen)
    //     filename = setting.lastOpen;
    // else
    // {
    //     v_askForFilename();
    //     cin >> filename;
    // }
    // if (setting.autoAddSuffix)
    //     filename += setting.filenameSuffix;
    // if (setting.enableUsingDefaultPT)
    //     practiceTime = setting.defaultPracticeTimes;
    // else
    // {
    //     v_askForPracticeTime();
    //     cin >> practiceTime;
    // }

    string fn = setting.lastOpen + ".csv";

    vector<WordClass> wc_vec;
    WordBook wd(fn, WORDBOOK, wc_vec, setting.defaultPracticeTimes);

    vector<WordClass> fa_vec;
    WordBook wf("Data/familiar.csv", FAMILIAR, fa_vec);

    vector<WordClass> uf_vec;
    WordBook wuf("Data/unfamiliar.csv", UNFAMILIAR, uf_vec);
    cout << "------------------------------------------------------" << endl;

    charger(wc_vec, uf_vec, UNFAMILIAR);
    charger(wc_vec, fa_vec, FAMILIAR);
    for (auto i : wc_vec)
    {
        i.coutString();
    }
    cout << "hhhhhhhhhhhhhhhh" << endl;

    srand(time(NULL));
    bool practicing = true;
    int randIndex, twice;

    for (int i = 0; i < wc_vec.size(); i++)
    {
        wc_vec.at(i).coutString();
    }
    
    while (practicing)
    {
        while (true)
        {
            randIndex = rand() % wc_vec.size();
            if (wc_vec.at(randIndex).practiceTimes != 0)
            {
                wc_vec.at(randIndex).practiceTimes--;
                break;
            }
            // note 单词没有了怎么办？用什么
        }

        cout << BLUE("\n\n       [释义] ") << wc_vec.at(randIndex).meaning << endl;
        string input_text = input();
        cleanUp();

        if (isCommand(input_text))
        {
            // switch ()
            // {   
            // case :
            //     break;
            
            // default:
            //     break;
            // }
        }
        
        
        
    }
    
    

    pause();
}