/**************************头文件声明************************************/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"

/**************************函数声明************************************/

void init();	                     //初始化函数
void add();                          //信息录入函数
void view();                         //信息显示函数
void mod();                          //信息修改函数
void modmeun();                      //修改菜单
void modnavimeun();                  //路线修改菜单
void del();                          //信息删除函数
void find();                         //信息查询函数
void findmeun();                     //查询菜单
void findnavi();                     //路线导航查询函数
void findnum();                      //路线编号查询函数
void findstameun();                  //站台信息查询菜单
void findsta();                      //站台信息查询函数
void save();                         //信息保存函数
void mainmeun();                     //主菜单
char Test(char a,char b,char c);     //菜单输入检测函数

/**************************宏定义声明************************************/
#define N 100                    //公交车数量

/**************************结构体定义************************************/
struct station                   //途径站点信息
{
	char c[20];                  //站点名称
};

struct bus                       //公交车信息
{
	char num[20];                //公交车路线编号
	char name[20];               //司机姓名
	int n;                       //站台数目
	struct station b[12];        //站台名称
	char topen[20];              //起始时间
	char tclose[20];             //终止时间
	int money;                   //票价
}a[N];


/**************************函数定义************************************/

int main()
{
	char a;
	init();
	printf("\n\t\t目前所能录入的公交车数量上限为 %d 辆\n\n",N);
	printf("\n\t\t输入回车键继续\n");
	fflush(stdin);                           //清除键盘缓冲区
	while(1)
	{
		system("cls");
		mainmeun();
		a=Test(getchar(),'1','6');      //菜单检测输入函数
		switch(a)
		{
		case '1':	system("cls"); add(); break;
		case '2':	system("cls"); view(); break;
		case '3':	system("cls"); mod(); break;
		case '4':	system("cls"); del(); break;
		case '5':   system("cls"); find(); break;
		case '6':   return 0;
		}
	}
	return 0;
}

void init()     //初始化函数
{
	FILE *fp;                        //文件指针
	int i;
	if((fp=fopen("bus.txt","r+"))==NULL)                  //初次尝试打开"bus.txt"文本文件
	{
		printf("\n\t\t文件打开失败\n\n\t\t正在尝试创建新文件...\n");
		fp=fopen("bus.txt","w");                          //创建"bus.txt"文本文件
		if((fp=fopen("bus.txt","r+"))==NULL)              //再次判断是否打开成功
		{
			printf("\t\t文件创建失败!!!\n");
			return;
		}
	}
	fp=fopen("bus.txt","r+");
	for(i=0;i<N;i++)                                          //将磁盘中的信息输出到内存中
		if(fread(&a[i],sizeof(struct bus),1,fp)!=1)
			break;
	fclose(fp);
	printf("\n\t\t初始化完成!!!\n\n");
	return;
}

