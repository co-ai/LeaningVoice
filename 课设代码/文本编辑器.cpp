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
typedef struct _find_data{
    int num;    //���ֱ��
    int jd_num; //�ڵ���
    Sjjd sjjd_last; //��һ�����ݽڵ��ַ
    Sjjd sjjd_next; //��һ�����ݽڵ��ַ
    struct _find_data *fd_next; //��һ���������ݽڵ�λ��
}find_data, *Find_data;

void wenbenbj_1(char *fname);   //�ı��༭һ��
void wenbencj_2(char *fname);   //�ı�����һ��
void theme_3(void);             //����ѡ��һ��
void bi_ji(FILE *fp, char fname[100]);  //�༭�ı�����
void ch_ji(FILE *fp);                   //�����ı�����
char *cat_out_filename(char *fname);        //��ȡ�ļ���
int pdzfc(char fp);                         //�ж��ַ������
void sclb(Sjjd head,char fname[100]);       //�����������
Find_data str_fnd_xh(Sjjd head, char *str); //ϸ���Ĳ��ҹ���ģ��
void dest_fd(Find_data head_fd);            //�ͷŲ��ҽ��������
void str_fnd(Sjjd head);                            //�ַ�������
Sjjd str_ins(Sjjd head, char *fname);               //�ַ�������
Sjjd str_del(Sjjd head, char *fname);               //�ַ���ɾ��
Sjjd str_rep(Sjjd head, char *fname);               //�ַ����滻
void qut_n_save(Sjjd head, FILE *fp);               //�˳�������
void qut_y_save(Sjjd head, FILE *fp, char *fname);  //�˳�������

