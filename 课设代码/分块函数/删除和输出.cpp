#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���ݽڵ�ṹ
typedef struct _node {
	char *Data; //�ַ���
	int da_lg;  //�ַ�������
	struct _node *next;     //��һ���ڵ�λ��
	struct _node *last;     //��һ���ڵ�λ��
}sjjd, *Sjjd;       //���ݽڵ�ṹ

//�������ݱ���
typedef struct _find_data {
	int num;    //���ֱ��
	int jd_num; //�ڵ���
	Sjjd sjjd_last; //��һ�����ݽڵ��ַ
	Sjjd sjjd_next; //��һ�����ݽڵ��ַ
	struct _find_data *fd_next; //��һ���������ݽڵ�λ��
}find_data, *Find_data;

//�нڵ�
typedef struct line{
	
};

void wenbenbj_1(char *fname);   //�ı��༭һ��
void wenbencj_2(char *fname);   //�ı�����һ��
void theme_3(void);             //����ѡ��һ��
void bi_ji(FILE *fp, char fname[100]);  //�༭�ı�����  ��
void ch_ji(FILE *fp);                   //�����ı�����
char *cat_out_filename(char *fname);        //��ȡ�ļ���
int pdzfc(char fp);                         //�ж��ַ������  ��
void sclb(Sjjd head, char fname[100]);       //�����������
Find_data find(Sjjd head, char *str); //ϸ���Ĳ��ҹ���ģ��  ��˼��
void dest_fd(Find_data head_fd);            //�ͷŲ��ҽ��������  ��˼��
void Find(Sjjd head);                            //�ַ�������  ��˼��
Sjjd str_ins(Sjjd head, char *fname);               //�ַ�������
Sjjd str_del(Sjjd head, char *fname);               //�ַ���ɾ��
Sjjd str_rep(Sjjd head, char *fname);               //�ַ����滻
void qut_n_save(Sjjd head, FILE *fp);               //�˳�������
void qut_y_save(Sjjd head, FILE *fp, char *fname);  //�˳�������

