// 背单词小程序 v2023.2

//* 增加一个功能
//* 用户可以输入指令
//* /familiar 加入熟单词本 done
//* /unfamiliar 加入生词本 done
//* /help 获取帮助，使用system()指令打开预先准备好的图片 done
//* /remove 对于单词使用这个指令，本次练习移除此单词 done
//* /settings 设置功能，帮助用户设置，例如，单词最少练习次数
//*
//*
//*

// note UI需要改进，以及指令代码部分，/show之后干什么呢？ done
// note 熟词本等 需要测试 done
// note 控制台彩色显示？ done

#include <Windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORD_LEN 40
#define MEANING_LEN 80
#define FILE_NAME_LEN 40
#define WordListMaxLength 4000  // 单词本最多容纳4000个单词

char input[WORD_LEN];

typedef struct WORD_ {
    char word[WORD_LEN];
    char meaning[MEANING_LEN];
    int display_times;
} WORD_;

typedef struct List {
    WORD_ WordList[WordListMaxLength];
    int length;
} List;

struct User {
    double all_words;
    double correct_number;
} info;

/* 函数声明 */
void initList(List* L);
void insertList(List* L, WORD_ value);
_Bool isFileEmpty(FILE* file_pointer);
int getLines(FILE* file_pointer);
void WordBook_getInFile(List* L, FILE* file_pointer, int file_lines);
void setDisplayTimes(List* L, int display_times, int WordsNumber);
void checkFilename(char filename[]);
// void cleanFile(char filename[]);
//_Bool checkDiff(List* familiar, List* unfamiliar);
void FamiliarWordsChecker(List* L, List* familiar_list);
void UnfamiliarWordsChecker(List* L, List* unfamiliar_list);
void BubbleSort(List* L);
int BinarySearch(List* L, char value[]);
int integer_input(void);
void writeInWrongWords(List* L, List* W, int word_i);
_Bool isThatAll(List* L);
void getInput();
_Bool isCommand(char input[]);
int runCommand(List* L, List* UNFAMILIAR, int word_i);
void resetInput();

/* 彩色打印函数 */
void printf_red(const char* s) {
    printf("\033[0m\033[1;31m%s\033[0m", s);
}

void printf_green(const char* s) {
    printf("\033[0m\033[1;32m%s\033[0m", s);
}

void printf_yellow(const char* s) {
    printf("\033[0m\033[1;33m%s\033[0m", s);
}

void printf_blue(const char* s) {
    printf("\033[0m\033[1;34m%s\033[0m", s);
}

void printf_pink(const char* s) {
    printf("\033[0m\033[1;35m%s\033[0m", s);
}

void printf_cyan(const char* s) {
    printf("\033[0m\033[1;36m%s\033[0m", s);
}

