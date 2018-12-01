#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE * fp,* fpx;
	char ch,newfile[10];
	if((fp = fopen("C:\\Users\\Pec\\Desktop\\test.txt","r")) == NULL)
	{
		printf("can not open this file/n");
		exit(0);
	}
	printf("please input your file name:");
	scanf("%s",newfile);
	if((fpx = fopen(newfile,"w")) == NULL)
	{
		printf("can not open this file/n");
		exit(0);
	}
	while(!feof(fp))
	{	
		ch = fgetc(fp);
		fputc(ch,fpx);
		putchar(ch);
	}
	fclose(fp);	
	fclose(fpx);		
	putchar(10);
	return 0;
}
