#include<iostream>
using namespace std;

int max1(int,int);
int max1(int,int,int);
double max1(double,double);
double max1(double,double,double);

int main()
{
	int a,b,c;
	double a1,a2,a3;
	cout<<"please:";
	cin>>a>>b>>c>>a1>>a2>>a3;
	cout<<"max two int "<<max1(a,b)<<endl;
	cout<<"max three int "<<max1(a,b,c)<<endl;
	cout<<"max two double "<<max1(a1,a2)<<endl;
	cout<<"max three double "<<max1(a1,a2,a3)<<endl;
	return 0;
}

int max1(int x,int y)
{
	if(x<y)
	{
		x = y;
	}
	return x;
}

int max1(int x,int y,int z)
{
	if(x<y)
	{
		x = y;
	}
	if(x<z)
	{
		x = z;
	}
	return x;
}
double max1(double x,double y)
{
	if(x<y)
	{
		x = y;
	}
	return x;
}

double max1(double x,double y,double z)
{
	if(x<y)
	{
		x = y;
	}
	if(x<z)
	{
		x = z;
	}
	return x;
}
