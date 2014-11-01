#include<iostream>
#define MAX 2700
// Author : Propk

using namespace std;
long arr[MAX] = { 0 };

void ans()
{
	for (int i = 2; i < MAX; i++)
		if (arr[i] == 0)
			for (int j = i + 1; j < MAX; j++)
				if (arr[j] < 3 && j % i == 0) arr[j]++;
}

int main()
{
	int count = 0, op[1100], j=0;
	ans();
	for (int i = 0; i < MAX; i++)
	{
		if (arr[i]>2) {
			//count++;   // to calibrate MAX
			op[j] = i; j++;
		}
	}
	//cout << count << endl;
	int t, n;
	cin >> t;
	while (t--)
	{
		cin >> n;
		cout << op[n-1] << endl;
	}
	return 0;
}
