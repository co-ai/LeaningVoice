/**************************ͷ�ļ�����************************************/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"

/**************************��������************************************/

void init();	                     //��ʼ������
void add();                          //��Ϣ¼�뺯��
void view();                         //��Ϣ��ʾ����
void mod();                          //��Ϣ�޸ĺ���
void modmeun();                      //�޸Ĳ˵�
void modnavimeun();                  //·���޸Ĳ˵�
void del();                          //��Ϣɾ������
void find();                         //��Ϣ��ѯ����
void findmeun();                     //��ѯ�˵�
void findnavi();                     //·�ߵ�����ѯ����
void findnum();                      //·�߱�Ų�ѯ����
void findstameun();                  //վ̨��Ϣ��ѯ�˵�
void findsta();                      //վ̨��Ϣ��ѯ����
void save();                         //��Ϣ���溯��
void mainmeun();                     //���˵�
char Test(char a,char b,char c);     //�˵������⺯��

/**************************�궨������************************************/
#define N 100                    //����������

/**************************�ṹ�嶨��************************************/
struct station                   //;��վ����Ϣ
{
	char c[20];                  //վ������
};

struct bus                       //��������Ϣ
{
	char num[20];                //������·�߱��
	char name[20];               //˾������
	int n;                       //վ̨��Ŀ
	struct station b[12];        //վ̨����
	char topen[20];              //��ʼʱ��
	char tclose[20];             //��ֹʱ��
	int money;                   //Ʊ��
}a[N];


/**************************��������************************************/