/* 主函数从这里开始 */
int main(void) {
    _Bool RUN = TRUE;
    char filename[FILE_NAME_LEN];
    printf_yellow("\n\n       请输入你想要练习的单词本的文件名 ");
    gets(filename);

    // char filename[FILE_NAME_LEN] = "words.csv";
    checkFilename(filename);
    printf_yellow("\n\n\n       正在读取文件...");
    Sleep(500);

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf_red("\b\b\b   失败！\n\n");
        printf_red(
            "       错误信息：\n   "
            "       请将配置好的.csv文件放置于该程序的同一目录下，\n"
            "          重新运行此程序！\n\n\n");
        printf_yellow("       程序将在10秒后自动退出......");
        Sleep(10000);

        exit(0);
    } else {
        if (isFileEmpty(fp)) {
            printf_red("\b\b\b   失败！\n\n");
            printf_red(
                "       错误信息：\n   "
                "       检测到目标文件为空，请配置目标的.csv文件，\n"
                "          重新运行此程序！\n\n\n");

            printf_yellow("       程序将在10秒后自动退出......");
            Sleep(10000);

            exit(0);
        }
        printf_green("\b\b\b   成功！");
        Sleep(1000);
        system("cls");
    }

    FILE* familiar = fopen("userdata\\familiar.txt", "a+");
    FILE* unfamiliar = fopen("userdata\\unfamiliar.txt", "a+");

    List L;
    List W;
    List FAMILIAR;
    List UNFAMILIAR;

    initList(&L);
    initList(&W);
    initList(&FAMILIAR);
    initList(&UNFAMILIAR);

    L.length = getLines(fp);
    FAMILIAR.length = getLines(familiar);
    UNFAMILIAR.length = getLines(unfamiliar);

    WordBook_getInFile(&L, fp, L.length);
    printf_yellow("\n\n       请输入每个单词练习的最少次数 ");

    int times = integer_input();
    system("cls");

    setDisplayTimes(&L, times, L.length);

    if (!isFileEmpty(familiar)) {
        WordBook_getInFile(&FAMILIAR, familiar, FAMILIAR.length);
    }
    if (!isFileEmpty(unfamiliar)) {
        WordBook_getInFile(&UNFAMILIAR, unfamiliar, UNFAMILIAR.length);
    }

    fclose(fp);
    fclose(familiar);
    fclose(unfamiliar);

    UnfamiliarWordsChecker(&L, &UNFAMILIAR);
    FamiliarWordsChecker(&L, &FAMILIAR);
    srand((unsigned)time(NULL));

    char input_word[WORD_LEN], ch;
    _Bool flag = TRUE, init_wrong = TRUE, skip = FALSE, end = FALSE;
    int input_word_len, word_i, count = 1, twice, command = 0;

    info.all_words = info.correct_number = 0;

    while (RUN) {
        while (flag) {
            word_i = rand() % L.length;
            if (L.WordList[word_i].display_times != 0) {
                flag = FALSE;
                L.WordList[word_i].display_times--;
                info.all_words++;
            }
        }

        flag = TRUE;
        twice = 0;
        skip = FALSE;

        printf_blue("\n\n       [释义] ");
        printf("%s", L.WordList[word_i].meaning);
        printf("\n");

        while (TRUE) {
            getInput();
            if (isCommand(input)) {
                command = runCommand(&L, &UNFAMILIAR, word_i);
                if (command == 1 || command == 7) {
                    system("cls");
                    skip = TRUE;
                    break;
                }
                if (command == 4) {
                    end = TRUE;
                    break;
                }
                if (command == 5) {
                    system("cls");
                    skip = TRUE;
                    L.WordList[word_i].display_times++;
                    break;
                }

            } else {
                if (strcmp(input, L.WordList[word_i].word) == 0) {
                    printf("\n\n");
                    printf_yellow("       [系统] 输入正确！\n");
                    info.correct_number++;
                    resetInput();
                    break;
                } else {
                    twice++;
                    if (twice == 2) {
                        L.WordList[word_i].display_times++;
                        if (init_wrong) {
                            FILE* ww = fopen("WrongWordList.csv", "w");
                            fclose(ww);
                        }
                        writeInWrongWords(&L, &W, word_i);
                        resetInput();
                        break;
                    }
                }
            }
            resetInput();
        }

        if (skip) {
            continue;
        }

        if (end) {
            break;
        }

        printf_yellow("\n\n       [系统] 当前正确率为 ");
        printf(" %.0lf/%.0lf", info.correct_number, info.all_words);
        printf_yellow("\n       [系统] 按下Enter键以继续...");

        getchar();
        system("cls");

        if (isThatAll(&L)) {
            break;
        }
    }

    if (end) {
        system("cls");
        printf("\n\n      你已完成本次练习。");
        printf("\n      你联系了 %.0lf 个单词，其中答对 %.0lf 个",
               info.correct_number, info.all_words);
        printf("\n      正确率为 %.2lf", info.correct_number / info.all_words);
    } else {
        printf("\n\n      你已完成全部单词的练习！");
        printf("\n      正确率为 %.2lf", info.correct_number / info.all_words);
    }

    printf("\n      按下Enter键以退出...");
    getchar();

    return 0;
}

void initList(List* L) {
    for (int i = 0; i < WordListMaxLength; i++) {
        L->WordList[i].display_times = 0;
    }
    L->length = 0;
}

void insertList(List* L, WORD_ value) {
    L->WordList[L->length] = value;
    L->length++;
}

_Bool isThatHave(List* L, char value[]) {
    _Bool flag = FALSE;
    for (int i = 0; i < L->length; i++) {
        if (strcmp(L->WordList[i].word, value) == 0) {
            flag = TRUE;
        }
    }
    return flag;
}

int whereIsThat(List* L, char value[]) {
    for (int i = 0; i < L->length; i++) {
        if (strcmp(L->WordList[i].word, value) == 0) {
            return i;
        }
    }
    return -1;
}

_Bool isFileEmpty(FILE* file_pointer) {
    if (fgetc(file_pointer) == EOF) {
        return TRUE;
    }
    return FALSE;
}

