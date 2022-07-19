// version 22.2.11
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define WORD_LEN 20 // 用于设置相关数组的长度

int input_word_len;  // 定义一个输入单词长度的变量
int actual_word_len; // 定义一个实际单词长度的变量

void input_word(char write[]);             // 声明一个输入单词的函数
int word_judge(char word[], char write[]); // 声明一个判断输入单词是否正确的函数
int integer_input(void);                   // 声明一个限制只能输入整数的函数

struct PI
{
	double all_words;          // 用户的所答的所有单词数
	double correct_number;     // 用户答对的单词个数
	double accuracy;           // 用户的正确率
	char wrong_word[WORD_LEN]; // 用于临时记录用户写错的单词
	int byte_num[];            // 用于记录单词文件每个换行符的下一个字节的字节数
} user;

int main(void)
{
	int num = 1, t, n = 0, test_num, line, flag1, flag2, flag3;
	char word[WORD_LEN], write[WORD_LEN], rewrite[WORD_LEN], ch, ch2, ch3;
	/*
        num，每个单词的顺序
        t，用于接收获取文本文件的字符返回值
        n，用于辅助记录byte_num
        test_num，想要练习的单词个数（单词可能会重复，但次数不会）
        line，随机的行数
    */
	
	FILE *word_loaction;  // 单词文件的指针
	FILE *wrong_word_txt; // 存放写错单词文件的指针
	
	printf("\n");
	
	word_loaction = fopen("words.txt", "r");
	
	// 以下内容用于判断是否找到文件
	printf("    正在读取单词文本文件 ");
	Sleep(200);
	if (word_loaction == NULL)
	{
		printf("   失败！\n");
		printf("    请将配置好的单词文本文件放置于该程序的同一目录下,重新运行此程序！\n\n");
		printf("    程序将在10秒后自动退出......");
		Sleep(10000);
		exit(0);
	}
	else
	{
		if (fgetc(word_loaction) == EOF)
		{
			printf("   目标文件内容为空！！！\n");
			printf("    请配置单词文本文件！\n\n");
			printf("    程序将在10秒后自动退出......");
			Sleep(10000);
			exit(0);
		}
		printf("   成功！");
		Sleep(1500);
		system("cls");
	}
	
	user.byte_num[0] = 0;
	while ((t = fgetc(word_loaction)) != EOF)
	{
		if (t == '\n')
		{
			n++;
			user.byte_num[n] = ftell(word_loaction);
		}
	}
	// printf("%d", n);
	
	srand((unsigned)time(NULL)); // 播种，使每次拼写的单词不一样
	
	test_num = integer_input(); // 限制输入为整数
	printf("\n");
	
	// 如果输入的值不为零，那么可以计算正确率，并把错误的单词写入文件
	if (test_num != 0)
		wrong_word_txt = fopen("wrong_words.txt", "w");
	user.all_words = test_num;
	user.correct_number = 0;
	
	for (int i = 0; i < test_num; i++)
	{
		for (int v = 0; v < WORD_LEN; v++) // 将所有字符数组初始化为空格，
		{                                  // 方便写入文件后，记事本打开文件不会出现乱码，也方便系统校对单词
			word[v] = ' ';
			write[v] = ' ';
			rewrite[v] = ' ';
		}
		
		line = rand() % n;
		fseek(word_loaction, user.byte_num[line], SEEK_SET);
		/*
            fseek函数用来调整光标的位置，
            目的是使此时的光标为一行的开始，
            byte_num数组的每个元素都是每一行的开头字节数
            byte_num[0]是第一行，byte_num[1]是第二行...
        */
		
		printf("    Word %d ", num); // 单词的个数（顺序，1、2、3、4...）
		
		// 将单词录入word字符数组中
		actual_word_len = 0;
		ch = fgetc(word_loaction);
		while (ch != '#') // 可以修改此处实现录入录入词组，我太懒了，现在不想做
		{
			word[actual_word_len] = ch;
			actual_word_len++;
			ch = fgetc(word_loaction);
		}
		ch = fgetc(word_loaction); // 达到'#'不显示的效果
		// 输出单词释义
		while (ch != '\n')
		{
			putchar(ch);
			ch = fgetc(word_loaction);
		}
		
		printf("\n");
		
		for (int j = 0; j < WORD_LEN; j++)
			user.wrong_word[j] = word[j]; // 将正确的单词赋给写错的单词的字符数组，以后的写入操作，使用的是user.wrong_word字符数组
		input_word(write);                // 运行该函数以录入拼写的单词
		flag1 = word_judge(word, write);  // 运行该函数以获得对和错的返回值
		
		if (flag1 == 0) // 当输入错误时开始执行
		{
			
			flag3 = 1;
			printf("输入错误，是否再试一次  ");
			
			ch2 = ch3 = getchar();
			while (ch2 != '\n')
				ch2 = getchar();
			// 收集从第二个开始，'\n'结尾的字符，防止用户输入过多字符导致程序出问题
			
			if (ch3 == 'y' || ch3 == 'Y') // 开始单词重写
			{
				input_word(rewrite);
				flag2 = word_judge(word, rewrite);
				
				if (flag2 == 1) // 重写对了
				{
					user.correct_number++; // 答对个数+1，用于计算正确率
					printf("单词输入正确\n");
					printf("---------------------------------------------\n\n");
				}
				if (flag2 == 0) // 重写错了
				{
					printf("正确的单词拼写为  ");
					for (int q = 0; q < actual_word_len; q++)
						printf("%c", word[q]);
					printf("\n---------------------------------------------\n\n");
					flag3 = 0;
				}
			}
			else
			{
				printf("正确的单词拼写为  ");
				for (int m = 0; m < actual_word_len; m++)
					printf("%c", word[m]);
				printf("\n---------------------------------------------\n\n");
				flag3 = 0;
			}
			
			if (flag3 == 0)
			{
				fputs(user.wrong_word, wrong_word_txt); // 将错误的单词写入wrong_words.txt文件中
				fputs("\n", wrong_word_txt);            // 补写一个换行
			}
		}
		else
		{
			user.correct_number++;
			printf("单词输入正确\n");
			printf("---------------------------------------------\n\n");
			Sleep(300);
		}
		num++;
	}
	
	if (user.all_words != 0)
		user.accuracy = user.correct_number / user.all_words;
	printf("\n程序结束,你的正确率为%.2lf%%", user.all_words != 0 ? user.accuracy * 100 : user.all_words);
	
	fclose(word_loaction);
	fclose(wrong_word_txt);
	
	printf("\n\n按下Enter键以退出程序...");
	getchar();
	
	return 0;
}

void input_word(char write[]) // 定义一个输入单词的函数
{
	char ch;
	printf("                              输入：");
	input_word_len = 0;
	ch = getchar();
	while (ch != '\n')
	{
		write[input_word_len++] = ch;
		ch = getchar();
	}
}

int word_judge(char word[], char write[]) // 定义一个判断输入单词是否正确的函数
{
	int flag = 1;
	for (int i = 0; i < WORD_LEN; i++)
	{
		if (word[i] != write[i])
		{
			flag = 0;
			break;
		}
	}
	
	if (flag == 1)
		return 1;
	else
		return 0;
}

int integer_input(void) // 定义一个限制只能输入整数的函数
{
	// 代码详解>>>https://blog.csdn.net/weixin_50952196/article/details/108903861
	int n, judge;
	printf("\n    请输入你想要练习的单词个数（整数，单位：个）  ____\b\b\b");
	scanf("%d", &n);
	judge = getchar();
	while (judge != '\n')
	{
		fflush(stdin);
		printf("    你的输入不规范，请重新输入!  ____\b\b\b");
		scanf("%d", &n);
		judge = getchar();
	}
	return n;
}