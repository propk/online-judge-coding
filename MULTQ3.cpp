#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
using namespace std;
struct node{
	int o, t, z;
	node() :
		o(0), t(0), z(1) {
	}
};

node st[100009];
int flag[100009];
inline void update(node &p, const node &ch1,const node &ch2)
{
	p.z = ch1.z + ch2.z;
	p.o = ch1.o + ch2.o;
	p.t = ch1.t + ch2.t;
}

void construct(int b, int e, int si)
{
	if (b == e)
	{
		st[si].z = 1;
		st[si].o = 0;
		st[si].t = 0;
	}
	else{
		int mid = b + e >> 1;
		construct(b, mid, si << 1);
		construct(mid + 1, e, si << 1 | 1);
		update(st[si], st[si << 1], st[si << 1 | 1]);
	}
}

void reload(int si)
{
	if (flag[si] == 0) return;
	else
	{
		flag[si << 1] += flag[si];
		if (flag[si << 1] >= 3) 
			flag[si << 1] -= 3;
		flag[si << 1 | 1] += flag[si];
		if (flag[si << 1 | 1] >= 3)
			flag[si << 1 | 1] -= 3;
		while (flag[si] > 0){
			int temp = st[si].t;
			st[si].t = st[si].o;
			st[si].o = st[si].z;
			st[si].z = temp;
			flag[si]--;
		}
	}
}

void modify(int ss, int se, int l, int r, int si)
{
	reload(si);
	if (ss > r || se < l) return;
	else if (ss >= l && se <= r){
		flag[si] += 1;
		if (flag[si] >=3) flag[si] -= 3;
		reload(si);
	}
	else{
		int mid = ss + se >> 1;
		modify(ss, mid, l, r, si << 1);
		modify(mid + 1, se, l, r, si << 1 | 1);
		update(st[si], st[si << 1], st[si << 1 | 1]);
	}
}


node querry(int ss, int se, int l, int r, int si)
{
	reload(si);
	if(ss >= l && se <= r){
		return st[si];
	}
	else{
		node temp;
		int mid = ss + se >> 1;
		if (r <= mid) temp = querry(ss, mid, l, r, si << 1);
		else if (l > mid) temp = querry(mid + 1, se, l, r, si << 1 | 1);
		else{
			update(temp, querry(ss, mid, l, r, si << 1), querry(mid + 1, se, l, r, si << 1 | 1));
		}
		return temp;
	}
}

inline int next_int() {
	int n = 0;
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

int main() {
	int N = next_int();
	int Q = next_int();
	construct(0, N-1, 1);
	while (Q--) {
		int a = next_int();
		int b = next_int();
		int c = next_int();
		if (a) {
			printf("%d\n", querry(0, N - 1, b, c, 1).z);
		}
		else {
			modify(0, N - 1, b, c, 1);
		}
	}
	return 0;
}
