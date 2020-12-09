#include<stdio.h>
#include<string.h>
//#include<conio.h>
#include<stdlib.h>

#define N 30
#define M 3

#define NUM_SIZE  16
#define NAME_SIZE  32

#define DATA_PATH  "./scorebase.txt"

typedef struct student{
	char number[NUM_SIZE];
	char name[NAME_SIZE];
	float score[M];
	float aver;
	float total;
}STU;

STU stu[N];

int n;
void inputscore(void);
void savescore(void);
void avergescore(void);
void total(void);
void modifyscore(void);
void lookscore(void);
void searchscore(void);
void statistic(void);
void add(void);
void modify(void);
void delscore(void);
void menu(void);
void loadscore();

int getStrings(char * str, int max_size)
{
    int num = 0;
    char c;

    do{
        scanf("%c", &c);
        str[ num ++ ] = c;
    }while(c != '\n' && num < max_size);

    str[num - 1] = '\0';

    return num - 1;
}

void cleanWindow()
{
	
#ifdef __unix
	//system("clear");
#else
	system("cls");
#endif
}
int main(int argc, char *argv[])
{
	int flag = 1;
	char opt = '0';
	
	do
	{
		menu();

#if 0	
#ifdef __unix
		switch(getchar())
#else
		switch(getch())
#endif
#endif
		scanf("%c",&opt);
		switch(opt)
		{
			case '1'://输入成绩
			case 1:
				printf("进入输入.....\n");
				inputscore();
				printf("输入完成....\n");
				//lookscore();
				break;
			case '2': //查看成绩
			case 2:
				lookscore();
				break;
			case '3': //查找成绩
			case 3:
				searchscore();
				break;
			case '4': //成绩统计
			case 4:
				statistic();
				break;
			case '5': //修改成绩
			case 5:
				modify();
				break;
			case '6': //添加成绩
			case 6:
				add();
				break;
			case '7': //删除成绩
			case 7:
				delscore();
				break;
			case '8': //保存成绩
			case 8:
				savescore();
				break;
			case 'Q'://退出程序
			case 'q':
				flag=0;
				//exit(0);
				break;
			case 'L'://加载文件中成绩
			case 'l':
				loadscore();
				break;
			default:
				printf("输入有误\n");
				break;
		}
		if(flag)
		{
			printf("按任意键继续\n");
#ifdef __unix
			getchar();
#else
			getch();
#endif
		}
	
	} while (flag == 1);
}

void menu(void)
{
	//system("cls");
	cleanWindow();
	printf("\n");
	printf("*********欢迎进入学生成绩管理系统**************\n");
	printf("*********菜单**************\n");
	printf("*********输入成绩*********1\n");
	printf("查看成绩及成绩排序2\n");
	printf("查询学生成绩3\n");
	printf("成绩统计4\n");
	printf("修改成绩5\n");
	printf("添加成绩6\n");
	printf("删除成绩7\n");
	printf("保存成绩8\n");
	printf("退出系统 Q or q\n");
	printf("加载文件中的成绩 L or l\n");
	printf("**********************************************\n");
	printf("请输入您的选择\n");
}
void inputscore(void)
{
	int i, j;
	//system("cls");
	cleanWindow();
	printf("请输入学生总数：\n");
	scanf("%d", &n);
	printf("提示：*输入学号时请输入由1位大写字母和8位数字组成的学号，如P0********\n");
	for (i = 0;i < n;i++)
	{
		printf("请输入学生%d的学号姓名：\n", i + 1);
		scanf("%s %s", stu[i].number, stu[i].name);
		//fgets(stu[i].number, NUM_SIZE, stdin);
		//getchar();
		//fgets(stu[i].name, NAME_SIZE, stdin);
		//fscanf(stdin,"%s %s",stu[i].number, stu[i].name);
		printf("请输入学生成绩:\n");
		printf("高数\t物理\tC语言\n");
		for (j = 0;j < M;j++)
			scanf("%f", &stu[i].score[j]);
	}
	printf("成功输入\n");
}

void total(void)
{
	int i, j;
	for (i = 0;i < n;i++)
	{
		stu[i].total = 0;
		for (j = 0;j < M;j++)
		{
			stu[i].total += stu[i].score[j];
		}
	}
}

void avergescore(void)
{
	int i, j;
	for (i = 0;i < n;i++)
	{
		stu[i].aver = 0;
		for (j = 0;j < M;j++)
		{
			stu[i].aver += stu[i].score[j];
		}
		stu[i].aver = stu[i].aver / M;
	}
}

void lookscore(void)
{
	int i, j, k;
	STU t;
	total();
	avergescore();
	//system("cls");
	cleanWindow();
	for (i = 0;i < n - 1;i++)
	{
		for (k = i, j = i + 1;j < n;j++)
			if (stu[j].aver > stu[k].aver)
				k = j;
		if (k != j)
		{
			t = stu[k];
			stu[k] = stu[i];
			stu[i] = t;
		}
	}
	printf("名次\t学号\t\t姓名\t\t高数\t物理\tC语言\t总分\t平均分\n");
	for (i = 0;i < n;i++)
	{
		printf("%d\t%s\t%s\t\t", i + 1, stu[i].number, stu[i].name);
		for (j = 0;j < M;j++)
			printf("%4.2f\t", stu[i].score[j]);
		printf("%4.2f\t", stu[i].total);
		printf("%4.2f", stu[i].aver);
		printf("\n");
	}
}

