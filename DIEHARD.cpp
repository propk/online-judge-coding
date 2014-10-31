#include<iostream>
#include<map>
//author: Propk
using namespace std;

int max3(int a, int b, int c)
{
	if (a >= b && a >= c) return a;
	else if (b >= c) return b;
	else return c;
}

int r[1001][1001][3] = { 0 };
int survive_dp(int h, int a, int state, int level) // dynamic programming
{
	if (h <= 0 || a <= 0) return level;
    else if (r[h][a][state] > 0) return r[h][a][state];
	else
	{
		int m1, m2;
		if (state == 0)
		{
			m1 = survive_dp(h - 5, a - 10, 1, level + 1);
			m2 = survive_dp(h - 20, a + 5, 2, level + 1);
			int ans = m1 > m2 ? m1 : m2;
			r[h][a][state] = ans;
			return ans;
		}
		else if (state == 1)
		{
			m1 = survive_dp(h + 3, a + 2, 0, level + 1);
			m2 = survive_dp(h - 20, a + 5, 2, level + 1);
			int ans = m1 > m2 ? m1 : m2;
			r[h][a][state] = ans;
			return ans;
		}
		else
		{
			m1 = survive_dp(h + 3, a + 2, 0, level + 1);
			m2 = survive_dp(h - 5, a - 10, 1, level + 1);
			int ans = m1 > m2 ? m1 : m2;
			r[h][a][state] = ans;
			return ans;
		}

	}
}

int main()
{
	int t, h, a;
	cin >> t;

	while (t--)
	{
		for (int i = 0; i < 1001; i++)
		  for (int j = 0; j < 1001; j++)
		  	for (int k = 0; k < 3; k++)
			  	r[i][j][k] = -100000;
		cin >> h >> a;
		cout << max3(survive_dp(h, a, 0, -1), survive_dp(h, a, 1, -1), survive_dp(h, a, 2, -1)) << endl;
	}
	
	return 0;
}