/*
�������Ĺ���:
1.������˵�����ѡ�����
2.��һ�β�������������������һ�β���,�������˵������˳�
*/
int main()
{
	char fname[200], temp, choice_next;		//fname[]�����н����ļ���·��,temp���ڻ�ȡ�ַ�,��������
	int choice_this;        //��ǰ��������һ������
	system("title Text Editor");
	do
	{
		printf("*********************************************�ı��༭��*********************************************\n");
		printf("1.���ļ�\t");
		printf("2.�����ļ�\t");
		printf("3.�˳�����\n");
		printf("��������Ĳ���(1~3):");
		while (1)
		{
			scanf("%d", &choice_this);
			while
				((temp = getchar()) != EOF && temp != '\n');       //���������
			if (choice_this < 1 || choice_this > 3)
				printf("������1~3֮�������!\n");
			else
				break;
		}
		switch (choice_this)
		{
		case 1: wenbenbj_1(fname);
		case 2: wenbencj_2(fname);
		case 3: printf("��лʹ��\n"); return 0;
			/*printf("�˳�ǰ�Ƿ񱣴�?(y/n)\n:");
			scanf("%c", &choice_quit);
			while ((temp = getchar()) != EOF && temp != '\n');
				if(choice_quit == 'y')
					qut_y_save(Sjjd head, FILE *fp, char *fname);*/
		}
		printf("�Ƿ����ѡ�����?(y\n):  ");
		scanf("%c", &choice_next);
		while ((temp = getchar()) != EOF && temp != '\n');
		if (choice_next == 'y')		//������һ��ѭ��
		{
			system("cls");
		}
		else if (choice_next == 'n')	//����ѭ��,ִ��return 0;
		{
			break;
		}
	} while (true);
	return 0;
}
//����������
//����������ģ��-һ��
void wenbenbj_1(char *fname)    //�ı��༭-һ��
{
	char tmp;   //����������
	FILE *fp;

	printf("������Ҫ�򿪵��ļ�λ�ü����֣�������100���ַ���\n");
	scanf("%s", fname);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
	while ((fp = fopen(fname, "r")) == NULL)
	{
		printf("���ļ�ʧ�ܣ�ʧ��ԭ�����Ϊ��\n");
		printf("1���ļ�������\n2��·������\n3��Ȩ�޴���\n");
		printf("��������������ļ�λ�ü�����\n");
		scanf("%s", fname);
		while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
	}
	system("cls");  //����
	bi_ji(fp, fname);       //���ñ༭�ı�����
}
void wenbencj_2(char *fname)    //�ı�����-һ��
{
	char tmp;   //����������
	FILE *fp;

	printf("������Ҫ�������ļ�λ�ü�����(������100���ַ�)\n");
	scanf("%s", fname);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
	while ((fp = fopen(fname, "w+")) == NULL)
	{
		printf("�����ļ�ʧ�ܣ�ʧ��ԭ�����Ϊ��\n");
		printf("1��·������\n2��Ȩ�޴���\n");
		printf("��������������ļ�λ�ü�����\n");
		scanf("%s", fname);
		while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
	}
	system("cls");
	printf("�ļ���%s���ѳɹ�������\n", fname);
	ch_ji(fp);  //���ô����ı�����
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
}
//�ı��༭����-�������忪ʼ
//�༭�ı�������ʼ
void bi_ji(FILE *fp, char fname[100])   //���ļ��������ַ����浽�ṹ������
{
	char str[30], *arr, ch; 	//arr�ַ����������ý��,ch�����ж�
	char save, tmp;        		//���桢�Իس�
	int i, lg, choice, cancle; //���Ʊ������ڵ����ݳ��ȡ�����ѡ��
	Sjjd head, pointer, p;
	head = pointer = NULL;

	while (1)
	{
		i = 0;
		ch = fgetc(fp), fseek(fp, -1L, SEEK_CUR);	//�ļ��ַ�ָ�����
		if (ch == EOF)
			break;
		if (pdzfc(ch) == 0) 	//���������[��Ӣ����ĸ]
		{
			str[i] = fgetc(fp), str[1] = '\0';		//�ļ��ַ�ָ��ָ����һ���ַ�
			arr = (char *)malloc(2), strcpy(arr, str);//һ�����ռһ���ֽ�,��'\0'һ�������ֽ�

			if (head == NULL)   //����Ϊ��
			{
				head = pointer = (Sjjd)malloc(sizeof(sjjd));    //����ͷ�ڵ�͵�һ���ڵ�
				pointer->Data = arr, pointer->da_lg = (*arr == '\t') ? 8 : 1, pointer->next = pointer->last = NULL;
			}       //ÿ������ռһ���ֽ�,�Ʊ��ռ8���ֽ�
			else
			{
				p = (Sjjd)malloc(sizeof(sjjd));
				p->Data = arr, p->da_lg = (*arr == '\t') ? 8 : 1, p->next = NULL;
				pointer->next = p, p->last = pointer;
				pointer = p;
			}
		}
		else       //һ������
		{
			i = 0;
			while (pdzfc(ch))		//whileѭ����Ӣ����ĸ���������У�ֱ���������š�
			{
				str[i] = fgetc(fp);		//��ǰ��ĸ��������
				ch = fgetc(fp), fseek(fp, -1L, SEEK_CUR);		//��ch��ʱ�洢��һ���ַ����ļ��ַ�ָ�����
				i++;
			}
			str[i] = '\0';		// '\0'�����ַ����顾һ�����ʡ�
			lg = (int)strlen(str);		//���Ȳ�����'\0'
			arr = (char *)malloc(lg + 1), strcpy(arr, str);     //����

			if (head == NULL)
			{
				head = pointer = (Sjjd)malloc(sizeof(sjjd));
				pointer->Data = arr, pointer->da_lg = lg, pointer->next = pointer->last = NULL;
			}
			else
			{
				p = (Sjjd)malloc(sizeof(sjjd));
				p->Data = arr, p->da_lg = lg, p->next = NULL;
				pointer->next = p, p->last = pointer;
				pointer = p;
			}
			if (ch == EOF)      //�ų������һ�����ʽ������ļ�
				break;
		}
	} //��ȡ�ı����ݵ������н���
	if (head == NULL)   //���������-��
	{
		printf("�ļ�Ϊ�գ�\n");        //���ļ������ʾ
		fclose(fp);
		qut_y_save(head, fp, fname);
	}
	else
		sclb(head, fname);      //���������-�ǿ�
	//����༭����
	do
	{       //�༭�����˵�
		printf("1������\n");
		printf("2������\n");
		printf("3��ɾ��\n");
		printf("4���滻\n");
		do
		{
			choice = 0;     //����ϴγɹ�ͨ���ж�ʱ������
			scanf("%d", &choice);
			while ((tmp = getchar()) != '\n' && tmp != EOF);
			if (choice < 1 || choice > 4)
				printf("�����������\n");
			else
				break;
		} while (1);

		switch (choice)
		{
		case 1:
			Find(head); break;
		case 2:
			head = str_ins(head, fname); break;
		case 3:
			head = str_del(head, fname); break;
		case 4:
			head = str_rep(head, fname); break;
		}
		printf("�Ƿ��������?y/n\n");
		save = getchar();
		while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
		if (save == 'y')   //��������ǰ��������Ȼ��������ļ�����
		{
			system("cls");  //����
			if (head == NULL)   //���������-��
			{
				printf("�ļ�Ϊ�գ�\n");        //���ļ������ʾ
				qut_y_save(head, fp, fname);
			}
			else
				sclb(head, fname);      //���������-�ǿ�
		}
	} while (save == 'y');
	//�˳�ģʽѡ��
	printf("�Ƿ񽫱������?\n");
	printf("1:������\n");
	printf("2:������\n");
	do
	{
		scanf("%d", &cancle);
		while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
		if (cancle < 1 || cancle > 2)
			printf("û�и�ѡ����������룺\n");
		else
			break;
	} while (1);
	if (cancle == 1)
		qut_n_save(head, fp);   //�˳�������
	else
		qut_y_save(head, fp, fname); //�˳�������
}   //�ı��༭�����������


