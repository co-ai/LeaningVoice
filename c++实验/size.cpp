#include<iostream>
using namespace std;
const double Pi = 3.14;

int size(double );
int size(double,double);

int main()
{
	double r,a,b;
	char s;
	cout<<"Բ:C,�����Σ�S�������Σ�R:  "<<endl;
	cin>>s;
	if(s == 'C')
	{
		cout<<"������뾶��"<<endl;
		cin>>r;
		size(r);
	}
	else if(s == 'S' || s == 'R')
	{
		cout<<"������߳����߳���"<<endl;
        cin>>a>>b;
        size(a,b);
	}
}

int size(double r)
{
	double size = Pi*r*r;
	cout<<"�����"<<size<<endl;
	return 0;
}

int size(double a,double b)
{
	double size = a*b;
	cout<<"�����"<<size<<endl;
	return 0;
}