void searchscore(void)
{
	char a[10];
	int i, j;
	
	//system("cls");
	cleanWindow();
	printf("请输入需查询的学生学号\n");
	scanf("%s", a);
	for (i = 0;i < n;i++)
	{
		if (strcmp(a, stu[i].number) == 0)
		{
			printf("名次\t学号\t\t姓名\t高数\t物理\tC语言\t总分\t平均分\n");
			printf("%d\t%s\t%s\t", i + 1, stu[i].number, stu[i].name);
			for (j = 0;j < M;j++)
				printf("%4.2f\t", stu[i].score[j]);
			printf("%4.2f\t", stu[i].total);
			printf("%4.2f", stu[i].aver);
			printf("\n");
			break;//找到该学生成绩信息后跳出for循环
		}
		else
			printf("未找到该学生信息\n");
	}
}

void statistic(void)
{
	STU* p = stu;
	int i, j;
	float count, sum;
	
	//system("cls");
	cleanWindow();
	for (i = 0;i < n;i++)
	{
		sum += (p + i)->aver;
	}
	printf("该班级平均分为%4.2f\n", sum / n);
	//平均分计算
	for (i = 0;i < n;i++)
	{
		if ((p + i)->aver >= 60)
			count++;
	}
	printf("该班级及格率为%4.2f%%\n", count / n * 100);//及格率计算
	count;
	for (i = 0;i < n;i++)
	{
		if ((p + i)->aver >= 90)
			count++;
	}
	printf("平均分低于60的学生名单\n");
	for (i = 0;i < n;i++)
	{
		if (stu[i].aver < 60)
			printf("%s\n", stu[i].name);
	}
}
void modify(void)
{
	char a[10];
	int i, j;
	//system("cls");
	cleanWindow();
	printf("请输入需要修改成绩的学生学号\n");
	scanf("%s", a);
	for (i = 0;i < n;i++)
	{
		if (strcmp(a, stu[i].number) == 0)
		{
			printf("名次\t学号\t\t姓名\t高数\t物理\tC语言\t总分\t平均分\n");
			printf("%d\t%s\t%s\t", i + 1, stu[i].number, stu[i].name);
			for (j = 0;j < M;j++)
				printf("%4.2f\t", stu[i].score[j]);
			printf("%4.2f", stu[i].total);
			printf("%4.2f", stu[i].aver);
			printf("\n");
			printf("请重新输入该学生的学号 ,姓名:\n");
			scanf("%s%s", stu[i].number, stu[i].name);
			printf("请重新输入学生成绩:\n");
			printf("高数\t物理\tC语言\n");
			for (j = 0;j < M;j++)
				scanf("%f", &stu[i].score[j]);//找到该学生成绩后进行修改，跳出for循环
			printf("修改成功\n");
			break;
		}
		else
		printf("请确认该学生是否为本班学生！\n");
	}
}
void add(void)
{
	int a, i, j;
	//system("cls");
	cleanWindow();
	printf("请输入新增加的学生人数：\n");
	scanf("%d", &a);
	n = n + a;
	for (i = n - a;i < n;i++)
	{
		printf("请输入学生%d的学号?姓名:\n", i + 1);
		scanf("%s%s", stu[i].number, stu[i].name);
		printf("请输入学生成绩:\n");
		printf("高数\t物理\tC语言\n");
		for (j = 0;j < M;j++)
			scanf("%f", &stu[i].score[j]);
		printf("添加成功\n");
	}
}
void delscore(void)
{
	int i, j, c;
	char m, a[10];
	//system("cls");
	cleanWindow();
	printf("请输入学生学号\n");
	scanf("%s", a);
	for (i = 0;i < n;i++)
	{
		if (strcmp(a, stu[i].number) == 0)
		{
			printf("名次\t学号\t\t姓名\t高数\t物理\tC语言\t总分\t平均分\n");
			printf("%d\t%s\t%s\t", i + 1, stu[i].number, stu[i].name);
			for (j = 0;j < M;j++)
				printf("%4.2f\t", stu[i].score[j]);
			printf("%4.2f\t", stu[i].total);
			printf("%4.2f", stu[i].aver);
			printf("\n");
			c = i;
			break;
		}
		else
			printf("未找到该学生信息\n");
	}
	printf("是否删除该学生成绩(y/n)\n");
	scanf("%s", &m);
	if (m == 'y')
	{
		for (i = c;i < n - 1;i++)
			stu[i] = stu[i + 1];
		n = n - 1;
		printf("删除成绩成功\n");
	}
	else
		printf("删除成绩失败\n");
}
void savescore(void)
{
	FILE* fp;
	int i, flag = 1;
	char m;
	//system("cls");
	cleanWindow();
	puts("是否保存学生成绩(y/n)");
	scanf("%s", &m);
	if (m == 'y')
	{
		if ((fp = fopen(DATA_PATH, "w")) == NULL)
		{
			printf("文件打开失败\n");
			return;
		}
		
		for (i = 0;i < n;i++)
			if (fwrite(&stu[i], sizeof(struct student), 1, fp) != 1)
			{
				printf("保存失败\n");
				flag = 0;
			}
		
		if (flag == 1)
			printf("保存成功!\n");
		
		fclose(fp);
	}
}

void loadscore()
{
	FILE* fp;
	int   ret = 0;
	
	if ((fp = fopen(DATA_PATH, "r")) == NULL)
	{
		printf("文件打开失败\n");
		return;
	}
	do{
		ret=fread(&stu[n],sizeof(struct student), 1, fp);
		if( ret != 1 &&  ret != 0 )
		{
			printf("load failed  ret : %d\n", ret);
			break;
		}
		if(ret > 0)
		{
			n+=ret;
			printf("load %d .....\n", n);
		}
	} while(ret>0);
	
	
	fclose(fp);
	
}

