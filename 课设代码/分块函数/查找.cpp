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
Find_data find(Sjjd head, char *str)
{
	Sjjd p = head;
	Find_data head1, tail, q;       //定义查找结果链表相关指针
	head1 = tail = NULL;               //查找结果结果链表指针初始化
	int total, line, linenumber1, linenumber2, enter, k, flag = 0;    //待查找字符串在文件中位置（节点、行号、行字节数、行节点、回车出现的节点、出现次数）
	k = total = linenumber2 = linenumber1 = 0, line = 1;

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
				printf("num:%-6d line_nm:%-6d toal_jd:%-6d line_jd:%-6d\n", k, line - 1,total, enter);
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

