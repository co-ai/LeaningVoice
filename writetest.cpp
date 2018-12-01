#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE * fp;
	char ch,filename[10];
	printf("your file name£º");
	scanf("%s",filename);
	if((fp = fopen(filename,"w")) == NULL)
	{
		printf("can not open this file/n");
		exit(0);
	}
	ch = getchar();
	printf("please input a serials of strings:");
	ch = getchar();
	while(ch!='#')
	{
		fputc(ch,fp);
		putchar(ch);
		ch = getchar();
	}
	fclose(fp);
	putchar(10);
	return 0;
}
