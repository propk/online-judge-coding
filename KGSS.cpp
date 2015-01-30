#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
using namespace std;
struct node{
	long long max0, max1, sum;
	node() :
		sum(0), max0(-1), max1(0) {
	}
};

node st[1000009];
long long arr[500000];
inline void update(node &p, const node &ch1, const node &ch2)
{
	if (ch1.max0 > ch2.max0)
	{
		p.max0 = ch1.max0;
		if (ch2.max0 > ch1.max1) p.max1 = ch2.max0;
		else p.max1 = ch1.max1;
	}
	else
	{
		p.max0 = ch2.max0;
		if (ch1.max0 > ch2.max1) p.max1 = ch1.max0;
		else p.max1 = ch2.max1;
	}
	p.sum = p.max0 + p.max1;
}

void construct(long long * arr, long long b, long long e, long long si)
{
	if (e == b)
	{
		st[si].max0 = arr[b];// > arr[e] ? arr[b] : arr[e];
		st[si].max1 = -1;// arr[b] < arr[e] ? arr[b] : arr[e];
		st[si].sum = arr[b];// +arr[e];
	}
	else{
		long long mid = b + e >> 1;
		construct(arr, b, mid, si << 1);
		construct(arr, mid + 1, e, si << 1 | 1);
		update(st[si], st[si << 1], st[si << 1 | 1]);
	}
}

void modify(long long ss, long long se, long long i, long long x, long long si)
{
	if (ss > i || se < i) return;
	else if (ss == i && se == i){
		st[si].max0 = x;
		st[si].sum = x;
	}
	else{
		long long mid = ss + se >> 1;
		modify(ss, mid, i, x, si << 1);
		modify(mid + 1, se, i, x, si << 1 | 1);
		update(st[si], st[si << 1], st[si << 1 | 1]);
	}
}


node querry(long long ss, long long se, long long l, long long r, long long si)
{
	if (ss >= l && se <= r){
		return st[si];
	}
	else{
		node temp;
		temp.sum = 0;
		temp.max0 = -1;
		temp.max1 = 0;
		long long mid = ss + se >> 1;
		//cout << "M:" << mid << " ";
		if (r <= mid) temp = querry(ss, mid, l, r, si << 1);
		else if (l > mid) temp = querry(mid + 1, se, l, r, si << 1 | 1);
		else{
			update(temp, querry(ss, mid, l, r, si << 1), querry(mid+1, se, l, r, si << 1 | 1));
		}
		return temp;
	}
}

inline long long next_int() {
	long long n = 0;
	char c = getchar_unlocked();
	while (!('0' <= c && c <= '9')) {
		c = getchar_unlocked();
	}
	while ('0' <= c && c <= '9') {
		n = n * 10 + c - '0';
		c = getchar_unlocked();
	}
	return n;
}

int main()
{
	long long N, Q;
	cin >> N;
	for (long long i = 0; i < N; i++)
	{
		arr[i] = next_int();
	}
	cin >> Q;
	construct(arr, 0, N - 1, 1);
	while (Q--) {
		char a;
		a = getchar_unlocked();
		long long x = next_int();
		long long y = next_int();
		if (a == 'U') {
			modify(0, N - 1, x - 1, y, 1);
		}
		else {
			printf("%lld\n", querry(0, N - 1, x - 1, y - 1, 1).sum);
		}
	}
	return 0;
}
