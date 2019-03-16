#include<iostream>
using namespace std;

int max1(int x ,int y = 0)
{
	if(x>y)
	{
		cout<<"positive"<<endl;
	}
	else cout<<"negative"<<endl;
}

int main()
{
	int x;
	while(cin>>x && x != '#')
	{max1(x);}
	return 0;
}
