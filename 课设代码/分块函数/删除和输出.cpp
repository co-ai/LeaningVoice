#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//数据节点结构
typedef struct _node {
	char *Data; //字符串
	int da_lg;  //字符串长度
	struct _node *next;     //下一个节点位置
	struct _node *last;     //上一个节点位置
}sjjd, *Sjjd;       //数据节点结构

//查找数据保存
typedef struct _find_data {
	int num;    //出现编号
	int jd_num; //节点编号
	Sjjd sjjd_last; //上一个数据节点地址
	Sjjd sjjd_next; //下一个数据节点地址
	struct _find_data *fd_next; //下一个查找数据节点位置
}find_data, *Find_data;

//行节点
typedef struct line{
	
};

void wenbenbj_1(char *fname);   //文本编辑一级
void wenbencj_2(char *fname);   //文本创建一级
void theme_3(void);             //主题选择一级
void bi_ji(FILE *fp, char fname[100]);  //编辑文本二级  彭畅
void ch_ji(FILE *fp);                   //创建文本二级
char *cat_out_filename(char *fname);        //截取文件名
int pdzfc(char fp);                         //判断字符类别函数  彭畅
void sclb(Sjjd head, char fname[100]);       //输出链表内容
Find_data find(Sjjd head, char *str); //细化的查找功能模块  陈思雅
void dest_fd(Find_data head_fd);            //释放查找结果链表函数  陈思雅
void Find(Sjjd head);                            //字符串查找  陈思雅
Sjjd str_ins(Sjjd head, char *fname);               //字符串插入
Sjjd str_del(Sjjd head, char *fname);               //字符串删除
Sjjd str_rep(Sjjd head, char *fname);               //字符串替换
void qut_n_save(Sjjd head, FILE *fp);               //退出不保存
void qut_y_save(Sjjd head, FILE *fp, char *fname);  //退出并保存