void add()     //信息录入函数
{
	FILE *fp=NULL;                        //文件指针
	int i,j;
	char cc[20];
	for(i=0;i<N;i++)
	{
		if(*a[i].num!='\0')
			continue;
		else
		{
			printf("\n添加第%d辆公交车路线记录:\n",i+1);
			printf("\n请输入路线编码(3位编码，第一位为大写字母，后两位为数字):\n");    //路线编码
			scanf("%s",cc);
			for(j=0;j<N;j++)                                                           //检验是否重复
				if(strcmp(a[j].num,cc)==0)
				{
					printf("\n与已有路线编码重复，按回车键返回!!!\n");
					fflush(stdin);                           //清除键盘缓冲区
					getchar();
					system("cls");
					return;
				}
			strcpy(a[i].num,cc);
			printf("\n请输入司机姓名: ");                                              //司机姓名
			scanf("%s",a[i].name);
			printf("\n请输入途径站台总数(>=2): ");                                     //站台总数
			scanf("%d",&a[i].n);
			printf("\n");
			if(a[i].n<2||a[i].n>12)
			{
				while(a[i].n<2||a[i].n>12)
				{
					printf("\n站台总数应满足(2<=n<=12)，请重新输入: ");
					scanf("%d",&a[i].n);
					printf("\n");
				}
			}
			for(j=0;j<a[i].n;j++)
			{
				printf("请输入第%d个站台名称: ",j+1);                    //站台名称
				scanf("%s",a[i].b[j].c);
			}
			printf("\n自动生成公交路线:(1) %s",a[i].b[0].c);
			for(j=1;j<a[i].n;j++)
			{
				printf(" ----> (%d) %s",j+1,a[i].b[j].c);
			}
			printf("\n\n请输入公交车的起始时间(格式为：时:分): ");       //起始时间
			scanf("%s",a[i].topen);
			printf("请输入公交车的终止时间(格式为：时:分): ");           //终止时间
			scanf("%s",a[i].tclose);
			printf("\n请输入公交车的票价: ");                            //票价
			scanf("%d",&a[i].money);
			printf("\n第%d辆公交车路线记录创建成功!!!\n",i+1);
			save();
			printf("\n\t按回车键返回!!!\n");
			fflush(stdin);                           //清除键盘缓冲区
			getchar();
			system("cls");
			return;
		}
	}
	if(i==N)
		printf("\n\n\n\t空间已满，不能录入!!!\n");
	printf("\n\t按回车键返回!!!\n");
	fflush(stdin);                           //清除键盘缓冲区
	getchar();
	system("cls");
	return;
}


void view()    //信息显示函数
{
	int i,j,min;
	struct bus t;
	for(i=0;*a[i].num!='\0'&&i<N;i++)               //按“路线编号”用选择法排序
	{
		min=i;
		for(j=i+1;*a[j].num!='\0'&&j<N;j++)
			if(strcmp(a[i].num,a[j].num)>0)
				min=j;
		t=a[i];
		a[i]=a[min];
		a[min]=t;
	}
	printf("\n\n                              公交车信息库");
	printf("\n********************************************************************************\n");
	for(i=0;*a[i].num!='\0'&&i<N;i++)
	{
		printf("\t路线编号: %-6s\t单程票价: %d 元\t\t司机姓名: %s\n",a[i].num,a[i].money,a[i].name);
		printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n",a[i].topen,a[i].tclose,a[i].n);
		printf("\t公交路线:(1) %s",a[i].b[0].c);
		for(j=1;j<a[i].n;j++)
			printf(" ---->(%d) %s",j+1,a[i].b[j].c);
		printf("\n\n");
	}
	printf("\n********************************************************************************\n");
	printf("\n\t\t公交车信息显示完毕!!!\n");
	printf("\n\t\t输入回车键返回主菜单:");
	fflush(stdin);                           //清除键盘缓冲区
	getchar();
	system("cls");
	return;
}