int main(void)
{
    char fname[100], tmp;   //�ļ�������·��������������
    int choice1;    //�˵�ѡ��
    char choice2;   //��������ѡ��

    system("title Notepad_Simple 1.0"); //���ڱ�����ʾ������
    do
    {
        printf("��ӭʹ��simple Notepad\n");
        printf("ע������������ļ��༭���ܡ�Ŀǰֻ֧��Ӣ���ı�����\n���������ı��������ݲ���Ӱ�죩�������汾��֧�����ģ���\n�˴����Ĳ��������^_^!\n");
        printf("��ѡ��\n");
        printf("1�����ļ�\t");
        printf("2�������ļ�\n");
        printf("3������ѡ��\t");
        printf("4����    ��\n");
        do
        {
            scanf("%d", &choice1);
            while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
            if (choice1 < 1 || choice1 > 4)
                printf("û�и�ѡ����������룺\n");
            else
                break;
        } while (1);

        switch (choice1)
        {
        case 1: system("mode con cols=90"); wenbenbj_1(fname); break;
        case 2: system("mode con cols=60"); wenbencj_2(fname); break;
        case 3: theme_3(); choice2 = 'y';   goto re; break;     //ִ�������������ֱ����ת����ʼ����
        case 4: choice2 = 'n';  goto re; break;
        }

        printf("�Ƿ����������y/n��");
        scanf("%c", &choice2);
        while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
    re: if (choice2 == 'y')     //��������ǰ����
            system("cls");
    } while (choice2 == 'y' );

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
void theme_3(void)      //����ѡ��-һ��
{
    int choice;     //����ѡ��
    char tmp;   //����������
    printf("��ѡ�����⣺\n");
    printf("1:���ۺ�   2:�����\n");
    printf("3:��Ȼ��   4:�����\n");

    do
    {
        scanf("%d", &choice);
        while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
        if (choice >= 1 && choice <= 4)
            break;
        else
            printf("û�и����⣬������������룡\n");
    } while (1);

    switch (choice)
    {
    case 1: system("color 0E"); break;
    case 2: system("color 0F"); break;
    case 3: system("color 2F"); break;
    case 4: system("color 4F"); break;
    }
}

//�ı��༭����-�������忪ʼ
void bi_ji(FILE *fp, char fname[100])
{
    char str[30], *arr, ch; //��ʱ����ַ������������ַ����������ж�
    char flag1, tmp;        //(flag1��flag2)���������ж��á�������뻺����
    int i, lg, choice, quit_mode;           //���Ʊ������ڵ����ݳ��ȡ�����ѡ��
    Sjjd head, tail, p;
    head = tail = NULL;
    //��ȡ�ı����ݵ������п�ʼ
    while ( 1 )
    {
        i = 0;
        ch = fgetc(fp), fseek(fp, -1L, SEEK_CUR);
        if (ch == EOF)
            break;
        //һ�����ţ��ո񡢻س����Ʊ�������ַ���
        if (pdzfc(ch) == 0)
        {
            str[i] = fgetc(fp), str[1] = '\0';
            arr = (char *)malloc(2), strcpy(arr, str);

            if (head == NULL)
            {
                head = tail = (Sjjd)malloc(sizeof(sjjd));
                tail->Data = arr, tail->da_lg = (*arr == '\t') ? 8 : 1, tail->next = tail->last = NULL;
            }
            else
            {
                p = (Sjjd)malloc(sizeof(sjjd));
                p->Data = arr, p->da_lg = (*arr == '\t') ? 8 : 1, p->next = NULL;
                tail->next = p, p->last = tail;
                tail = p;
            }
        }
        else       //һ������
        {
            i = 0;
            while (pdzfc(ch))
            {
                str[i] = fgetc(fp);
                ch = fgetc(fp), fseek(fp, -1L, SEEK_CUR);
                i++;
            }
            str[i] = '\0';
            lg = (int)strlen(str);
            arr = (char *)malloc(lg + 1), strcpy(arr, str);

            if (head == NULL)
            {
                head = tail = (Sjjd)malloc(sizeof(sjjd));
                tail->Data = arr, tail->da_lg = lg, tail->next = tail->last = NULL;
            }
            else
            {
                p = (Sjjd)malloc(sizeof(sjjd));
                p->Data = arr, p->da_lg = lg, p->next = NULL;
                tail->next = p, p->last = tail;
                tail = p;
            }
            if (ch == EOF)      //�ų������һ�����ʽ������ļ�
                break;
        }
    } //��ȡ�ı����ݵ������н���
    if (head == NULL)   //���������-��
    {
        printf("���ļ�Ϊ���ļ������л��������ı�������\n");        //���ļ������ʾ
        fclose(fp);
        goto end;
    }
    else
        sclb(head, fname);      //���������-�ǿ�
    //����༭����
    do
    {       //�༭�����˵�
        printf("��ѡ�������\n");
        printf("1���ַ�������\n");
        printf("2���ַ�������\n");
        printf("3���ַ���ɾ��\n");
        printf("4���ַ����滻\n");
        do
        {
            choice = 0;     //����ϴγɹ�ͨ���ж�ʱ������
            scanf("%d", &choice);
            while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
            if (choice < 1 || choice > 4)
                printf("û�и�ѡ����������룺\n");
            else
                break;
        } while (1);

        switch (choice)
        {
        case 1:
            str_fnd(head); break;   //�ַ�������
        case 2:
            head = str_ins(head, fname); break; //�ַ�������
        case 3:
            head = str_del(head, fname); break; //�ַ���ɾ��
        case 4:
            head = str_rep(head, fname); break; //�ַ����滻
        }
        printf("�Ƿ��˳��ļ��༭������y/n\n");
        flag1 = getchar();
        while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
        if (flag1 == 'n')   //��������ǰ��������Ȼ��������ļ�����
        {
            system("cls");  //����
            if (head == NULL)   //���������-��
            {
                printf("���ļ�Ϊ���ļ������л��������ı�������\n");        //���ļ������ʾ
                goto end;
            }
            else
                sclb(head, fname);      //���������-�ǿ�
        }
    } while (flag1 == 'n');
    //�˳�ģʽѡ��
    printf("�˳�ģʽѡ��\n");
    printf("1���˳�������\n");
    printf("2���˳�������\n");
    do
    {
        scanf("%d", &quit_mode);
        while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
        if (quit_mode < 1 || quit_mode > 2)
            printf("û�и�ѡ����������룺\n");
        else
            break;
    } while (1);
    if (quit_mode == 1)
        qut_n_save(head, fp);   //�˳�������
    else
        qut_y_save(head, fp,fname); //�˳�������
    end:;
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
    int toal_jd=0, line_nm = 1, line_jd=0, line_bt_num=0;   //����֮ǰ�ܽڵ�������кţ�����ÿ�н������㣩�����нڵ���������ֽڣ���ÿ�н������㣩
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

        if ( ((line_bt_num >= 45 && p->next != NULL) && (p->next->da_lg != 1 || *(p->next->Data) == '\n')) || *(p->Data) == '\n')   //��β����
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

//�ַ������Һ������忪ʼ
void str_fnd(Sjjd head)
{
    char str[50], tmp;
    Find_data head_fd, p_fd;

    printf("������Ҫ���ҵ��ַ�������ֻ֧�ֵ������ʻ��ַ�������\n");
    scanf("%s", str);
    while ((tmp = getchar()) != '\n' && tmp != EOF);    //������뻺����
    if (strcmp(str, "\\t") == 0)    //���Ʊ�����д���
        strcpy(str, "\t");
    else if (strcmp(str, "\\n") == 0)   //�Իس����д���
        strcpy(str, "\n");
    else if (strcmp(str, "\\s") == 0)   //�Կո���д���
        strcpy(str, " ");

    head_fd = str_fnd_xh(head, str);
    dest_fd(head_fd);   //�ͷŲ�������ռ�
}       //�ַ������Һ����������

//ϸ���Ĳ��ҹ���ģ�鿪ʼ
Find_data str_fnd_xh(Sjjd head, char *str)
{
    Sjjd p = head;
    Find_data head_fd, tail_fd, p_fd;       //������ҽ���������ָ��
    head_fd = tail_fd = NULL;               //���ҽ���������ָ���ʼ��
    int toal_jd, line_nm, line_bt_num, line_jd, enter_jd, cnt, flag = 0;    //�������ַ������ļ���λ�ã��ڵ㡢�кš����ֽ������нڵ㡢�س����ֵĽڵ㡢���ִ�����
    cnt = toal_jd = line_jd =line_bt_num = 0, line_nm = 1;

    do
    {
        if (*(p->Data) != '\n')     //�б��з�"\n"�Ĵ���
        {   //�ǻ��з�����
            if (*(p->Data) == '\t')
                //ˮƽ�Ʊ������ˮƽ�Ʊ����ʽ����������8���ո���棩��Ҳ��Ϊһ���ڵ��ͬ��������ַ�����ͳ�ƴ���
                toal_jd++, line_jd++, line_bt_num += 8;
            else  //��ͨ�ַ�����ֱ�����
                toal_jd++, line_jd++, line_bt_num += p->da_lg;
        }
        else    //���з��������з���ʽ���������Ŀո���棩�����з�Ҳ��Ϊһ���ڵ��ͬ��������ַ�����ͳ�ƴ���
            toal_jd++, line_jd++, enter_jd = line_jd;

        if (((line_bt_num >= 45 && p->next != NULL) && (p->next->da_lg != 1 || *(p->next->Data) == '\n')) || *(p->Data) == '\n')    //��β����
            line_nm++, line_jd = 0, line_bt_num = 0;

        if (!strcmp(p->Data, str))
        {
            cnt++;
            if(strcmp(p->Data, "\n") == 0)
                printf("num:%-6d line_nm:%-6d toal_jd:%-6d line_jd:%-6d\n", cnt, line_nm-1, toal_jd, enter_jd);
            else
                printf("num:%-6d line_nm:%-6d toal_jd:%-6d line_jd:%-6d\n", cnt, line_nm, toal_jd, line_jd);
            p_fd = (Find_data)malloc(sizeof(find_data));
            p_fd->sjjd_next = p->next, p_fd->sjjd_last = p->last, p_fd->num = cnt, p_fd->jd_num = toal_jd, p_fd->fd_next = NULL;
            if (head_fd == NULL)
                head_fd = tail_fd = p_fd;
            else
                tail_fd->fd_next = p_fd;    tail_fd = p_fd;
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

    return head_fd;
}   //ϸ���Ĳ���ģ�����

//�ַ������뺯�����忪ʼ
Sjjd str_ins(Sjjd head,char *fname)
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

    p_fd = head_fd = str_fnd_xh(head, str);     //���ò��Һ������Ҷ�Ӧ����
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
    char str[50],str_tar[50],tmp;       //���滻�ַ����������������
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

    p_fd = head_fd = str_fnd_xh(head, str);     //���ò��Һ������Ҷ�Ӧ����
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
    Sjjd p1, p2=p1=head;
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
void qut_y_save(Sjjd head, FILE *fp,char *fname)
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

