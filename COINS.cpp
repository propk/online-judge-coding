#include<iostream>
#include<map>
//author: Propk
//Basic Dynamic Programming

using namespace std;
unsigned int max(unsigned int a,unsigned int b)
{
    if(a>=b) return a;
    else return b;
}

typedef map<int , unsigned int> mymap ;
mymap k;
unsigned int TOP_DOWN(int n)
{
    unsigned int q;
    if(n == 0) return 0;
    else if(!(k.find(n) == k.end())) return k[n];
    else {
            q = max(n, TOP_DOWN(n/2) + TOP_DOWN(n/3) + TOP_DOWN(n/4));
        k[n] = q;
        return q;
    }
}
int main()
{
   int n, t = 10;
   while(t--)
   {
       cin>>n;
       cout<<TOP_DOWN(n)<<endl;
   }
    return 0;
}
