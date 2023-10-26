#include "./headers/preset.h"
#include "./headers/menu.h"
#include <algorithm>

#include "Class/Settings.cpp"
#include "Class/File.cpp"
#include "Class/WordClass.cpp"

int main()
{
   Settings setting("Data/settings.txt");
   // if (setting.thisIsTheFirstTimeUsing)
   // {
   //     v_firstMeet();
   //     string username;
   //     cin >> username;
   //     setting.username = username;
   //     cleanUp();

   //     // note 第一次让用户自己配置文件
   //     setting.updateSettings();
   // }
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
   WordBook wd(filename, WORDBOOK, wc_vec, practiceTime);

   vector<WordClass> fa_vec;
   WordBook wf("Data/familiar.csv", FAMILIAR, fa_vec);

   vector<WordClass> uf_vec;
   WordBook wuf("Data/familiar.csv", UNFAMILIAR, uf_vec);

   for (us i = 0; i < uf_vec.size(); i++)
   {
       uf_vec.at(i).coutString();
   }
   

   for (auto i : uf_vec)
   {

       auto it = std::find(wc_vec.begin(), wc_vec.end(), i);
       if (it != wc_vec.end())
       {
           i.coutString();
       }
   }

   pause();
}