/*
主函数的功能:
1.输出主菜单并且选择操作
2.第一次操作后清屏并且输入下一次操作,进入主菜单或者退出
*/
int main()
{
	char fname[200], temp, choice_next;		//fname[]数组中接收文件的路径,temp用于获取字符,清理缓存区
	int choice_this;        //当前操作和下一步操作
	system("title Text Editor");
	do
	{
		printf("*********************************************文本编辑器*********************************************\n");
		printf("1.打开文件\t");
		printf("2.创建文件\t");
		printf("3.退出程序\n");
		printf("请输入你的操作(1~3):");
		while (1)
		{
			scanf("%d", &choice_this);
			while
				((temp = getchar()) != EOF && temp != '\n');       //清除缓存区
			if (choice_this < 1 || choice_this > 3)
				printf("请输入1~3之间的数字!\n");
			else
				break;
		}
		switch (choice_this)
		{
		case 1: wenbenbj_1(fname);
		case 2: wenbencj_2(fname);
		case 3: printf("感谢使用\n"); return 0;
			/*printf("退出前是否保存?(y/n)\n:");
			scanf("%c", &choice_quit);
			while ((temp = getchar()) != EOF && temp != '\n');
				if(choice_quit == 'y')
					qut_y_save(Sjjd head, FILE *fp, char *fname);*/
		}
		printf("是否继续选择操作?(y\n):  ");
		scanf("%c", &choice_next);
		while ((temp = getchar()) != EOF && temp != '\n');
		if (choice_next == 'y')		//进入下一个循环
		{
			system("cls");
		}
		else if (choice_next == 'n')	//结束循环,执行return 0;
		{
			break;
		}
	} while (true);
	return 0;
}
//函数定义区
//主函数功能模块-一级
void wenbenbj_1(char *fname)    //文本编辑-一级
{
	char tmp;   //缓冲区清理
	FILE *fp;

	printf("请输入要打开的文件位置及名字（不超过100个字符）\n");
	scanf("%s", fname);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
	while ((fp = fopen(fname, "r")) == NULL)
	{
		printf("打开文件失败！失败原因可能为；\n");
		printf("1：文件名错误\n2：路径错误\n3：权限错误\n");
		printf("请检查后重新输入文件位置及名字\n");
		scanf("%s", fname);
		while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
	}
	system("cls");  //清屏
	bi_ji(fp, fname);       //调用编辑文本函数
}
void wenbencj_2(char *fname)    //文本创建-一级
{
	char tmp;   //缓冲区清理
	FILE *fp;

	printf("请输入要创建的文件位置及名字(不超过100个字符)\n");
	scanf("%s", fname);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
	while ((fp = fopen(fname, "w+")) == NULL)
	{
		printf("创建文件失败！失败原因可能为；\n");
		printf("1：路径错误\n2：权限错误\n");
		printf("请检查后重新输入文件位置及名字\n");
		scanf("%s", fname);
		while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
	}
	system("cls");
	printf("文件“%s”已成功创建！\n", fname);
	ch_ji(fp);  //调用创建文本函数
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
}
//文本编辑函数-二级定义开始
//编辑文本二级开始
void bi_ji(FILE *fp, char fname[100])   //将文件中所有字符保存到结构体链表
{
	char str[30], *arr, ch; 	//arr字符传入链表的媒介,ch符号判断
	char save, tmp;        		//保存、吃回车
	int i, lg, choice, cancle; //控制变量、节点数据长度、操作选择
	Sjjd head, pointer, p;
	head = pointer = NULL;

	while (1)
	{
		i = 0;
		ch = fgetc(fp), fseek(fp, -1L, SEEK_CUR);	//文件字符指针回溯
		if (ch == EOF)
			break;
		if (pdzfc(ch) == 0) 	//保存标点符号[非英文字母]
		{
			str[i] = fgetc(fp), str[1] = '\0';		//文件字符指针指向下一个字符
			arr = (char *)malloc(2), strcpy(arr, str);//一个标点占一个字节,加'\0'一共两个字节

			if (head == NULL)   //链表为空
			{
				head = pointer = (Sjjd)malloc(sizeof(sjjd));    //开辟头节点和第一个节点
				pointer->Data = arr, pointer->da_lg = (*arr == '\t') ? 8 : 1, pointer->next = pointer->last = NULL;
			}       //每个符号占一个字节,制表符占8个字节
			else
			{
				p = (Sjjd)malloc(sizeof(sjjd));
				p->Data = arr, p->da_lg = (*arr == '\t') ? 8 : 1, p->next = NULL;
				pointer->next = p, p->last = pointer;
				pointer = p;
			}
		}
		else       //一个单词
		{
			i = 0;
			while (pdzfc(ch))		//while循环把英文字母置入数组中，直到遇到符号。
			{
				str[i] = fgetc(fp);		//当前字母置入数组
				ch = fgetc(fp), fseek(fp, -1L, SEEK_CUR);		//用ch临时存储下一个字符，文件字符指针回溯
				i++;
			}
			str[i] = '\0';		// '\0'结束字符数组【一个单词】
			lg = (int)strlen(str);		//长度不包括'\0'
			arr = (char *)malloc(lg + 1), strcpy(arr, str);     //开辟

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
			if (ch == EOF)      //排除最后以一个单词结束的文件
				break;
		}
	} //读取文本内容到链表中结束
	if (head == NULL)   //将链表输出-空
	{
		printf("文件为空！\n");        //空文件输出提示
		fclose(fp);
		qut_y_save(head, fp, fname);
	}
	else
		sclb(head, fname);      //将链表输出-非空
	//进入编辑操作
	do
	{       //编辑操作菜单
		printf("1：查找\n");
		printf("2：插入\n");
		printf("3：删除\n");
		printf("4：替换\n");
		do
		{
			choice = 0;     //清除上次成功通过判断时的数据
			scanf("%d", &choice);
			while ((tmp = getchar()) != '\n' && tmp != EOF);
			if (choice < 1 || choice > 4)
				printf("你的输入有误\n");
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
		printf("是否继续操作?y/n\n");
		save = getchar();
		while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
		if (save == 'y')   //继续操作前先清屏，然后再输出文件内容
		{
			system("cls");  //清屏
			if (head == NULL)   //将链表输出-空
			{
				printf("文件为空！\n");        //空文件输出提示
				qut_y_save(head, fp, fname);
			}
			else
				sclb(head, fname);      //将链表输出-非空
		}
	} while (save == 'y');
	//退出模式选择
	printf("是否将保存更改?\n");
	printf("1:不保存\n");
	printf("2:并保存\n");
	do
	{
		scanf("%d", &cancle);
		while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
		if (cancle < 1 || cancle > 2)
			printf("没有该选项，请重新输入：\n");
		else
			break;
	} while (1);
	if (cancle == 1)
		qut_n_save(head, fp);   //退出不保存
	else
		qut_y_save(head, fp, fname); //退出并保存
}   //文本编辑函数定义结束


//创建文本函数-二级定义
void ch_ji(FILE *fp)
{
	char ch;

	printf("请输入文本内容:(输入以“#”结束)\n");
	do
	{
		ch = getchar();
		if (ch == '#')
			break;
		fputc(ch, fp);
	} while (1);

	if (fclose(fp) == 0)
		printf("内容已成功写入到文件中！\n");
	else
		printf("写入到文件中失败！\n");
}

//辅助函数定义区
//输出链表内容函数定义
void sclb(Sjjd head, char fname[100])
{
	int toal_jd = 0, line_nm = 1, line_jd = 0, line_bt_num = 0;   //该行之前总节点个数，行号（不随每行结束清零）。该行节点个数，行字节（随每行结束清零）
	int i, j, filename_L;
	char *filename;     //存储文件名（不包括路径）
	Sjjd p = head;

	filename = cat_out_filename(fname); //提取文件名
	filename_L = (int)strlen(filename); //计算文件名长度

	for (i = 1; i < 60; i++)    //文件输出前首行提示
	{
		putchar('*');
		if (i == (59 - filename_L) / 2)
		{
			for (j = 0; j < filename_L; j++)
				putchar(filename[j]);
			i += filename_L;
		}
	}       printf("|");
	printf("toal_jd   line_jd   line_nm\n");    //每个信息占八个位宽，相邻信息间隔为两个空格
	do         //文件内容输出开始
	{
		if (*(p->Data) != '\n')     //判别换行符"\n"的处理
		{   //非换行符处理
			if (*(p->Data) == '\t')
			{
				//水平制表符处理（水平制表符形式上用连续的8个空格代替），也记为一个节点等同于其符号字符进行统计处理
				for (i = 1; i <= 8; i++)        //空格填充对齐
				{
					putchar(' ');
				}
				toal_jd++, line_jd++, line_bt_num += p->da_lg;
			}
			else
			{   //普通字符处理(空格包含在内)，直接输出
				printf("%s", p->Data), toal_jd++, line_jd++, line_bt_num += p->da_lg;
			}
		}
		else
		{   //换行符处理（换行符形式上用连续的空格代替），换行符也记为一个节点等同于其符号字符进行统计处理
			toal_jd++, line_jd++;
		}

		if (((line_bt_num >= 45 && p->next != NULL) && (p->next->da_lg != 1 || *(p->next->Data) == '\n')) || *(p->Data) == '\n')   //行尾处理
		{
			for (i = 1; i < 60 - line_bt_num; i++)      //空格填充对齐
			{
				putchar(' ');
			}       printf("|");
			printf("%-8d  %-8d  %-8d\n", toal_jd - line_jd, line_jd, line_nm);  //每个信息占八个位宽，相邻信息间隔为两个空格
			line_nm++, line_jd = 0, line_bt_num = 0;
		}

		if (p->next == NULL)    //输出结束判断
		{
			for (i = 1; i < 60 - line_bt_num; i++)      //空格填充对齐
			{
				putchar(' ');
			}       printf("|");
			printf("%-8d  %-8d  %-6d\n", toal_jd - line_jd, line_jd, line_nm);  //每个信息占八个位宽，相邻信息间隔为两个空格
			for (i = 1; i < 60; i++)        //文件输出结束提示行
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

//判断字符类别函数定义
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

//截取文件名函数定义
char *cat_out_filename(char *fname)
{
	static char filename[50];

	if (strrchr(fname, '\\') == NULL)
		strcpy(filename, fname);
	else
		strcpy(filename, strrchr(fname, '\\') + 1);     //指针往后移动一位，指向\\之后的位置

	return filename;
}

//查找函数
void Find(Sjjd head)
{
	char str[50], tmp;
	Find_data q, p;
	printf("请输入要查找的内容：\n");
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

//细化的查找功能模块开始
Find_data find(Sjjd head, char *str)
{
	Sjjd p = head;
	Find_data head1, tail, q;       //定义查找结果链表相关指针
	head1 = tail = NULL;               //查找结果结果链表指针初始化
	int total, line, linenumber1, linenumber2, enter, k, flag = 0;    //待查找字符串在文件中位置（节点、行号、行字节数、行节点、回车出现的节点、出现次数）
	k = total = linenumber2 = linenumber1 = 0, line = 1;
    //total总结点数,line行数,linenumber1,linenumber2当前行节点数
	do
	{
		if (*(p->Data) != '\n')     //判别换行符"\n"的处理
		{   //非换行符处理
			if (*(p->Data) == '\t')
				//水平制表符处理（水平制表符形式上用连续的8个空格代替），也记为一个节点等同于其符号字符进行统计处理
			{
				total++;
				linenumber2++;
				linenumber1 = linenumber1 + 8;
			}
			else  //普通字符处理，直接输出
			{
				total++;
				linenumber2++;
				linenumber1 = linenumber1 + p->da_lg;
			}
		}
		else    //换行符处理（换行符形式上用连续的空格代替），换行符也记为一个节点等同于其符号字符进行统计处理
		{
			total++;
			linenumber2++;
			enter = linenumber2;
		}

		if (((linenumber1 >= 45 && p->next != NULL) && (p->next->da_lg != 1 || *(p->next->Data) == '\n')) || *(p->Data) == '\n')    //行尾处理
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
		printf("查找失败，该字符串不存在！\n");
	}

	return head1;
}   //细化的查找模块结束

//字符串插入函数定义开始
Sjjd str_ins(Sjjd head, char *fname)
{
	char str[50], tmp;      //待插入字符临时存放位置、清除输入缓冲区用
	Sjjd p = head, p1;      //p初始化指向头指针
	int toal_jd, i;         //待插入的位置、控制变量

	printf("输入待插入的单个字符串及其插入位置(<=1插在第一位，>尾节点插在最后)：");
	scanf("%s %d", str, &toal_jd);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
	if (strcmp(str, "\\t") == 0)    //对制表符进行处理
		strcpy(str, "\t");
	else if (strcmp(str, "\\n") == 0)   //对回车进行处理
		strcpy(str, "\n");
	else if (strcmp(str, "\\s") == 0)   //对空格进行处理
		strcpy(str, " ");

	for (i = 1; i < toal_jd && p->next != NULL; i++, p = p->next);  //移动位置指针位置指针到插入位置(只要输入的节点数大于总节点数就视为插在最后一个位置)

	if (p->last == NULL)        //插入位置在头节点
	{
		p1 = (Sjjd)malloc(sizeof(sjjd));
		p1->Data = strcpy((char *)malloc(strlen(str) + 1), str), p1->da_lg = (*str == '\t' ? 8 : strlen(str));
		p1->last = NULL, p1->next = p;
		head = p->last = p1;
	}
	else if (p->next == NULL && i < toal_jd)    //插入位置在尾节点
	{
		p1 = (Sjjd)malloc(sizeof(sjjd));
		p1->Data = strcpy((char *)malloc(strlen(str) + 1), str), p1->da_lg = (*str == '\t' ? 8 : strlen(str));
		p1->next = NULL, p1->last = p;
		p->next = p1;
	}
	else     //插入位置在中间
	{
		p1 = (Sjjd)malloc(sizeof(sjjd));
		p1->Data = strcpy((char *)malloc(strlen(str) + 1), str), p1->da_lg = (*str == '\t' ? 8 : strlen(str));
		p->last->next = p1, p1->last = p->last, p1->next = p, p->last = p1;
	}
	system("cls");  //清屏
	printf("插入后的文件内容如下：\n");
	sclb(head, fname);

	return head;
}//字符串插入函数定义结束

//字符串删除函数定义开始
Sjjd str_del(Sjjd head, char *fname)
{
	char str[50], tmp;      //待删除字符串、清除缓冲区用
	Find_data head_fd, p_fd;    //定义查找结果链表相关指针
	int choice, i;

	printf("请输入要删除的字符串：");
	scanf("%s", str);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
	if (strcmp(str, "\\t") == 0)    //对制表符进行处理
		strcpy(str, "\t");
	else if (strcmp(str, "\\n") == 0)   //对回车进行处理
		strcpy(str, "\n");
	else if (strcmp(str, "\\s") == 0)   //对空格进行处理
		strcpy(str, " ");

	p_fd = head_fd = find(head, str);     //调用查找函数查找对应内容
	if (head_fd == NULL)    //要删除的字符串不存在处理
		goto end;
	printf("请选择删除对象（“0”表示删除全部查找到的对象，选择删除时每次只能删除一个！）：\n");
re: scanf("%d", &choice);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
	if (choice < 0)     //限定输入的对象只能为>=0的数
	{
		printf("输入数据有误！请重新输入：");
		goto re;
	}
	p_fd = head_fd;     //goto的加入使得要添加该语句
	if (choice == 0)    //查找到内容全部删除
	{
		do
		{   //删除操作开始
			if (p_fd->sjjd_last == NULL)    //头节点的删除
			{
				free(p_fd->sjjd_next->last->Data);  //释放该节点存放的字符串空间
				free(p_fd->sjjd_next->last);        //释放该节点所占内存空间
				head = p_fd->sjjd_next; //头结点下移一位
				head->last = NULL;
			}
			else if (p_fd->sjjd_next == NULL)   //尾节点的删除
			{
				free(p_fd->sjjd_last->next->Data);  //释放该节点存放的字符串空间
				free(p_fd->sjjd_last->next);    //释放该节点所占内存空间
				p_fd->sjjd_last->next = NULL;
			}
			else     //中间节点的删除
			{
				free(p_fd->sjjd_next->last->Data);
				free(p_fd->sjjd_next->last);
				p_fd->sjjd_last->next = p_fd->sjjd_next;    //上一个节点的next域与下一个节点相连
				p_fd->sjjd_next->last = p_fd->sjjd_last;    //下一个节点的last域与上一个节点相连
			}
			if (p_fd->fd_next == NULL)
				break;
			p_fd = p_fd->fd_next;
		} while (1);
	}
	else    //删除指定的查找内容
	{
		for (i = 1; i < choice; p_fd = p_fd->fd_next, i++)      //移动到要删除的节点
		{
			if (p_fd->fd_next == NULL)      //输入的序号超过查找到的个数
			{
				printf("你的输入有误，请检查后重新输入！");
				goto re;
			}
		}
		//删除操作开始
		if (p_fd->sjjd_last == NULL)    //头节点的删除
		{
			free(p_fd->sjjd_next->last->Data);  //释放该节点存放的字符串空间
			free(p_fd->sjjd_next->last);        //释放该节点所占内存空间
			head = p_fd->sjjd_next; //头结点下移一位
			head->last = NULL;
		}
		else if (p_fd->sjjd_next == NULL)   //尾节点的删除
		{
			free(p_fd->sjjd_last->next->Data);  //释放该节点存放的字符串空间
			free(p_fd->sjjd_last->next);    //释放该节点所占内存空间
			p_fd->sjjd_last->next = NULL;
		}
		else     //中间节点的删除
		{
			free(p_fd->sjjd_next->last->Data);
			free(p_fd->sjjd_next->last);
			p_fd->sjjd_last->next = p_fd->sjjd_next;    //上一个节点的next域与下一个节点相连
			p_fd->sjjd_next->last = p_fd->sjjd_last;    //下一个节点的last域与上一个节点相连
		}
	}
	dest_fd(head_fd);   //释放查找链表空间
	system("cls");      //清屏
	printf("删除操作完成！删除后的内容如下：\n");
	sclb(head, fname);

end:    return head;
}//字符串删除函数定义结束

//字符串替换函数定义开始
Sjjd str_rep(Sjjd head, char *fname)
{
	char str[50], str_tar[50], tmp;       //待替换字符串、清除缓冲区用
	Find_data head_fd, p_fd, p1;    //定义查找结果链表相关指针
	int choice, i;

	printf("请输入被替换的字符串和替换后的字符串:");
	scanf("%s %s", str, str_tar);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
	//str的处理
	if (strcmp(str, "\\t") == 0)    //对制表符进行处理
		strcpy(str, "\t");
	else if (strcmp(str, "\\n") == 0)   //对回车进行处理
		strcpy(str, "\n");
	else if (strcmp(str, "\\s") == 0)   //对空格进行处理
		strcpy(str, " ");
	//str_tar的处理
	if (strcmp(str_tar, "\\t") == 0)    //对制表符进行处理
		strcpy(str_tar, "\t");
	else if (strcmp(str_tar, "\\n") == 0)   //对回车进行处理
		strcpy(str_tar, "\n");
	else if (strcmp(str_tar, "\\s") == 0)   //对空格进行处理
		strcpy(str_tar, " ");

	p_fd = head_fd = find(head, str);     //调用查找函数查找对应内容
	if (head_fd == NULL)    //待替换字符不存在的处理
		goto end;
	printf("请选择替换对象（“0”表示替换全部查找到的对象，选择替换时每次只能替换一个！）：\n");
re: scanf("%d", &choice);
	while ((tmp = getchar()) != '\n' && tmp != EOF);    //清除输入缓冲区
	if (choice < 0)     //限定输入的对象只能为>=0的数
	{
		printf("输入数据有误！请重新输入：");
		goto re;
	}
	p_fd = head_fd;     //goto的加入使得要添加该语句
	if (choice == 0)    //查找到内容全部替换
	{
		do
		{   //替换操作开始
			if (p_fd->sjjd_last == NULL)    //头节点的替换
			{
				free(p_fd->sjjd_next->last->Data);  //释放该节点存放的字符串空间
				p_fd->sjjd_next->last->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //替换
				p_fd->sjjd_next->last->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //替换后的数据长度
			}
			else if (p_fd->sjjd_next == NULL)   //尾节点的替换
			{
				free(p_fd->sjjd_last->next->Data);  //释放该节点存放的字符串空间
				p_fd->sjjd_last->next->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //替换
				p_fd->sjjd_last->next->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //替换后的数据长度
			}
			else     //中间节点的替换
			{
				free(p_fd->sjjd_next->last->Data);  //释放该节点存放的字符串空间
				p_fd->sjjd_next->last->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //替换
				p_fd->sjjd_next->last->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //替换后的数据长度
			}
			if (p_fd->fd_next == NULL)
				break;
			p_fd = p_fd->fd_next;
		} while (1);
	}
	else    //替换指定的查找内容
	{
		for (i = 1; i < choice; p_fd = p_fd->fd_next, i++)      //移动到要删除的节点
		{
			if (p_fd->fd_next == NULL)      //输入的序号超过查找到的个数
			{
				printf("你的输入有误，请检查后重新输入！");
				goto re;
			}
		}
		//替换操作开始
		if (p_fd->sjjd_last == NULL)    //头节点的替换
		{
			free(p_fd->sjjd_next->last->Data);  //释放该节点存放的字符串空间
			p_fd->sjjd_next->last->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //替换
			p_fd->sjjd_next->last->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //替换后的数据长度
		}
		else if (p_fd->sjjd_next == NULL)   //尾节点的替换
		{
			free(p_fd->sjjd_last->next->Data);  //释放该节点存放的字符串空间
			p_fd->sjjd_last->next->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //替换
			p_fd->sjjd_last->next->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //替换后的数据长度
		}
		else     //中间节点的替换
		{
			free(p_fd->sjjd_next->last->Data);  //释放该节点存放的字符串空间
			p_fd->sjjd_next->last->Data = strcpy((char *)malloc(strlen(str_tar) + 1), str_tar); //替换
			p_fd->sjjd_next->last->da_lg = (*str_tar == '\t' ? 8 : strlen(str_tar));    //替换后的数据长度
		}
	}
	dest_fd(head_fd);   //释放查找链表空间
	system("cls");      //清屏
	printf("替换操作完成！替换后的内容如下：\n");
	sclb(head, fname);

end:    return head;
}//字符串替换函数定义结束

//退出编辑模式不保存函数定义开始
void qut_n_save(Sjjd head, FILE *fp)
{
	Sjjd p1, p2 = p1 = head;
	//销毁链表
	while (p1->next != NULL)
	{
		free(p1->Data);
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	if (fclose(fp) == 0)
		printf("操作成功！已关闭文件指针。\n");
	else
		printf("操作失败！关闭文件指针失败。\n");
} //退出编辑模式不保存函数定义结束

//退出编辑模式并保存函数定义开始
void qut_y_save(Sjjd head, FILE *fp, char *fname)
{
	Sjjd p1, p2 = p1 = head;

	fclose(fp); fp = fopen(fname, "w"); //改变文件打开属性，切换为写操作
	//将链表内容输入到文件中
	do
	{
		fprintf(fp, "%s", p1->Data);
		if (p1->next == NULL)
			break;
		else
			p1 = p1->next;
	} while (1);
	//销毁链表
	p1 = p2;
	while (p1->next != NULL)
	{
		free(p1->Data);
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	if (fclose(fp) == 0)
		printf("操作成功！文件已保存，文件指针已关闭。\n");
	else
		printf("操作失败！文件保存失败，关闭文件指针失败。\n");
}//退出编辑模式并保存函数定义结束


void dest_fd(Find_data head_fd) //释放查找结果链表函数
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