//�����ı�����-��������
void ch_ji(FILE *fp)
{
	char ch;

	printf("�������ı�����:(�����ԡ�#������)\n");
	do
	{
		ch = getchar();
		if (ch == '#')
			break;
		fputc(ch, fp);
	} while (1);

	if (fclose(fp) == 0)
		printf("�����ѳɹ�д�뵽�ļ��У�\n");
	else
		printf("д�뵽�ļ���ʧ�ܣ�\n");
}

//��������������
//����������ݺ�������
void sclb(Sjjd head, char fname[100])
{
	int toal_jd = 0, line_nm = 1, line_jd = 0, line_bt_num = 0;   //����֮ǰ�ܽڵ�������кţ�����ÿ�н������㣩�����нڵ���������ֽڣ���ÿ�н������㣩
	int i, j, filename_L;
	char *filename;     //�洢�ļ�����������·����
	Sjjd p = head;

	filename = cat_out_filename(fname); //��ȡ�ļ���
	filename_L = (int)strlen(filename); //�����ļ�������

	for (i = 1; i < 60; i++)    //�ļ����ǰ������ʾ
	{
		putchar('*');
		if (i == (59 - filename_L) / 2)
		{
			for (j = 0; j < filename_L; j++)
				putchar(filename[j]);
			i += filename_L;
		}
	}       printf("|");
	printf("toal_jd   line_jd   line_nm\n");    //ÿ����Ϣռ�˸�λ��������Ϣ���Ϊ�����ո�
	do         //�ļ����������ʼ
	{
		if (*(p->Data) != '\n')     //�б��з�"\n"�Ĵ���
		{   //�ǻ��з�����
			if (*(p->Data) == '\t')
			{
				//ˮƽ�Ʊ������ˮƽ�Ʊ����ʽ����������8���ո���棩��Ҳ��Ϊһ���ڵ��ͬ��������ַ�����ͳ�ƴ���
				for (i = 1; i <= 8; i++)        //�ո�������
				{
					putchar(' ');
				}
				toal_jd++, line_jd++, line_bt_num += p->da_lg;
			}
			else
			{   //��ͨ�ַ�����(�ո��������)��ֱ�����
				printf("%s", p->Data), toal_jd++, line_jd++, line_bt_num += p->da_lg;
			}
		}
		else
		{   //���з��������з���ʽ���������Ŀո���棩�����з�Ҳ��Ϊһ���ڵ��ͬ��������ַ�����ͳ�ƴ���
			toal_jd++, line_jd++;
		}

		if (((line_bt_num >= 45 && p->next != NULL) && (p->next->da_lg != 1 || *(p->next->Data) == '\n')) || *(p->Data) == '\n')   //��β����
		{
			for (i = 1; i < 60 - line_bt_num; i++)      //�ո�������
			{
				putchar(' ');
			}       printf("|");
			printf("%-8d  %-8d  %-8d\n", toal_jd - line_jd, line_jd, line_nm);  //ÿ����Ϣռ�˸�λ��������Ϣ���Ϊ�����ո�
			line_nm++, line_jd = 0, line_bt_num = 0;
		}

		if (p->next == NULL)    //��������ж�
		{
			for (i = 1; i < 60 - line_bt_num; i++)      //�ո�������
			{
				putchar(' ');
			}       printf("|");
			printf("%-8d  %-8d  %-6d\n", toal_jd - line_jd, line_jd, line_nm);  //ÿ����Ϣռ�˸�λ��������Ϣ���Ϊ�����ո�
			for (i = 1; i < 60; i++)        //�ļ����������ʾ��
			{
				putchar('*');
				if (i == (59 - 8) / 2)
				{
					printf("FILE-END");
					i += 8;
				}
			}       printf("|%-8d\n", toal_jd);
			break;
		}
		p = p->next;
	} while (1);

}

