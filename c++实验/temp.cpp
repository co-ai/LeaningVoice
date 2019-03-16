#include<iostream>
using namespace std;

int main()
{
	double temp,t;
	cout<<"Fahrenheit:";
	cin>>temp;
	t = (temp-32)*5/9;
	cout<<"Celsius="<<(temp-32)*5/9<<endl;
	return 0;
}
