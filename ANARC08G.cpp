#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#define gc getchar_unlocked // not supported on windows and unsafe
// Author: Propk

void scanint(int &x) // fast i-o for improved runtime (unsigned i-0)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

using namespace std;
int arr[1000][1000];

int main() // ad-hoc question
{
	int serial, counter = 0;
	scanint(serial);
	while (serial != 0)
	{
		counter++;
		int  give[1000] = { 0 }, take[1000] = { 0 }, sum2 = 0;
		for (int i = 0; i < serial; i++)
		{
			for (int j = 0; j < serial; j++)
			{
				scanint(arr[i][j]);
				give[j] += arr[i][j];
				sum2 += arr[i][j];
			}
		}
		for (int i = 0; i < serial; i++)
			for (int j = 0; j < serial; j++)
				take[j] += arr[j][i];
		for (int i = 0; i < serial; i++){
			if (take[i]>give[i]) {
				take[i] -= give[i]; give[i] = 0;
			}
			else{
				give[i] -= take[i]; take[i] = 0;
			}
		}
		int sum = 0;
		for (int i = 0; i < serial; i++)
			sum += give[i];
			printf("%d. %d %d\n",counter,sum2,sum);
		//cout << counter << ". " << sum2 << " " << sum << endl;
		scanf("%d", &serial);
	}//end of test case
	return 0;
}