//�ж��ַ����������
int pdzfc(char ch)
{
	int flag = 0;
	if (ch >= '0' && ch <= '9')
		flag = 1;
	if (ch >= 'a' && ch <= 'z')
		flag = 1;
	if (ch >= 'A' && ch <= 'Z')
		flag = 1;
	return flag;
}

//��ȡ�ļ�����������
char *cat_out_filename(char *fname)
{
	static char filename[50];

	if (strrchr(fname, '\\') == NULL)
		strcpy(filename, fname);
	else
		strcpy(filename, strrchr(fname, '\\') + 1);     //ָ�������ƶ�һλ��ָ��\\֮���λ��

	return filename;
}

//���Һ���
void Find(Sjjd head)
{
	char str[50], tmp;
	Find_data q, p;
	printf("������Ҫ���ҵ����ݣ�\n");
	scanf("%s", str);
	while ((tmp = getchar()) != '\n' && tmp != EOF);
	if (strcmp(str, "\\t") == 0)
		strcpy(str, "\t");
	if (strcmp(str, "\\n") == 0)
		strcpy(str, "\n");
	if (strcmp(str, "\\s") == 0)
		strcpy(str, " ");

	q = find(head, str);
	dest_fd(q);
}

//ϸ���Ĳ��ҹ���ģ�鿪ʼ
Find_data find(Sjjd head, char *str)
{
	Sjjd p = head;
	Find_data head1, tail, q;       //������ҽ���������ָ��
	head1 = tail = NULL;               //���ҽ���������ָ���ʼ��
	int total, line, linenumber1, linenumber2, enter, k, flag = 0;    //�������ַ������ļ���λ�ã��ڵ㡢�кš����ֽ������нڵ㡢�س����ֵĽڵ㡢���ִ�����
	k = total = linenumber2 = linenumber1 = 0, line = 1;
    //total�ܽ����,line����,linenumber1,linenumber2��ǰ�нڵ���
	do
	{
		if (*(p->Data) != '\n')     //�б��з�"\n"�Ĵ���
		{   //�ǻ��з�����
			if (*(p->Data) == '\t')
				//ˮƽ�Ʊ������ˮƽ�Ʊ����ʽ����������8���ո���棩��Ҳ��Ϊһ���ڵ��ͬ��������ַ�����ͳ�ƴ���
			{
				total++;
				linenumber2++;
				linenumber1 = linenumber1 + 8;
			}
			else  //��ͨ�ַ�����ֱ�����
			{
				total++;
				linenumber2++;
				linenumber1 = linenumber1 + p->da_lg;
			}
		}
		else    //���з��������з���ʽ���������Ŀո���棩�����з�Ҳ��Ϊһ���ڵ��ͬ��������ַ�����ͳ�ƴ���
		{
			total++;
			linenumber2++;
			enter = linenumber2;
		}

		if (((linenumber1 >= 45 && p->next != NULL) && (p->next->da_lg != 1 || *(p->next->Data) == '\n')) || *(p->Data) == '\n')    //��β����
		{
			line++;
			linenumber1 = 0;
			linenumber2 = 0;
		}

		if (!strcmp(p->Data, str))
		{
			k++;
			if (strcmp(p->Data, "\n") == 0)
				printf("num:%-6d line_nm:%-6d toal_jd:%-6d line_jd:%-6d\n", k, line - 1, total, enter);
			else
				printf("num:%-6d line_nm:%-6d toal_jd:%-6d line_jd:%-6d\n", k, line, total, linenumber2);
			q = (Find_data)malloc(sizeof(find_data));
			q->sjjd_next = p->next, q->sjjd_last = p->last, q->num = k, q->jd_num = total, q->fd_next = NULL;
			if (head1 == NULL)
				head1 = tail = q;
			else
				tail->fd_next = q;    tail = q;
			flag = 1;
		}
		if (p->next == NULL)
			break;
		else
			p = p->next;
	} while (1);

	if (flag == 0)
	{
		printf("����ʧ�ܣ����ַ��������ڣ�\n");
	}

	return head1;
}   //ϸ���Ĳ���ģ�����

