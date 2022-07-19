// version 22.2.16
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string.h>

#define WORD_LEN 20  // ���������������ĳ���

int input_word_len;  // ����һ�����뵥�ʳ��ȵı���
int actual_word_len; // ����һ��ʵ�ʵ��ʳ��ȵı���

void input_word(char write[], int a);      // ����һ�����뵥�ʵĺ���
int word_judge(char word[], char write[]); // ����һ���ж����뵥���Ƿ���ȷ�ĺ���
int integer_input(void);                   // ����һ������ֻ�����������ĺ���

struct PI
{
	double all_words;          // �û�����������е�����
	double correct_number;     // �û���Եĵ��ʸ���
	double accuracy;           // �û�����ȷ��
	char wrong_word[WORD_LEN]; // ������ʱ��¼�û�д��ĵ���
	int byte_num[];            // ���ڼ�¼�����ļ�ÿ�����з�����һ���ֽڵ��ֽ���
} user;

int main(void)
{
	int num = 1, t, n = 0, test_num, line, flag, flag1, flag2, flag3;
	char word[WORD_LEN], write[WORD_LEN], rewrite[WORD_LEN], ch, file_name[WORD_LEN], _txt[5] = ".txt";
	/*
        num��ÿ�����ʵ�˳��
        t�����ڽ��ջ�ȡ�ı��ļ����ַ�����ֵ
        n�����ڸ�����¼byte_num
        test_num����Ҫ��ϰ�ĵ��ʸ��������ʿ��ܻ��ظ������������ᣩ
        line�����������
    */
	
	FILE *word_loaction;  // �����ļ���ָ��
	FILE *wrong_word_txt; // ���д�����ļ���ָ��
	
	printf("\n");
	
	puts("����������Ҫ��ϰ���ʵ��ı��ļ���");
	gets(file_name);
	
	flag = 1; // �ж��û�������ļ���������.txt�������Ͳ���
	for(int i=0;i<(WORD_LEN-3);i++)
	{
		if(file_name[i]=='.'&&file_name[i+1]=='t'&&file_name[i+2]=='x'&&file_name[i+3]=='t')
		{
			flag = 0;
			break;
		}
	}
	if(flag==1)
	{
		strcat(file_name, _txt);
	}
	
	word_loaction = fopen(file_name, "r");
	// �������������ж��Ƿ��ҵ��ļ�
	printf("���ڶ�ȡ�ļ� ");
	Sleep(300);
	if (word_loaction == NULL)
	{
		printf("   ʧ�ܣ�\n");
		printf("�뽫���úõĵ����ı��ļ������ڸó����ͬһĿ¼��,�������д˳���\n\n");
		printf("������10����Զ��˳�......");
		Sleep(10000);
		exit(0);
	}
	else
	{
		if (fgetc(word_loaction) == EOF)
		{
			printf("   Ŀ���ļ�����Ϊ�գ�����\n");
			printf("   �����õ����ı��ļ���\n\n");
			printf("������10����Զ��˳�......");
			Sleep(10000);
			exit(0);
		}
		printf("   �ɹ���\n");
		Sleep(1500);
		// system("cls");
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
	printf("\n��ǰ�ļ����е�����[%d]", n);
	
	srand((unsigned)time(NULL)); // ���֣�ʹÿ��ƴд�ĵ��ʲ�һ��
	
	test_num = integer_input(); // ��������Ϊ����
	system("cls");
	printf("\n");
	
	// ��������ֵ��Ϊ�㣬��ô���Լ�����ȷ�ʣ����Ѵ���ĵ���д���ļ�
	if (test_num != 0)
		wrong_word_txt = fopen("wrong_words.txt", "w");
	user.all_words = test_num;
	user.correct_number = 0;
	
	for (int i = 0; i < test_num; i++)
	{
		for (int v = 0; v < WORD_LEN; v++) // �������ַ������ʼ��Ϊ�ո�
		{                                  // ����д���ļ��󣬼��±����ļ�������֡��ڡ�
			word[v] = ' ';
			write[v] = ' ';
			rewrite[v] = ' ';
		}
		
		line = rand() % n;
		fseek(word_loaction, user.byte_num[line], SEEK_SET);
		/*
            fseek����������������λ�ã�
            Ŀ����ʹ��ʱ�Ĺ��Ϊһ�еĿ�ʼ��
            byte_num�����ÿ��Ԫ�ض���ÿһ�еĿ�ͷ�ֽ���
            byte_num[0]�ǵ�һ�У�byte_num[1]�ǵڶ���...
        */
		
		printf("    Word %d ", num); // ���ʵĸ�����˳��1��2��3��4...��
		
		// ������¼��word�ַ�������
		actual_word_len = 0;
		ch = fgetc(word_loaction);
		while (ch != '#')
		{
			word[actual_word_len] = ch;
			actual_word_len++;
			ch = fgetc(word_loaction);
		}
		ch = fgetc(word_loaction); // �ﵽ'#'����ʾ��Ч��
		// �����������
		while (ch != '\n')
		{
			putchar(ch);
			ch = fgetc(word_loaction);
		}
		
		printf("\n");
		
		for (int j = 0; j < WORD_LEN; j++)
			user.wrong_word[j] = word[j]; // ����ȷ�ĵ��ʸ���д��ĵ��ʵ��ַ����飬�Ժ��д�������ʹ�õ���user.wrong_word�ַ�����
		input_word(write, 1);             // ���иú�����¼��ƴд�ĵ���
		flag1 = word_judge(word, write);  // ���иú����Ի�öԺʹ�ķ���ֵ
		
		if (flag1 == 0) // ���������ʱ��ʼִ��
		{
			
			flag3 = 1;
			
			input_word(rewrite, 2);
			flag2 = word_judge(word, rewrite);
			
			if (flag2 == 1) // ��д����
			{
				user.correct_number++; // ��Ը���+1�����ڼ�����ȷ��
				printf("����������ȷ\n");
				printf("---------------------------------------------\n\n");
			}
			
			if (flag2 == 0) // ��д����
			{
				printf("��ȷ�ĵ���ƴдΪ  ");
				for (int q = 0; q < actual_word_len; q++)
					printf("%c", word[q]);
				printf("\n---------------------------------------------\n\n");
				flag3 = 0;
			}
			
			if (flag3 == 0)
			{
				fputs(user.wrong_word, wrong_word_txt); // ������ĵ���д��wrong_words.txt�ļ���
				fputs("\n", wrong_word_txt);            // ��дһ������
			}
		}
		else
		{
			user.correct_number++;
			printf("����������ȷ\n");
			printf("---------------------------------------------\n\n");
			Sleep(300);
		}
		num++;
	}
	
	if (user.all_words != 0)
		user.accuracy = user.correct_number / user.all_words;
	printf("\n�������\n�����ȷ��Ϊ[%.2lf%%]", user.all_words != 0 ? user.accuracy * 100 : user.all_words);
	
	fclose(word_loaction);
	fclose(wrong_word_txt);
	
	printf("\n\n����Enter�����˳�����...");
	getchar();
	
	return 0;
}

void input_word(char write[], int a) // ����һ�����뵥�ʵĺ���
{
	char ch;
	printf("%s", a == 1 ? "                              ���룺" : "�����������������          ���룺");
	input_word_len = 0;
	ch = getchar();
	while (ch != '\n')
	{
		write[input_word_len] = ch;
		input_word_len++;
		ch = getchar();
	}
}

int word_judge(char word[], char write[]) // ����һ���ж����뵥���Ƿ���ȷ�ĺ���
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

int integer_input(void) // ����һ������ֻ�����������ĺ���
{
	// �������>>>https://blog.csdn.net/weixin_50952196/article/details/108903861
	int n, judge;
	printf("\n����������Ҫ��ϰ�ĵ��ʸ���   ");
	scanf("%d", &n);
	judge = getchar();
	while (judge != '\n')
	{
		fflush(stdin);
		printf("������벻�淶������������!  ");
		scanf("%d", &n);
		judge = getchar();
	}
	return n;
}