void mod()                          //信息修改函数
{
	int i,j,m=0;
	char t,cc[20],mod[20];
	printf("请输入要修改信息的公交车路线编号:\n");
	scanf("%s",cc);
	for(i=0;*a[i].num!='\0'&&i<N;i++)     //查找所输入的公交车
	{
		if(strcmp(a[i].num,cc)==0)
		{
			m=1;
			printf("\n\n\t\t已找到!!!\n");
			while(1)
			{
				system("cls");
				printf("\n\n                            正在修改的公交车信息\n");
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
				printf("\t路线编号: %-6s\t单程票价: %d 元\t\t司机姓名: %s\n",a[i].num,a[i].money,a[i].name);
				printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n",a[i].topen,a[i].tclose,a[i].n);
				printf("\t公交路线:(1) %s",a[i].b[0].c);
				for(j=1;j<a[i].n;j++)
					printf(" ---->(%d) %s",j+1,a[i].b[j].c);
				printf("\n\n");
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
				modmeun();
				fflush(stdin);                           //清除键盘缓冲区
				t=Test(getchar(),'1','5');      //菜单检测输入函数
				system("cls");
				switch(t)
				{
				case '1':           //修改路线编号
					{
						int k;
						printf("\n请输入新的公交车编号:");
						scanf("%s",mod);
						for(k=0;*a[k].num!='\0'&&k<N;k++)
						{
							if(strcmp(a[k].num,mod)==0)
							{
								printf("与已有编号重复,按回车键返回主菜单\n");
								fflush(stdin);                           //清除键盘缓冲区
								getchar();
								system("cls");
								return;
							}
						}
						strcpy(a[i].num,mod);
						save();
						break;
					}
				case '2':           //修改车辆信息
					{
						printf("\n请输入新的司机姓名:");
						scanf("%s",a[i].name);
						printf("\n请输入新的公交车票价:");
						scanf("%d",&a[i].money);
						save();
						break;
					}
				case '3':           //修改行车路线
					{
						void modnavimeun(); //路线修改菜单
						int k;
						char z;
						while(1)
						{
							system("cls");
							modnavimeun();
							fflush(stdin);                           //清除键盘缓冲区
							z=Test(getchar(),'1','5');      //菜单检测输入函数
							system("cls");
							switch(z)
							{
							case '1':     //添加站点
								{
									if(a[i].n+1>12)             //判断是否满足条件
									{
										printf("\n站台总数达到12个，无法添加新站点\n\n按回车键返回\n");
										fflush(stdin);                           //清除键盘缓冲区
										getchar();
										system("cls");
										return;
									}
									printf("\n请输入需要添加第几个站点：");
									scanf("%d",&k);
									while(a[i].n+1<k)
									{
										printf("目前共%d个站点，无法添加第%d个站点\n请重新输入：",a[i].n,k);
										scanf("%d",&k);
										printf("\n");
									}
									a[i].n=a[i].n+1;
									for(j=a[i].n;j>k-1;j--)
									{
											a[i].b[j]=a[i].b[j-1];
									}
									printf("\n请输入新添加的站点名称：");
									scanf("%s",a[i].b[k-1].c);
									save();
									break;
								}
							case '2':     //修改站点
								{
									printf("\n请输入需要修改第几个站点：");
									scanf("%d",&k);
									printf("\n请输入新的站点名称：");
									scanf("%s",a[i].b[k-1].c);
									save();
									break;
								}
							case '3':     //删除站点
								{
									printf("\n请输入需要删除第几个站点：");
									scanf("%d",&k);
									for(j=k-1;j<a[i].n;j++)
									{
										a[i].b[j]=a[i].b[j+1];
									}
									a[i].n=a[i].n-1;
									save();
									break;
								}
							case '4':     //重置路线
								{
									printf("\n请输入新的途径站台总数(2<=n<=12): ");
									scanf("%d",&a[i].n);
									printf("\n");
									while(a[i].n<2||a[i].n>12)             //判断是否满足条件
									{
										printf("\n站台总数应满足(2<=n<=12)，请重新输入: ");
										scanf("%d",&a[i].n);
										printf("\n");
									}
									for(j=0;j<a[i].n;j++)
									{
										printf("请输入新的第%d个站台名称: ",j+1);
										scanf("%s",a[i].b[j].c);
									}
									printf("\t公交路线:(1) %s",a[i].b[0].c);
									for(j=1;j<a[i].n;j++)
										printf(" ---->(%d) %s",j+1,a[i].b[j].c);
									printf("\n\n");
									save();
									break;
								}
							case '5':     //返回菜单
								{
									printf("\n\t\t按回车键返回菜单\n");
									fflush(stdin);                           //清除键盘缓冲区
									getchar();
									system("cls");
									return;                            //返回主菜单
								}
							}
						}
					}
				case '4':           //修改行车时间
					{
						printf("\n\n请输入公交车的起始时间(格式为：时:分): ");
						scanf("%s",a[i].topen);
						printf("请输入公交车的终止时间(格式为：时:分): ");
						scanf("%s",a[i].tclose);
						save();
						break;
					}
				case '5':
					{
						printf("\n\t\t按回车键返回主菜单\n");
						fflush(stdin);                           //清除键盘缓冲区
						getchar();
						system("cls");
						return;                            //返回主菜单
					}
				}
			}
		}
	}
	if(m==0)
		printf("\n\n\t\t无此公交车信息!!!\n");
	printf("\n\t\t按回车键返回\n");
	fflush(stdin);                           //清除键盘缓冲区
	getchar();
	system("cls");
	return;
}



