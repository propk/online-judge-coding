// author propk
//HackerRank

#include<iostream>
#include<math.h>
using namespace std;

long reccursive(int n)
{
	if (n == 4) return 2;
	else if (n == 0) return 0;
	else if (n < 4) return 1;
	else 
		return reccursive(n - 1) + reccursive(n - 4);

}

long noPrimes(long m)
{
	long n = reccursive(m);
	cout << n << endl;
	if (n < 2) return 0;
	else
	{
		long count = 0;
		bool arr[300000] = { 0 };
	
		for (long i = 2; i <= sqrt(n); i++)
		{
			if (!arr[i])
			{
				for (long j = 2; j <= n; j++)
				{
					if (i != j)
						if (j%i == 0) arr[j] = 1;
				}
			}
		}

		for (long i = 2; i <= n; i++)
		{
			if (!arr[i]) count++;
		}
		return count;
	}
}
int main()
{
	int t, n;
	cin >> t;
	while (t--)
	{
		cin >> n;
		cout << noPrimes(n) << endl;
	}
	cin >> n;
	return 0;
}