int main()
{
	char a;
	init();
	printf("\n\t\tĿǰ����¼��Ĺ�������������Ϊ %d ��\n\n",N);
	printf("\n\t\t����س�������\n");
	fflush(stdin);                           //������̻�����
	while(1)
	{
		system("cls");
		mainmeun();
		a=Test(getchar(),'1','6');      //�˵�������뺯��
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

void init()     //��ʼ������
{
	FILE *fp;                        //�ļ�ָ��
	int i;
	if((fp=fopen("bus.txt","r+"))==NULL)                  //���γ��Դ�"bus.txt"�ı��ļ�
	{
		printf("\n\t\t�ļ���ʧ��\n\n\t\t���ڳ��Դ������ļ�...\n");
		fp=fopen("bus.txt","w");                          //����"bus.txt"�ı��ļ�
		if((fp=fopen("bus.txt","r+"))==NULL)              //�ٴ��ж��Ƿ�򿪳ɹ�
		{
			printf("\t\t�ļ�����ʧ��!!!\n");
			return;
		}
	}
	fp=fopen("bus.txt","r+");
	for(i=0;i<N;i++)                                          //�������е���Ϣ������ڴ���
		if(fread(&a[i],sizeof(struct bus),1,fp)!=1)
			break;
	fclose(fp);
	printf("\n\t\t��ʼ�����!!!\n\n");
	return;
}

void add()     //��Ϣ¼�뺯��
{
	FILE *fp=NULL;                        //�ļ�ָ��
	int i,j;
	char cc[20];
	for(i=0;i<N;i++)
	{
		if(*a[i].num!='\0')
			continue;
		else
		{
			printf("\n��ӵ�%d��������·�߼�¼:\n",i+1);
			printf("\n������·�߱���(3λ���룬��һλΪ��д��ĸ������λΪ����):\n");    //·�߱���
			scanf("%s",cc);
			for(j=0;j<N;j++)                                                           //�����Ƿ��ظ�
				if(strcmp(a[j].num,cc)==0)
				{
					printf("\n������·�߱����ظ������س�������!!!\n");
					fflush(stdin);                           //������̻�����
					getchar();
					system("cls");
					return;
				}
			strcpy(a[i].num,cc);
			printf("\n������˾������: ");                                              //˾������
			scanf("%s",a[i].name);
			printf("\n������;��վ̨����(>=2): ");                                     //վ̨����
			scanf("%d",&a[i].n);
			printf("\n");
			if(a[i].n<2||a[i].n>12)
			{
				while(a[i].n<2||a[i].n>12)
				{
					printf("\nվ̨����Ӧ����(2<=n<=12)������������: ");
					scanf("%d",&a[i].n);
					printf("\n");
				}
			}
			for(j=0;j<a[i].n;j++)
			{
				printf("�������%d��վ̨����: ",j+1);                    //վ̨����
				scanf("%s",a[i].b[j].c);
			}
			printf("\n�Զ����ɹ���·��:(1) %s",a[i].b[0].c);
			for(j=1;j<a[i].n;j++)
			{
				printf(" ----> (%d) %s",j+1,a[i].b[j].c);
			}
			printf("\n\n�����빫��������ʼʱ��(��ʽΪ��ʱ:��): ");       //��ʼʱ��
			scanf("%s",a[i].topen);
			printf("�����빫��������ֹʱ��(��ʽΪ��ʱ:��): ");           //��ֹʱ��
			scanf("%s",a[i].tclose);
			printf("\n�����빫������Ʊ��: ");                            //Ʊ��
			scanf("%d",&a[i].money);
			printf("\n��%d��������·�߼�¼�����ɹ�!!!\n",i+1);
			save();
			printf("\n\t���س�������!!!\n");
			fflush(stdin);                           //������̻�����
			getchar();
			system("cls");
			return;
		}
	}
	if(i==N)
		printf("\n\n\n\t�ռ�����������¼��!!!\n");
	printf("\n\t���س�������!!!\n");
	fflush(stdin);                           //������̻�����
	getchar();
	system("cls");
	return;
}


void view()    //��Ϣ��ʾ����
{
	int i,j,min;
	struct bus t;
	for(i=0;*a[i].num!='\0'&&i<N;i++)               //����·�߱�š���ѡ������
	{
		min=i;
		for(j=i+1;*a[j].num!='\0'&&j<N;j++)
			if(strcmp(a[i].num,a[j].num)>0)
				min=j;
		t=a[i];
		a[i]=a[min];
		a[min]=t;
	}
	printf("\n\n                              ��������Ϣ��");
	printf("\n********************************************************************************\n");
	for(i=0;*a[i].num!='\0'&&i<N;i++)
	{
		printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\t\t˾������: %s\n",a[i].num,a[i].money,a[i].name);
		printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n",a[i].topen,a[i].tclose,a[i].n);
		printf("\t����·��:(1) %s",a[i].b[0].c);
		for(j=1;j<a[i].n;j++)
			printf(" ---->(%d) %s",j+1,a[i].b[j].c);
		printf("\n\n");
	}
	printf("\n********************************************************************************\n");
	printf("\n\t\t��������Ϣ��ʾ���!!!\n");
	printf("\n\t\t����س����������˵�:");
	fflush(stdin);                           //������̻�����
	getchar();
	system("cls");
	return;
}



void mod()                          //��Ϣ�޸ĺ���
{
	int i,j,m=0;
	char t,cc[20],mod[20];
	printf("������Ҫ�޸���Ϣ�Ĺ�����·�߱��:\n");
	scanf("%s",cc);
	for(i=0;*a[i].num!='\0'&&i<N;i++)     //����������Ĺ�����
	{
		if(strcmp(a[i].num,cc)==0)
		{
			m=1;
			printf("\n\n\t\t���ҵ�!!!\n");
			while(1)
			{
				system("cls");
				printf("\n\n                            �����޸ĵĹ�������Ϣ\n");
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
				printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\t\t˾������: %s\n",a[i].num,a[i].money,a[i].name);
				printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n",a[i].topen,a[i].tclose,a[i].n);
				printf("\t����·��:(1) %s",a[i].b[0].c);
				for(j=1;j<a[i].n;j++)
					printf(" ---->(%d) %s",j+1,a[i].b[j].c);
				printf("\n\n");
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
				modmeun();
				fflush(stdin);                           //������̻�����
				t=Test(getchar(),'1','5');      //�˵�������뺯��
				system("cls");
				switch(t)
				{
				case '1':           //�޸�·�߱��
					{
						int k;
						printf("\n�������µĹ��������:");
						scanf("%s",mod);
						for(k=0;*a[k].num!='\0'&&k<N;k++)
						{
							if(strcmp(a[k].num,mod)==0)
							{
								printf("�����б���ظ�,���س����������˵�\n");
								fflush(stdin);                           //������̻�����
								getchar();
								system("cls");
								return;
							}
						}
						strcpy(a[i].num,mod);
						save();
						break;
					}
				case '2':           //�޸ĳ�����Ϣ
					{
						printf("\n�������µ�˾������:");
						scanf("%s",a[i].name);
						printf("\n�������µĹ�����Ʊ��:");
						scanf("%d",&a[i].money);
						save();
						break;
					}
				case '3':           //�޸��г�·��
					{
						void modnavimeun(); //·���޸Ĳ˵�
						int k;
						char z;
						while(1)
						{
							system("cls");
							modnavimeun();
							fflush(stdin);                           //������̻�����
							z=Test(getchar(),'1','5');      //�˵�������뺯��
							system("cls");
							switch(z)
							{
							case '1':     //���վ��
								{
									if(a[i].n+1>12)             //�ж��Ƿ���������
									{
										printf("\nվ̨�����ﵽ12�����޷������վ��\n\n���س�������\n");
										fflush(stdin);                           //������̻�����
										getchar();
										system("cls");
										return;
									}
									printf("\n��������Ҫ��ӵڼ���վ�㣺");
									scanf("%d",&k);
									while(a[i].n+1<k)
									{
										printf("Ŀǰ��%d��վ�㣬�޷���ӵ�%d��վ��\n���������룺",a[i].n,k);
										scanf("%d",&k);
										printf("\n");
									}
									a[i].n=a[i].n+1;
									for(j=a[i].n;j>k-1;j--)
									{
											a[i].b[j]=a[i].b[j-1];
									}
									printf("\n����������ӵ�վ�����ƣ�");
									scanf("%s",a[i].b[k-1].c);
									save();
									break;
								}
							case '2':     //�޸�վ��
								{
									printf("\n��������Ҫ�޸ĵڼ���վ�㣺");
									scanf("%d",&k);
									printf("\n�������µ�վ�����ƣ�");
									scanf("%s",a[i].b[k-1].c);
									save();
									break;
								}
							case '3':     //ɾ��վ��
								{
									printf("\n��������Ҫɾ���ڼ���վ�㣺");
									scanf("%d",&k);
									for(j=k-1;j<a[i].n;j++)
									{
										a[i].b[j]=a[i].b[j+1];
									}
									a[i].n=a[i].n-1;
									save();
									break;
								}
							case '4':     //����·��
								{
									printf("\n�������µ�;��վ̨����(2<=n<=12): ");
									scanf("%d",&a[i].n);
									printf("\n");
									while(a[i].n<2||a[i].n>12)             //�ж��Ƿ���������
									{
										printf("\nվ̨����Ӧ����(2<=n<=12)������������: ");
										scanf("%d",&a[i].n);
										printf("\n");
									}
									for(j=0;j<a[i].n;j++)
									{
										printf("�������µĵ�%d��վ̨����: ",j+1);
										scanf("%s",a[i].b[j].c);
									}
									printf("\t����·��:(1) %s",a[i].b[0].c);
									for(j=1;j<a[i].n;j++)
										printf(" ---->(%d) %s",j+1,a[i].b[j].c);
									printf("\n\n");
									save();
									break;
								}
							case '5':     //���ز˵�
								{
									printf("\n\t\t���س������ز˵�\n");
									fflush(stdin);                           //������̻�����
									getchar();
									system("cls");
									return;                            //�������˵�
								}
							}
						}
					}
				case '4':           //�޸��г�ʱ��
					{
						printf("\n\n�����빫��������ʼʱ��(��ʽΪ��ʱ:��): ");
						scanf("%s",a[i].topen);
						printf("�����빫��������ֹʱ��(��ʽΪ��ʱ:��): ");
						scanf("%s",a[i].tclose);
						save();
						break;
					}
				case '5':
					{
						printf("\n\t\t���س����������˵�\n");
						fflush(stdin);                           //������̻�����
						getchar();
						system("cls");
						return;                            //�������˵�
					}
				}
			}
		}
	}
	if(m==0)
		printf("\n\n\t\t�޴˹�������Ϣ!!!\n");
	printf("\n\t\t���س�������\n");
	fflush(stdin);                           //������̻�����
	getchar();
	system("cls");
	return;
}



void modmeun()  //�޸Ĳ˵�
{
	printf("\n\t\t                 �޸Ĳ˵�                   ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1���޸�·�߱��               *");
	printf("\n\t\t*            2���޸ĳ�����Ϣ               *");
	printf("\n\t\t*            3���޸��г�·��               *");
	printf("\n\t\t*            4���޸��г�ʱ��               *");
	printf("\n\t\t*            5�����ص����˵�               *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t����������ѡ��:");
}


void modnavimeun() //·���޸Ĳ˵�
{
	printf("\n\t\t               ·���޸Ĳ˵�                 ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1�� վ �� �� ��               *");
	printf("\n\t\t*            2�� վ �� �� ��               *");
	printf("\n\t\t*            3�� վ �� ɾ ��               *");
	printf("\n\t\t*            4�� · �� �� ��               *");
	printf("\n\t\t*            5�� �� �� �� ��               *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t����������ѡ��:");
}


void del()       //��Ϣɾ������
{
	int i,j,t,m=0;
	char cc[20];
	printf("\n������Ҫɾ����Ϣ�Ĺ�����·�߱��:\n");
	scanf("%s",cc);
	for(i=0;*a[i].num!='\0'&&i<N;i++)     //����������Ĺ�����
	{
		if(strcmp(a[i].num,cc)==0)
		{
			m=1;
			printf("\n���ҵ�:\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
			printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\t\t˾������: %s\n",a[i].num,a[i].money,a[i].name);
			printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n",a[i].topen,a[i].tclose,a[i].n);
			printf("\t����·��:(1) %s",a[i].b[0].c);
			for(j=1;j<a[i].n;j++)
				printf(" ---->(%d) %s",j+1,a[i].b[j].c);
			printf("\n\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
			printf("����ɾ���ù�������Ϣ!!!\nȷ���밴1��");
			scanf("%d",&t);
			if(t==1)
			{
				if(i+1==N)
					memset(&a[i],'\0',sizeof(struct bus));      //���һ��ֱ�ӽ������
				else
					for(j=i;*a[j].num!='\0'&&j+1<N;j++)         //����Ĺ�������Ϣ����ɾȥ�Ĺ��ҳ���Ϣ
						a[j]=a[j+1];
				printf("���Ϊ%s�Ĺ�������Ϣɾ�����!\n",cc);
				save();
				break;
			}
		}
	}
	if(m==0)
		printf("\n\n\t\t�޴˹�������Ϣ!!!\n");
	printf("\n\n\t����س����������˵�:");
	fflush(stdin);                           //������̻�����
	getchar();
	system("cls");
	return;
}


void find()    //��Ϣ��ѯ����
{
	char t;
	while(1)
	{
		findmeun();
		fflush(stdin);                           //������̻�����
		t=Test(getchar(),'1','4');      //�˵�������뺯��
		switch(t)
		{
		case '1': system("cls"); findnavi();break;         //·�ߵ�����ѯ
		case '2': system("cls"); findnum();break;          //·�߱�Ų�ѯ����
		case '3': system("cls"); findsta();break;          //վ̨��Ϣ��ѯ����
		case '4': system("cls"); return;                    //�������˵�
		}
	}
	return;
}


void findmeun()  //��ѯ�˵�
{
	printf("\n\t\t                 ��ѯ�˵�                   ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1��·�ߵ�����ѯ               *");
	printf("\n\t\t*            2��·�߱�Ų�ѯ               *");
	printf("\n\t\t*            3��վ̨��Ϣ��ѯ               *");
	printf("\n\t\t*            4�����ص����˵�               *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t����������ѡ��:");
}


void findnavi()        //·�ߵ�����ѯ����
{
	int i,j,k,m=0;
	char c1[20],c2[20];
	printf("��������Ŀǰ���ڵ�վ��:\n\t\t");
	scanf("%s",c1);
	printf("����������Ҫǰ����վ��:\n\t\t");
	scanf("%s",c2);
	printf("\n\n����ѡ��Ĺ�������Ϣ����\n");
	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
	for(i=0;*a[i].num!='\0'&&i<N;i++)
	{
		for(j=0;j<a[i].n;j++)
			for(k=j+1;k<a[i].n;k++)
				if(strcmp(a[i].b[j].c,c1)==0&&strcmp(a[i].b[k].c,c2)==0)
				{
					m=1;
					printf("\n");
					printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\t\t˾������: %s\n",a[i].num,a[i].money,a[i].name);
					printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n",a[i].topen,a[i].tclose,a[i].n);
					printf("\t����·��:(1) %s",a[i].b[0].c);
					for(j=1;j<a[i].n;j++)
						printf(" ---->(%d) %s",j+1,a[i].b[j].c);
					printf("\n\n");
				}
	}
	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
	printf("\t\t\t\t��ʾ���\n");
	if(m==0)
		printf("\n\n\t\t\t\t��Ǹ,��;����·�ߵĹ�����\n");
	printf("\n\t\t\t\t����س������ز�ѯ�˵�:");
	fflush(stdin);                           //������̻�����
	getchar();
	system("cls");
	return;
}


void findnum()           //·�߱�Ų�ѯ����
{
	int i,j,m=0;
	char cc[20];
	printf("����������Ҫ���ҵĹ���·�߱��:\n");
	scanf("%s",cc);
	for(i=0;*a[i].num!='\0'&&i<N;i++)
	{
		if(strcmp(a[i].num,cc)==0)
		{
			m=1;
			printf("\n���ҵ�:\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
			printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\t\t˾������: %s\n",a[i].num,a[i].money,a[i].name);
			printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n",a[i].topen,a[i].tclose,a[i].n);
			printf("\t����·��:(1) %s",a[i].b[0].c);
			for(j=1;j<a[i].n;j++)
				printf(" ---->(%d) %s",j+1,a[i].b[j].c);
			printf("\n\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
			break;
		}
	}
	if(m==0)
		printf("\n\t\t�޴˹�������Ϣ\n");
	printf("\n\t\t����س������ز�ѯ�˵�:");
	fflush(stdin);                           //������̻�����
	getchar();
	system("cls");
	return;
}


 void findstameun()  //վ̨��Ϣ��ѯ�˵�
{
	printf("\n\t\t             վ̨��Ϣ��ѯ�˵�");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1����ʼվ̨��ѯ               *");
	printf("\n\t\t*            2����ֹվ̨��ѯ               *");
	printf("\n\t\t*            3��;��վ̨��ѯ               *");
	printf("\n\t\t*            4�����ز�ѯ�˵�               *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t����������ѡ��:");
}


void findsta()       //վ̨��Ϣ��ѯ����
{
	int i,j,k;
	char t;
	char cc[20];
	while(1)
	{
		int m=0;
		findstameun();
		fflush(stdin);                           //������̻�����
		t=Test(getchar(),'1','4');      //�˵�������뺯��
		system("cls");
		switch(t)
		{
		case '1':
			{
				printf("����������Ҫ��ѯ����ʼվ̨����:\n");
				scanf("%s",cc);
				printf("\n��%sΪ��ʼվ̨�Ĺ���������:\n",cc);
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
				for(i=0;*a[i].num!='\0'&&i<N;i++)
				{
					if(strcmp(a[i].b[0].c,cc)==0)
					{
						m=1;
						printf("\n");
						printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\t\t˾������: %s\n",a[i].num,a[i].money,a[i].name);
						printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n",a[i].topen,a[i].tclose,a[i].n);
						printf("\t����·��:(1) %s",a[i].b[0].c);
						for(j=1;j<a[i].n;j++)
							printf(" ---->(%d) %s",j+1,a[i].b[j].c);
						printf("\n\n");
					}
				}
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
				printf("\t��ȫ����ʾ���!!!\n");
				if(m==0)
					printf("\n\tû�й������Ը�վ��Ϊ��ʼվ̨\n");
				break;
			}
		case '2':
			{
				printf("����������Ҫ��ѯ����ֹվ̨����:\n");
				scanf("%s",cc);
				printf("\n��%sΪ��ֹվ̨�Ĺ���������:\n",cc);
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
				for(i=0;*a[i].num!='\0'&&i<N;i++)
				{
					k=a[i].n;
					if(strcmp(a[i].b[k-1].c,cc)==0)
					{
						m=1;
						printf("\n");
						printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\t\t˾������: %s\n",a[i].num,a[i].money,a[i].name);
						printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n",a[i].topen,a[i].tclose,a[i].n);
						printf("\t����·��:(1) %s",a[i].b[0].c);
						for(j=1;j<a[i].n;j++)
							printf(" ---->(%d) %s",j+1,a[i].b[j].c);
						printf("\n\n");
					}
				}
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
				printf("\t��ȫ����ʾ���!!!\n");
				if(m==0)
					printf("\n\tû�й������Ը�վ��Ϊ��ʼվ̨\n");
				break;
			}
		case '3':
			{
				printf("����������Ҫ��ѯ��;��վ̨����:\n");
				scanf("%s",cc);
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
				for(i=0;*a[i].num!='\0'&&i<N;i++)
					for(k=1;k<a[i].n-1;k++)
						if(strcmp(a[i].b[k].c,cc)==0)
						{
							m=1;
							printf("\n");
							printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\t\t˾������: %s\n",a[i].num,a[i].money,a[i].name);
							printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n",a[i].topen,a[i].tclose,a[i].n);
							printf("\t����·��:(1) %s",a[i].b[0].c);
							for(j=1;j<a[i].n;j++)
								printf(" ---->(%d) %s",j+1,a[i].b[j].c);
							printf("\n\n");
						}
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
				printf("\t��ȫ����ʾ���!!!\n");
				if(m==0)
					printf("\n\tû�й������Ը�վ��Ϊ;��վ̨\n");
				break;
			}
		case '4':
			{
				printf("\n\t\t���س������ز�ѯ�˵�\n");
				fflush(stdin);                           //������̻�����
				getchar();
				system("cls");
				return;                            //�������˵�
			}
		fflush(stdin);                           //������̻�����
		getchar();
		system("cls");
		}
	}
	return;
}

void save()         //��Ϣ���溯��
{
	FILE *fp=NULL;
	int i;
	if((fp=fopen("bus.txt","w+"))==NULL)            //�Զ�д�ķ�ʽ������Ϊ"bus"���ı��ļ�
	{
		printf("�ļ��򿪴���!!!\n");
		return;
	}
	fp=fopen("bus.txt","w+");
	for(i=0;*a[i].num!='\0'&&i<N;i++)                   //���ڴ��е����������������
		if(fwrite(&a[i],sizeof(struct bus),1,fp)!=1)
			break;
	printf("\n\t����ɹ�!!!\n");
	fclose(fp);
	return;
}

void mainmeun()  //���˵�
{
	printf("\n\t\t                ���˵�");
	printf("\n\t\t****************************************");
	printf("\n\t\t*            1����Ϣ¼��               *");
	printf("\n\t\t*            2����Ϣ��ʾ               *");
	printf("\n\t\t*            3����Ϣ�޸�               *");
	printf("\n\t\t*            4����Ϣɾ��               *");
	printf("\n\t\t*            5����Ϣ��ѯ               *");
	printf("\n\t\t*            6���˳�ϵͳ               *");
	printf("\n\t\t****************************************");
	printf("\n\n\t\t\t����������ѡ��:");
}

//�˵������⺯��
char Test(char a,char b,char c)
{
	while(a<b||a>c)
	{
		printf("\n\t\t\t�����������������: ");
		fflush(stdin);                           //������̻�����
		a=getchar();
	}
	return a;
}

