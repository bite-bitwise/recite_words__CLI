//背单词小程序 v9.20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define WORD_LEN 20
#define MEANING_LEN 80
#define FILE_NAME_LEN 40

#define Boolean int
#define True 1
#define False 0

typedef struct WORD_
{
	char word[WORD_LEN];
	char meaning[MEANING_LEN];
	int display_times;
} WORD_;

typedef struct WORDS
{
	char word[WORD_LEN];
	char meaning[MEANING_LEN];
} WORDS;

typedef struct User
{
	double all_words;
	double correct_number;
} User;

int integer_input(void);

int main(void)
{

	char filename[FILE_NAME_LEN], _csv[5] = ".csv";
	puts("请输入你想要练习单词的文本文件名");
	gets(filename);

	Boolean flag_csv = True; // 判断用户输入的文件名带不带.csv，不带就补上
	for (int i = 0; i < (FILE_NAME_LEN - 4); i++)
	{
		if (filename[i] == '.' && filename[i + 1] == 'c' && filename[i + 2] == 's' && filename[i + 3] == 'v' &&
			filename[i + 4] == '\0')
		{
			flag_csv = False;
			break;
		}
	}
	if (flag_csv == True)
	{
		strcat(filename, _csv);
	}

	FILE *fp = fopen(filename, "r");

	printf("正在读取文件...");
	Sleep(300);
	if (fp == NULL)
	{
		printf("\b\b\b   失败！\n");
		printf("请将配置好的.csv文件放置于该程序的同一目录下,重新运行此程序！\n\n");
		printf("程序将在10秒后自动退出......");
		Sleep(10000);
		exit(0);
	}
	else
	{
		if (fgetc(fp) == EOF)
		{
			printf("   目标文件内容为空！！！\n");
			printf("   请配置目标的.csv文件！\n\n");
			printf("程序将在10秒后自动退出......");
			Sleep(10000);
			exit(0);
		}
		printf("\b\b\b   成功！\n");
		Sleep(1500);
		system("cls");
	}

	FILE *ww = fopen("WrongWordList.csv", "w");
	fclose(ww); //以w方式打开会清除上次所写的内容，再次关闭，来达到清除源文件内容的目的。

	User info;
	info.all_words = 0;
	info.correct_number = 0;

	int line = 0;
	char t;
	while ((t = fgetc(fp)) != EOF)
	{
		if (t == '\n')
		{
			line++;
		}
	}
	rewind(fp);

	WORD_ WordList[line];
	WORDS WrongList[line];

	printf("请输入每个单词练习基数：");
	int times = integer_input();
	system("cls");

	for (int i = 0; i < line; i++)
	{
		fscanf(fp, "%[^,]", WordList[i].word);
		fgetc(fp);
		fscanf(fp, "%[^\n]", WordList[i].meaning);
		fgetc(fp);
		WordList[i].display_times = times;
	}
	fclose(fp);

	srand((unsigned)time(NULL));

	int word_i;
	int count = 1;

	char input_word[WORD_LEN];
	Boolean flag = True;
	Boolean a = True;
	char ch;
	int input_word_len;
	int i, j;
	int nums = 0;

	while (True)
	{
		while (flag)
		{
			word_i = rand() % line;
			if (WordList[word_i].display_times)
			{
				flag = False;
				WordList[word_i].display_times--;
				info.all_words++;
			}
		}
		

		printf("\n\n\n      Word.  %d  ", count);
		count++;

		printf("%s", WordList[word_i].meaning);
		printf("\n      输    入：");

		ch = getchar();
		input_word_len = 0;
		while (ch != '\n')
		{
			input_word[input_word_len++] = ch;
			ch = getchar();
		}
		input_word[input_word_len] = '\0';

		if (!strcmp(input_word, WordList[word_i].word))
		{
			printf("      单词输入正确！\n");
			info.correct_number++;
		}
		else
		{
			printf("      再次输入：");
			strcpy(input_word, ""); //清空字符数组

			ch = getchar();
			input_word_len = 0;
			while (ch != '\n')
			{
				input_word[input_word_len++] = ch;
				ch = getchar();
			}
			input_word[input_word_len] = '\0';

			if (strcmp(input_word, WordList[word_i].word) != 0)
			{
				WordList[word_i].display_times++;

				for (i = 0; i < line; i++)
				{
					if (strcmp(WrongList[i].word, input_word) == 0)
					{
						a = False;
					}
				}
				if (a)
				{
					ww = fopen("WrongWordList.csv", "a+");

					fprintf(ww, "%s", WordList[word_i].word);
					fprintf(ww, ",");
					fprintf(ww, "%s", WordList[word_i].meaning);
					fprintf(ww, "\n");

					fclose(ww);
				}
			}
			else
			{
				printf("      单词输入正确！\n");
				info.correct_number++;
			}
		}
		strcpy(input_word, "");

		printf("\n\n      当前正确率为：%.2lf", (info.correct_number / info.all_words));

		printf("\n\n      按下Enter键以继续...");
		getchar();

		// Sleep(2000);
		system("cls");

		for (j = 0; j < line; j++)
		{
			if (WordList[j].display_times == 0)
			{
				nums++;
			}
		}
		if (nums == line)
		{
			break;
		}

		flag = True;
	}

	printf("\n\n\n      你已经完成所有单词的练习！恭喜！");
	getchar();

	return 0;
}

int integer_input(void) // 定义一个限制只能输入整数的函数
{
	int n, judge;
	scanf("%d", &n);
	judge = getchar();
	while (judge != '\n')
	{
		fflush(stdin);
		printf("你的输入不规范，请重新输入!  ");
		scanf("%d", &n);
		judge = getchar();
	}
	return n;
}
