#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>

using namespace std;

int mp[1100][1100];

void dfs(int n)
{
	if (n == 1)
	{
		mp[1][1] = 1;
		return;
	}
	if (n & 1) n++;
	int t = n / 2;
	dfs(t);
	for (int i = 1; i <= t; i++)
		for (int j = 1; j <= t + 1; j++)
		{
			if (mp[i][j] > t)
			{
				mp[i + t][j] = i;
				mp[i][j] = i + t;
				int c = i + t + 1;
				for (int k = t + 2; (t & 1) && k <= n; k++, c++)
				{
					if (c == i + t)  c++;
					if (c > n) c -= n / 2;
					mp[i][k] = c;
					mp[c][k] = i;
				}
			}
			else
			{
				mp[i + t][j] = mp[i][j] + t;
				if ((t % 2 == 0) || t == 1)
				{
					mp[i + t][j + t] = mp[i][j];
					mp[i][j + t] = mp[i + t][j];
				}
			}
		}
}


int main()
{
	int n;
	while (~scanf("%d", &n))
	{
		memset(mp, 0, sizeof(mp));
		if (n & 1) dfs(n + 1);
		else    dfs(n);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n + (n & 1); j++)
			{
				cout << (mp[i][j] > n ? 0 : mp[i][j]);
				cout << (j == 1 ? ": " : " ");
			}
			cout << endl;
		}
		cout << endl;
	}
}