//�ַ������뺯�����忪ʼ
Sjjd str_ins(Sjjd head, char *fname)
{
	char str[50], tmp;      //�������ַ���ʱ���λ�á�������뻺������
	Sjjd p = head, p1;      //p��ʼ��ָ��ͷָ��
	int toal_jd, i;         //�������λ�á����Ʊ���

	printf("���������ĵ����ַ����������λ��(<=1���ڵ�һλ��>β�ڵ�������)��");
	scanf("%s %d", str, &toal_jd);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
	if (strcmp(str, "\\t") == 0)    //���Ʊ�����д���
		strcpy(str, "\t");
	else if (strcmp(str, "\\n") == 0)   //�Իس����д���
		strcpy(str, "\n");
	else if (strcmp(str, "\\s") == 0)   //�Կո���д���
		strcpy(str, " ");

	for (i = 1; i < toal_jd && p->next != NULL; i++, p = p->next);  //�ƶ�λ��ָ��λ��ָ�뵽����λ��(ֻҪ����Ľڵ��������ܽڵ�������Ϊ�������һ��λ��)

	if (p->last == NULL)        //����λ����ͷ�ڵ�
	{
		p1 = (Sjjd)malloc(sizeof(sjjd));
		p1->Data = strcpy((char *)malloc(strlen(str) + 1), str), p1->da_lg = (*str == '\t' ? 8 : strlen(str));
		p1->last = NULL, p1->next = p;
		head = p->last = p1;
	}
	else if (p->next == NULL && i < toal_jd)    //����λ����β�ڵ�
	{
		p1 = (Sjjd)malloc(sizeof(sjjd));
		p1->Data = strcpy((char *)malloc(strlen(str) + 1), str), p1->da_lg = (*str == '\t' ? 8 : strlen(str));
		p1->next = NULL, p1->last = p;
		p->next = p1;
	}
	else     //����λ�����м�
	{
		p1 = (Sjjd)malloc(sizeof(sjjd));
		p1->Data = strcpy((char *)malloc(strlen(str) + 1), str), p1->da_lg = (*str == '\t' ? 8 : strlen(str));
		p->last->next = p1, p1->last = p->last, p1->next = p, p->last = p1;
	}
	system("cls");  //����
	printf("�������ļ��������£�\n");
	sclb(head, fname);

	return head;
}//�ַ������뺯���������

//�ַ���ɾ���������忪ʼ
Sjjd str_del(Sjjd head, char *fname)
{
	char str[50], tmp;      //��ɾ���ַ����������������
	Find_data head_fd, p_fd;    //������ҽ���������ָ��
	int choice, i;

	printf("������Ҫɾ�����ַ�����");
	scanf("%s", str);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
	if (strcmp(str, "\\t") == 0)    //���Ʊ�����д���
		strcpy(str, "\t");
	else if (strcmp(str, "\\n") == 0)   //�Իس����д���
		strcpy(str, "\n");
	else if (strcmp(str, "\\s") == 0)   //�Կո���д���
		strcpy(str, " ");

	p_fd = head_fd = find(head, str);     //���ò��Һ������Ҷ�Ӧ����
	if (head_fd == NULL)    //Ҫɾ�����ַ��������ڴ���
		goto end;
	printf("��ѡ��ɾ�����󣨡�0����ʾɾ��ȫ�����ҵ��Ķ���ѡ��ɾ��ʱÿ��ֻ��ɾ��һ��������\n");
re: scanf("%d", &choice);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
	if (choice < 0)     //�޶�����Ķ���ֻ��Ϊ>=0����
	{
		printf("���������������������룺");
		goto re;
	}
	p_fd = head_fd;     //goto�ļ���ʹ��Ҫ��Ӹ����
	if (choice == 0)    //���ҵ�����ȫ��ɾ��
	{
		do
		{   //ɾ��������ʼ
			if (p_fd->sjjd_last == NULL)    //ͷ�ڵ��ɾ��
			{
				free(p_fd->sjjd_next->last->Data);  //�ͷŸýڵ��ŵ��ַ����ռ�
				free(p_fd->sjjd_next->last);        //�ͷŸýڵ���ռ�ڴ�ռ�
				head = p_fd->sjjd_next; //ͷ�������һλ
				head->last = NULL;
			}
			else if (p_fd->sjjd_next == NULL)   //β�ڵ��ɾ��
			{
				free(p_fd->sjjd_last->next->Data);  //�ͷŸýڵ��ŵ��ַ����ռ�
				free(p_fd->sjjd_last->next);    //�ͷŸýڵ���ռ�ڴ�ռ�
				p_fd->sjjd_last->next = NULL;
			}
			else     //�м�ڵ��ɾ��
			{
				free(p_fd->sjjd_next->last->Data);
				free(p_fd->sjjd_next->last);
				p_fd->sjjd_last->next = p_fd->sjjd_next;    //��һ���ڵ��next������һ���ڵ�����
				p_fd->sjjd_next->last = p_fd->sjjd_last;    //��һ���ڵ��last������һ���ڵ�����
			}
			if (p_fd->fd_next == NULL)
				break;
			p_fd = p_fd->fd_next;
		} while (1);
	}
	else    //ɾ��ָ���Ĳ�������
	{
		for (i = 1; i < choice; p_fd = p_fd->fd_next, i++)      //�ƶ���Ҫɾ���Ľڵ�
		{
			if (p_fd->fd_next == NULL)      //�������ų������ҵ��ĸ���
			{
				printf("�����������������������룡");
				goto re;
			}
		}
		//ɾ��������ʼ
		if (p_fd->sjjd_last == NULL)    //ͷ�ڵ��ɾ��
		{
			free(p_fd->sjjd_next->last->Data);  //�ͷŸýڵ��ŵ��ַ����ռ�
			free(p_fd->sjjd_next->last);        //�ͷŸýڵ���ռ�ڴ�ռ�
			head = p_fd->sjjd_next; //ͷ�������һλ
			head->last = NULL;
		}
		else if (p_fd->sjjd_next == NULL)   //β�ڵ��ɾ��
		{
			free(p_fd->sjjd_last->next->Data);  //�ͷŸýڵ��ŵ��ַ����ռ�
			free(p_fd->sjjd_last->next);    //�ͷŸýڵ���ռ�ڴ�ռ�
			p_fd->sjjd_last->next = NULL;
		}
		else     //�м�ڵ��ɾ��
		{
			free(p_fd->sjjd_next->last->Data);
			free(p_fd->sjjd_next->last);
			p_fd->sjjd_last->next = p_fd->sjjd_next;    //��һ���ڵ��next������һ���ڵ�����
			p_fd->sjjd_next->last = p_fd->sjjd_last;    //��һ���ڵ��last������һ���ڵ�����
		}
	}
	dest_fd(head_fd);   //�ͷŲ�������ռ�
	system("cls");      //����
	printf("ɾ��������ɣ�ɾ������������£�\n");
	sclb(head, fname);

end:    return head;
}//�ַ���ɾ�������������

//�ַ����滻�������忪ʼ
Sjjd str_rep(Sjjd head, char *fname)
{
	char str[50], str_tar[50], tmp;       //���滻�ַ����������������
	Find_data head_fd, p_fd, p1;    //������ҽ���������ָ��
	int choice, i;

	printf("�����뱻�滻���ַ������滻����ַ���:");
	scanf("%s %s", str, str_tar);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
	//str�Ĵ���
	if (strcmp(str, "\\t") == 0)    //���Ʊ�����д���
		strcpy(str, "\t");
	else if (strcmp(str, "\\n") == 0)   //�Իس����д���
		strcpy(str, "\n");
	else if (strcmp(str, "\\s") == 0)   //�Կո���д���
		strcpy(str, " ");
	//str_tar�Ĵ���
	if (strcmp(str_tar, "\\t") == 0)    //���Ʊ�����д���
		strcpy(str_tar, "\t");
	else if (strcmp(str_tar, "\\n") == 0)   //�Իس����д���
		strcpy(str_tar, "\n");
	else if (strcmp(str_tar, "\\s") == 0)   //�Կո���д���
		strcpy(str_tar, " ");

	p_fd = head_fd = find(head, str);     //���ò��Һ������Ҷ�Ӧ����
	if (head_fd == NULL)    //���滻�ַ������ڵĴ���
		goto end;
	printf("��ѡ���滻���󣨡�0����ʾ�滻ȫ�����ҵ��Ķ���ѡ���滻ʱÿ��ֻ���滻һ��������\n");
re: scanf("%d", &choice);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
	if (choice < 0)     //�޶�����Ķ���ֻ��Ϊ>=0����
	{
		printf("���������������������룺");
		goto re;
	}
	p_fd = head_fd;     //goto�ļ���ʹ��Ҫ��Ӹ����
	if (choice == 0)    //���ҵ�����ȫ���滻
	{
		do
		{   //�滻������ʼ
			if (p_fd->sjjd_last == NULL)    //ͷ�ڵ���滻
			{
				free(p_fd->sjjd_next->last->Data);  //�ͷŸýڵ��ŵ��ַ����ռ�
				p_fd->sjjd_next->last->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //�滻
				p_fd->sjjd_next->last->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //�滻������ݳ���
			}
			else if (p_fd->sjjd_next == NULL)   //β�ڵ���滻
			{
				free(p_fd->sjjd_last->next->Data);  //�ͷŸýڵ��ŵ��ַ����ռ�
				p_fd->sjjd_last->next->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //�滻
				p_fd->sjjd_last->next->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //�滻������ݳ���
			}
			else     //�м�ڵ���滻
			{
				free(p_fd->sjjd_next->last->Data);  //�ͷŸýڵ��ŵ��ַ����ռ�
				p_fd->sjjd_next->last->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //�滻
				p_fd->sjjd_next->last->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //�滻������ݳ���
			}
			if (p_fd->fd_next == NULL)
				break;
			p_fd = p_fd->fd_next;
		} while (1);
	}
	else    //�滻ָ���Ĳ�������
	{
		for (i = 1; i < choice; p_fd = p_fd->fd_next, i++)      //�ƶ���Ҫɾ���Ľڵ�
		{
			if (p_fd->fd_next == NULL)      //�������ų������ҵ��ĸ���
			{
				printf("�����������������������룡");
				goto re;
			}
		}
		//�滻������ʼ
		if (p_fd->sjjd_last == NULL)    //ͷ�ڵ���滻
		{
			free(p_fd->sjjd_next->last->Data);  //�ͷŸýڵ��ŵ��ַ����ռ�
			p_fd->sjjd_next->last->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //�滻
			p_fd->sjjd_next->last->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //�滻������ݳ���
		}
		else if (p_fd->sjjd_next == NULL)   //β�ڵ���滻
		{
			free(p_fd->sjjd_last->next->Data);  //�ͷŸýڵ��ŵ��ַ����ռ�
			p_fd->sjjd_last->next->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //�滻
			p_fd->sjjd_last->next->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //�滻������ݳ���
		}
		else     //�м�ڵ���滻
		{
			free(p_fd->sjjd_next->last->Data);  //�ͷŸýڵ��ŵ��ַ����ռ�
			p_fd->sjjd_next->last->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //�滻
			p_fd->sjjd_next->last->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //�滻������ݳ���
		}
	}
	dest_fd(head_fd);   //�ͷŲ�������ռ�
	system("cls");      //����
	printf("�滻������ɣ��滻����������£�\n");
	sclb(head, fname);

end:    return head;
}//�ַ����滻�����������

