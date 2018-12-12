#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 20
typedef struct {
	int number;
	char name[M];
	char major[M];
	int team;
}info;
info infox[M];
int sum;

void menu()
{
	printf("*****************\n");
	printf("请先加载学生信息,否则无法操作\n");
	printf("0.加载学生信息\n");
	printf("1.卡号查找\n");
	printf("2.卡号排序输出\n");
	printf("3.姓名排序输出\n");
	printf("*****************\n");
}

void returnmenu()
{
	int i;
	printf("输入0返回主菜单");
	scanf("%d", &i);
	if (i == 0)
	{
		system("cls");
		menu();
	}
	else exit(1);
}

void numsort(info s[], int left, int right)
{
	int i, j;
		info temp, t;
		if (left > right)
			return;
		i = left; j = right;
		temp = s[i];
		/*printf("卡号:%-7d  ""姓名:%-9s  ""系:%-15s  ""班级:%d  \n", temp.number, temp.name, temp.major, temp.team);*/
		while (i != j)
		{
			while (s[j].number >= temp.number&&i < j)
				j--;
			while (s[i].number <= temp.number&&i < j)
				i++;
			if (i < j)
			{
				t = s[i];
				s[i] = s[j];
				s[j] = t;
			}
		}
		s[left] = s[i];
		s[i] = temp;
		numsort(s, left, i - 1);
		numsort(s, i + 1, right);
	}
void namesort(info s[], int left, int right)
{
	int i, j;
	info temp,t;
	if (left > right)
		return;
	temp =  s[left];
	i = left; j = right;
	while (i != j)
	{
		while ((strcmp(s[j].name,temp.name) >= 0)&& i < j)
			j--;
		while ((strcmp(s[i].name, temp.name) <= 0) &&  i < j)
			i++;
		if (i < j)
		{
			t = s[i];
			s[i] = s[j];
			s[j] = t;
		}
	}
	s[left] = s[i];
	s[i] = temp;
	namesort(s, left, i - 1);
	namesort(s, i + 1, right);
}

int numfind(info s[],int k)
{
	int low = 0, high = sum - 1, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (s[mid].number == k)
			return mid;
		if (s[mid].number > k)
			high = mid - 1;
		else low = mid + 1;
	}
	return -1;
}

void namefind()
{

}



void print(info s[], int sum)
{
	int i, j;
	for (i = 0; i < sum - 1; i++)
	{
		printf("卡号:%-7d  ""姓名:%-9s  ""系:%-15s  ""班级:%d  \n", s[i].number, s[i].name, s[i].major, s[i].team);
	}

}

void load(FILE *fp, info s[], int sum)
{
	int i;
	system("cls");
	for (i = 0; i < sum; i++)
	{
		fscanf(fp, "%d%s%s%d", &infox[i].number, &infox[i].name, &infox[i].major, &infox[i].team);
		printf("卡号:%-7d  ""姓名:%-9s  ""系:%-15s  ""班级:%d  \n", infox[i].number, infox[i].name, infox[i].major, infox[i].team);
	}
	returnmenu();
}





int main()
{
	int i, j, k;
	int a;
	FILE *fp;

	fp = fopen("C:\\Users\\Pec\\Desktop\\mycode\\邻接表\\stuinfo.txt", "r");
	fscanf(fp, "%d", &sum);
	menu();
	printf("请输入你的操作:");
	while (scanf("%d", &a) != EOF)
	{
		switch (a)
		{
		case 0: load(fp, infox, sum); break;
		case 1: {
			printf("请输入你需要查询的卡号");
			int num;
			scanf("%d", &num);
			int x = 0;
			x = numfind(infox, num);
			if (x >= 0)
			{
				int i = x;
				printf("卡号:%-7d  ""姓名:%-9s  ""系:%-15s  ""班级:%d  \n", infox[i].number, infox[i].name, infox[i].major, infox[i].team);
			}
			else
				printf("找不到该学生"); break;
		}
		case 2: numsort(infox, 0, sum - 1); print(infox, sum - 1);break;
		case 3: namesort(infox, 0, sum - 1); print(infox, sum - 1); break;
		default: {
			printf("你的输入有误,请重新输入:\n"); break;
		}
		}
	}
}