int getLines(FILE* file_pointer) {
    // 默认文件不为空
    int line = 0;
    char t;
    while ((t = fgetc(file_pointer)) != EOF) {
        if (t == '\n') {
            line++;
        }
    }
    rewind(file_pointer);
    return line;
}

void WordBook_getInFile(List* L, FILE* file_pointer, int file_lines) {
    rewind(file_pointer);
    for (int i = 0; i < file_lines; i++) {
        fscanf(file_pointer, "%[^,]", L->WordList[i].word);
        fgetc(file_pointer);
        fscanf(file_pointer, "%[^\n]", L->WordList[i].meaning);
        fgetc(file_pointer);
    }
}

void setDisplayTimes(List* L, int display_times, int WordsNumber) {
    for (int i = 0; i < WordsNumber; i++) {
        L->WordList[i].display_times = display_times;
    }
}

void checkFilename(char filename[]) {
    // 判断用户输入的文件名带不带.csv，不带就补上
    _Bool flag_csv = TRUE;
    char _csv[5] = ".csv";
    for (int i = 0; i < (FILE_NAME_LEN - 5); i++) {
        if (filename[i] == '.' && filename[i + 1] == 'c' &&
            filename[i + 2] == 's' && filename[i + 3] == 'v' &&
            filename[i + 4] == '\0') {
            flag_csv = FALSE;
            break;
        }
    }
    if (flag_csv == TRUE) {
        strcat(filename, _csv);
    }
}

/*
    以w方式打开会清除上次所写的内容，再次关闭，
    来达到清除源文件内容的目的。

void cleanFile(char filename[]) {
    FILE* ww = fopen(filename, "w");
    fclose(ww);
}
*/

/*
    这个函数是用来检测是否存在相同的单词既在生词本又在熟词本的情况，
    但是，如果正常使用是不会出现这种情况，函数已注释

_Bool checkDiff(List* familiar, List* unfamiliar) {
    int t = -1;
    _Bool flag = TRUE;
    if (familiar->length >= unfamiliar->length) {
        BubbleSort(familiar);
        for (int i = 0; i < unfamiliar->length; i++) {
            t = BinarySearch(familiar, unfamiliar->WordList[i].word);
            if (t != -1) {
                flag = FALSE;
            }
        }
    } else {
        BubbleSort(unfamiliar);
        for (int i = 0; i < familiar->length; i++) {
            t = BinarySearch(unfamiliar, familiar->WordList[i].word);
            if (t != -1) {
                flag = FALSE;
            }
        }
    }
    return flag;
}

*/
void FamiliarWordsChecker(List* L, List* familiar_list) {
    int t = -1;
    if (L->length >= familiar_list->length) {
        BubbleSort(L);
        for (int i = 0; i < familiar_list->length; i++) {
            t = BinarySearch(L, familiar_list->WordList[i].word);
            if (t != -1) {
                L->WordList[t].display_times = 0;
            }
        }
    } else {
        BubbleSort(familiar_list);
        for (int i = 0; i < L->length; i++) {
            t = BinarySearch(familiar_list, L->WordList[i].word);
            if (t != -1) {
                L->WordList[t].display_times = 0;
            }
        }
    }
}

void UnfamiliarWordsChecker(List* L, List* unfamiliar_list) {
    int t = -1;
    if (L->length >= unfamiliar_list->length) {
        BubbleSort(L);
        for (int i = 0; i < unfamiliar_list->length; i++) {
            t = BinarySearch(L, unfamiliar_list->WordList[i].word);
            if (t != -1) {
                L->WordList[t].display_times += 2;
            }
        }
    } else {
        BubbleSort(unfamiliar_list);
        for (int i = 0; i < L->length; i++) {
            t = BinarySearch(unfamiliar_list, L->WordList[i].word);
            if (t != -1) {
                L->WordList[t].display_times += 2;
            }
        }
    }
}

void BubbleSort(List* L) {
    // 哦，这稳定的冒泡排序
    int i, j;
    WORD_ temp;
    for (i = 0; i < L->length - 1; i++) {
        for (j = i + 1; j < L->length - 1 - i; j++) {
            if (strcmp(L->WordList[j].word, L->WordList[j + 1].word) > 0) {
                temp = L->WordList[j];
                L->WordList[j] = L->WordList[j + 1];
                L->WordList[j + 1] = temp;
            }
        }
    }
}