//�˳��༭ģʽ�����溯�����忪ʼ
void qut_n_save(Sjjd head, FILE *fp)
{
	Sjjd p1, p2 = p1 = head;
	//��������
	while (p1->next != NULL)
	{
		free(p1->Data);
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	if (fclose(fp) == 0)
		printf("�����ɹ����ѹر��ļ�ָ�롣\n");
	else
		printf("����ʧ�ܣ��ر��ļ�ָ��ʧ�ܡ�\n");
} //�˳��༭ģʽ�����溯���������

//�˳��༭ģʽ�����溯�����忪ʼ
void qut_y_save(Sjjd head, FILE *fp, char *fname)
{
	Sjjd p1, p2 = p1 = head;

	fclose(fp); fp = fopen(fname, "w"); //�ı��ļ������ԣ��л�Ϊд����
	//�������������뵽�ļ���
	do
	{
		fprintf(fp, "%s", p1->Data);
		if (p1->next == NULL)
			break;
		else
			p1 = p1->next;
	} while (1);
	//��������
	p1 = p2;
	while (p1->next != NULL)
	{
		free(p1->Data);
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	if (fclose(fp) == 0)
		printf("�����ɹ����ļ��ѱ��棬�ļ�ָ���ѹرա�\n");
	else
		printf("����ʧ�ܣ��ļ�����ʧ�ܣ��ر��ļ�ָ��ʧ�ܡ�\n");
}//�˳��༭ģʽ�����溯���������


void dest_fd(Find_data head_fd) //�ͷŲ��ҽ��������
{
	Find_data p_fd = head_fd;

	while (head_fd != NULL && head_fd->fd_next != NULL)
	{
		head_fd = head_fd->fd_next;
		free(p_fd);
		p_fd = head_fd;
	}
	free(p_fd);
}

