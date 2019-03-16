#include "iostream"
#include"string" //操作字符串必须包含的头文件

using namespace std;

int main()
{
	int n;
	int s[200];
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
	}

	for (int i = 0; i < n; i++)
	{
		for (int t = 0;	t < n-i-1; t++)
		{
			int temp;
			if (s[t] > s[t + 1])
			{
				temp = s[t];
				s[t] = s[t + 1];
				s[t + 1] = temp;
			}
		}
	}

	for (int i = 0; i < n-1; i++)
	{
		cout << s[i]<<" ";
	}
	cout << s[n - 1]<<endl;
	system("pause");
	return 0;
}