int BinarySearch(List* L, char value[]) {
    int mid, low = 0, high = L->length;  // 二分查找
    while (low <= high) {
        mid = (low + high) / 2;
        if (strcmp(L->WordList[mid].word, value) > 0) {
            high = mid - 1;
        } else if (strcmp(L->WordList[mid].word, value) < 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int integer_input(void) {
    // 一个只能输入整数的函数
    int n, judge;
    scanf("%d", &n);
    judge = getchar();
    while (judge != '\n') {
        fflush(stdin);
        printf("你的输入不规范，请重新输入!  ");
        scanf("%d", &n);
        judge = getchar();
    }
    return n;
}

void writeInWrongWords(List* L, List* W, int word_i) {
    _Bool a = TRUE;
    for (int i = 0; i < L->length; i++) {
        if (strcmp(W->WordList[i].word, L->WordList[word_i].word) == 0) {
            a = FALSE;
        }
    }
    if (a) {
        insertList(W, L->WordList[word_i]);

        FILE* ww = fopen("WrongWordList.csv", "a+");
        fprintf(ww, "%s", L->WordList[word_i].word);
        fprintf(ww, ",");
        fprintf(ww, "%s", L->WordList[word_i].meaning);
        fprintf(ww, "\n");
        fclose(ww);
    }
}
_Bool isThatAll(List* L) {
    for (int j = 0; j < L->length; j++) {
        if (L->WordList[j].display_times != 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void getInput() {
    printf_green("       [输入] ");

    char ch;
    ch = getchar();
    int input_len = 0;
    while (ch != '\n') {
        input[input_len++] = ch;
        ch = getchar();
    }
    input[input_len] = '\0';
}

_Bool isCommand(char input[]) {
    if (input[0] == 47) {
        // note '/' 的ASCII码为47
        return TRUE;
    } else {
        return FALSE;
    }
}

int runCommand(List* L, List* UNFAMILIAR, int word_i) {
    char _show_[WORD_LEN + 20] = "       [系统] [ ";
    strcat(_show_, L->WordList[word_i].word);
    strcat(_show_, " ]");

    if (!strcmp(input, "/familiar")) {
        // 单词加入熟词本
        // note 好像没有必要，因为如果存在，DisplayTimes == 0;
        FILE* familiar = fopen("userdata\\familiar.txt", "a+");
        fprintf(familiar, "%s", L->WordList[word_i].word);
        fprintf(familiar, ",");
        fprintf(familiar, "%s", L->WordList[word_i].meaning);
        fprintf(familiar, "\n");
        fclose(familiar);
        L->WordList[word_i].display_times = 0;
        resetInput();

        return 1;
    } else if (!strcmp(input, "/unfamiliar")) {
        // 加入生词本
        if (!isThatHave(UNFAMILIAR, L->WordList[word_i].word)) {
            FILE* unfamiliar = fopen("userdata\\unfamiliar.txt", "a+");
            fprintf(unfamiliar, "%s", L->WordList[word_i].word);
            fprintf(unfamiliar, ",");
            fprintf(unfamiliar, "%s", L->WordList[word_i].meaning);
            fprintf(unfamiliar, "\n");
            fclose(unfamiliar);
        }
        L->WordList[word_i].display_times += 2;
        printf_yellow("       [系统] 该单词已被加入生词本中！练习次数 +2\n");
        resetInput();

        return 2;
    } else if (!strcmp(input, "/help")) {
        // system指令，打开help.文件
        system("start https://www.yuque.com/muqian_blog/xi8izm/ggnsvi");
        system("userdata\\help.png");
        // 改成图片会比较好

        resetInput();

        return 3;
    } else if (!strcmp(input, "/end")) {
        // 结束练习
        resetInput();

        return 4;
    } else if (!strcmp(input, "/skip")) {
        // 跳过这个单词
        info.all_words--;
        resetInput();

        return 5;
    } else if (!strcmp(input, "/show")) {
        // 展示这个单词
        printf_yellow(_show_);
        printf("\n");
        resetInput();

        return 6;
    } else if (!strcmp(input, "/remove")) {
        // 移除当前这个单词
        L->WordList[word_i].display_times = 0;
        resetInput();

        return 7;
    } else {
        printf_yellow("       [系统] 未知指令，请重新输入！\n");
        resetInput();

        return 0;
    }
}

void resetInput() {
    strcpy(input, "");
}