void modmeun()  //修改菜单
{
	printf("\n\t\t                 修改菜单                   ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1、修改路线编号               *");
	printf("\n\t\t*            2、修改车辆信息               *");
	printf("\n\t\t*            3、修改行车路线               *");
	printf("\n\t\t*            4、修改行车时间               *");
	printf("\n\t\t*            5、返回到主菜单               *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t请输入您的选择:");
}


void modnavimeun() //路线修改菜单
{
	printf("\n\t\t               路线修改菜单                 ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1、 站 点 添 加               *");
	printf("\n\t\t*            2、 站 点 修 改               *");
	printf("\n\t\t*            3、 站 点 删 除               *");
	printf("\n\t\t*            4、 路 线 重 置               *");
	printf("\n\t\t*            5、 返 回 菜 单               *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t请输入您的选择:");
}


void del()       //信息删除函数
{
	int i,j,t,m=0;
	char cc[20];
	printf("\n请输入要删改信息的公交车路线编号:\n");
	scanf("%s",cc);
	for(i=0;*a[i].num!='\0'&&i<N;i++)     //查找所输入的公交车
	{
		if(strcmp(a[i].num,cc)==0)
		{
			m=1;
			printf("\n已找到:\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
			printf("\t路线编号: %-6s\t单程票价: %d 元\t\t司机姓名: %s\n",a[i].num,a[i].money,a[i].name);
			printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n",a[i].topen,a[i].tclose,a[i].n);
			printf("\t公交路线:(1) %s",a[i].b[0].c);
			for(j=1;j<a[i].n;j++)
				printf(" ---->(%d) %s",j+1,a[i].b[j].c);
			printf("\n\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
			printf("即将删除该公交车信息!!!\n确定请按1：");
			scanf("%d",&t);
			if(t==1)
			{
				if(i+1==N)
					memset(&a[i],'\0',sizeof(struct bus));      //最后一辆直接进行清空
				else
					for(j=i;*a[j].num!='\0'&&j+1<N;j++)         //后面的公交车信息补上删去的公家车信息
						a[j]=a[j+1];
				printf("编号为%s的公交车信息删除完毕!\n",cc);
				save();
				break;
			}
		}
	}
	if(m==0)
		printf("\n\n\t\t无此公交车信息!!!\n");
	printf("\n\n\t输入回车键返回主菜单:");
	fflush(stdin);                           //清除键盘缓冲区
	getchar();
	system("cls");
	return;
}


void find()    //信息查询函数
{
	char t;
	while(1)
	{
		findmeun();
		fflush(stdin);                           //清除键盘缓冲区
		t=Test(getchar(),'1','4');      //菜单检测输入函数
		switch(t)
		{
		case '1': system("cls"); findnavi();break;         //路线导航查询
		case '2': system("cls"); findnum();break;          //路线编号查询函数
		case '3': system("cls"); findsta();break;          //站台信息查询函数
		case '4': system("cls"); return;                    //返回主菜单
		}
	}
	return;
}


void findmeun()  //查询菜单
{
	printf("\n\t\t                 查询菜单                   ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1、路线导航查询               *");
	printf("\n\t\t*            2、路线编号查询               *");
	printf("\n\t\t*            3、站台信息查询               *");
	printf("\n\t\t*            4、返回到主菜单               *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t请输入您的选择:");
}


void findnavi()        //路线导航查询函数
{
	int i,j,k,m=0;
	char c1[20],c2[20];
	printf("请输入您目前所在的站点:\n\t\t");
	scanf("%s",c1);
	printf("请输入您想要前往的站点:\n\t\t");
	scanf("%s",c2);
	printf("\n\n您可选择的公交车信息如下\n");
	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
	for(i=0;*a[i].num!='\0'&&i<N;i++)
	{
		for(j=0;j<a[i].n;j++)
			for(k=j+1;k<a[i].n;k++)
				if(strcmp(a[i].b[j].c,c1)==0&&strcmp(a[i].b[k].c,c2)==0)
				{
					m=1;
					printf("\n");
					printf("\t路线编号: %-6s\t单程票价: %d 元\t\t司机姓名: %s\n",a[i].num,a[i].money,a[i].name);
					printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n",a[i].topen,a[i].tclose,a[i].n);
					printf("\t公交路线:(1) %s",a[i].b[0].c);
					for(j=1;j<a[i].n;j++)
						printf(" ---->(%d) %s",j+1,a[i].b[j].c);
					printf("\n\n");
				}
	}
	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
	printf("\t\t\t\t显示完毕\n");
	if(m==0)
		printf("\n\n\t\t\t\t抱歉,无途径此路线的公交车\n");
	printf("\n\t\t\t\t输入回车键返回查询菜单:");
	fflush(stdin);                           //清除键盘缓冲区
	getchar();
	system("cls");
	return;
}


void findnum()           //路线编号查询函数
{
	int i,j,m=0;
	char cc[20];
	printf("请输入您想要查找的公交路线编号:\n");
	scanf("%s",cc);
	for(i=0;*a[i].num!='\0'&&i<N;i++)
	{
		if(strcmp(a[i].num,cc)==0)
		{
			m=1;
			printf("\n已找到:\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
			printf("\t路线编号: %-6s\t单程票价: %d 元\t\t司机姓名: %s\n",a[i].num,a[i].money,a[i].name);
			printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n",a[i].topen,a[i].tclose,a[i].n);
			printf("\t公交路线:(1) %s",a[i].b[0].c);
			for(j=1;j<a[i].n;j++)
				printf(" ---->(%d) %s",j+1,a[i].b[j].c);
			printf("\n\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
			break;
		}
	}
	if(m==0)
		printf("\n\t\t无此公交车信息\n");
	printf("\n\t\t输入回车键返回查询菜单:");
	fflush(stdin);                           //清除键盘缓冲区
	getchar();
	system("cls");
	return;
}


 void findstameun()  //站台信息查询菜单
{
	printf("\n\t\t             站台信息查询菜单");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1、起始站台查询               *");
	printf("\n\t\t*            2、终止站台查询               *");
	printf("\n\t\t*            3、途径站台查询               *");
	printf("\n\t\t*            4、返回查询菜单               *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t请输入您的选择:");
}


void findsta()       //站台信息查询函数
{
	int i,j,k;
	char t;
	char cc[20];
	while(1)
	{
		int m=0;
		findstameun();
		fflush(stdin);                           //清除键盘缓冲区
		t=Test(getchar(),'1','4');      //菜单检测输入函数
		system("cls");
		switch(t)
		{
		case '1':
			{
				printf("请输入您所要查询的起始站台名称:\n");
				scanf("%s",cc);
				printf("\n以%s为起始站台的公交车如下:\n",cc);
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
				for(i=0;*a[i].num!='\0'&&i<N;i++)
				{
					if(strcmp(a[i].b[0].c,cc)==0)
					{
						m=1;
						printf("\n");
						printf("\t路线编号: %-6s\t单程票价: %d 元\t\t司机姓名: %s\n",a[i].num,a[i].money,a[i].name);
						printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n",a[i].topen,a[i].tclose,a[i].n);
						printf("\t公交路线:(1) %s",a[i].b[0].c);
						for(j=1;j<a[i].n;j++)
							printf(" ---->(%d) %s",j+1,a[i].b[j].c);
						printf("\n\n");
					}
				}
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
				printf("\t已全部显示完毕!!!\n");
				if(m==0)
					printf("\n\t没有公交车以该站点为起始站台\n");
				break;
			}
		case '2':
			{
				printf("请输入您所要查询的终止站台名称:\n");
				scanf("%s",cc);
				printf("\n以%s为终止站台的公交车如下:\n",cc);
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
				for(i=0;*a[i].num!='\0'&&i<N;i++)
				{
					k=a[i].n;
					if(strcmp(a[i].b[k-1].c,cc)==0)
					{
						m=1;
						printf("\n");
						printf("\t路线编号: %-6s\t单程票价: %d 元\t\t司机姓名: %s\n",a[i].num,a[i].money,a[i].name);
						printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n",a[i].topen,a[i].tclose,a[i].n);
						printf("\t公交路线:(1) %s",a[i].b[0].c);
						for(j=1;j<a[i].n;j++)
							printf(" ---->(%d) %s",j+1,a[i].b[j].c);
						printf("\n\n");
					}
				}
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
				printf("\t已全部显示完毕!!!\n");
				if(m==0)
					printf("\n\t没有公交车以该站点为起始站台\n");
				break;
			}
		case '3':
			{
				printf("请输入您所要查询的途径站台名称:\n");
				scanf("%s",cc);
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
				for(i=0;*a[i].num!='\0'&&i<N;i++)
					for(k=1;k<a[i].n-1;k++)
						if(strcmp(a[i].b[k].c,cc)==0)
						{
							m=1;
							printf("\n");
							printf("\t路线编号: %-6s\t单程票价: %d 元\t\t司机姓名: %s\n",a[i].num,a[i].money,a[i].name);
							printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n",a[i].topen,a[i].tclose,a[i].n);
							printf("\t公交路线:(1) %s",a[i].b[0].c);
							for(j=1;j<a[i].n;j++)
								printf(" ---->(%d) %s",j+1,a[i].b[j].c);
							printf("\n\n");
						}
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
				printf("\t已全部显示完毕!!!\n");
				if(m==0)
					printf("\n\t没有公交车以该站点为途径站台\n");
				break;
			}
		case '4':
			{
				printf("\n\t\t按回车键返回查询菜单\n");
				fflush(stdin);                           //清除键盘缓冲区
				getchar();
				system("cls");
				return;                            //返回主菜单
			}
		fflush(stdin);                           //清除键盘缓冲区
		getchar();
		system("cls");
		}
	}
	return;
}

void save()         //信息保存函数
{
	FILE *fp=NULL;
	int i;
	if((fp=fopen("bus.txt","w+"))==NULL)            //以读写的方式打开名称为"bus"的文本文件
	{
		printf("文件打开错误!!!\n");
		return;
	}
	fp=fopen("bus.txt","w+");
	for(i=0;*a[i].num!='\0'&&i<N;i++)                   //将内存中的数据输出到磁盘中
		if(fwrite(&a[i],sizeof(struct bus),1,fp)!=1)
			break;
	printf("\n\t保存成功!!!\n");
	fclose(fp);
	return;
}

void mainmeun()  //主菜单
{
	printf("\n\t\t                主菜单");
	printf("\n\t\t****************************************");
	printf("\n\t\t*            1、信息录入               *");
	printf("\n\t\t*            2、信息显示               *");
	printf("\n\t\t*            3、信息修改               *");
	printf("\n\t\t*            4、信息删除               *");
	printf("\n\t\t*            5、信息查询               *");
	printf("\n\t\t*            6、退出系统               *");
	printf("\n\t\t****************************************");
	printf("\n\n\t\t\t请输入您的选择:");
}

//菜单输入检测函数
char Test(char a,char b,char c)
{
	while(a<b||a>c)
	{
		printf("\n\t\t\t输入错误，请重新输入: ");
		fflush(stdin);                           //清除键盘缓冲区
		a=getchar();
	}
	return a;
}

