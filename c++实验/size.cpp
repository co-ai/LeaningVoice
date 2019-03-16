#include<iostream>
using namespace std;
const double Pi = 3.14;

int size(double );
int size(double,double);

int main()
{
	double r,a,b;
	char s;
	cout<<"圆:C,正方形：S，长方形：R:  "<<endl;
	cin>>s;
	if(s == 'C')
	{
		cout<<"请输入半径："<<endl;
		cin>>r;
		size(r);
	}
	else if(s == 'S' || s == 'R')
	{
		cout<<"请输入边长或者长宽："<<endl;
        cin>>a>>b;
        size(a,b);
	}
}

int size(double r)
{
	double size = Pi*r*r;
	cout<<"面积："<<size<<endl;
	return 0;
}

int size(double a,double b)
{
	double size = a*b;
	cout<<"面积："<<size<<endl;
	return 0;
}
