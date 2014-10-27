// author propk
//HackerRank

#include<iostream>
#include<math.h>
#include<map>

using namespace std;
map<int, int> MyMap;

int reccursive(int n)
{
	if (!(MyMap.find(n) == MyMap.end())) return MyMap[n];
	else if (n < 4 )
	{
		MyMap[n] = 1; return 1;
	}
	else 
		return reccursive(n - 1) + reccursive(n - 4);

}

bool arr[250000] = { 0 };
void noPrimes(int n)
{
	int count = 0;
	for (int i = 2; i <= sqrt(n); i++)
		if (!arr[i])
			for (int j = 2; j <= n; j++)
				if (i != j)
					if (j%i == 0) arr[j] = 1;
	arr[0] = 1; arr[1] = 2;
}
int main()
{
	int t, n;
	cin >> t;
	noPrimes(250000);
	while (t--)
	{
		cin >> n;
		int count = 0;
		int r = reccursive(n);
		for (int i = 2; i <= r; i++)
			if (!arr[i]) count++;
		cout << count << endl;
	}
	cin >> n;
	return 0;
}
