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
Find_data find(Sjjd head, char *str)
{
	Sjjd p = head;
	Find_data head1, tail, q;       //������ҽ���������ָ��
	head1 = tail = NULL;               //���ҽ���������ָ���ʼ��
	int total, line, linenumber1, linenumber2, enter, k, flag = 0;    //�������ַ������ļ���λ�ã��ڵ㡢�кš����ֽ������нڵ㡢�س����ֵĽڵ㡢���ִ�����
	k = total = linenumber2 = linenumber1 = 0, line = 1;

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
		printf("����ʧ�ܣ����ַ��������ڣ�\n");
	}

	return head1;
}   //ϸ���Ĳ���ģ�����

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

