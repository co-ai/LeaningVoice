#include "iostream"
#include"string" //�����ַ������������ͷ�ļ�

using namespace std;
void fanb(int);

void main()
{
	int n;
	cin >> n;
	fanb(n);
	system("pause");
	return;
}

void fanb(int n)
{
	int f0 = 1;
	int f1 = 1;
	int temp;


	for ( int i = 1; i < n; i++)
	{
		temp = f1;
		f1 = (f0 + f1) % 10007;
		f0 = temp;
	}

	cout << f0 << endl;
}

