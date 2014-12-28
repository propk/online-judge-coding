#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int max_subarray(int *arr, int n)
{
    int current_sum = 0, best_sum = 0, current_index = -1, best_index= -1, best_end_index = -1, val;
    
    for(int i = 0; i < n; i++)
    {
        val = current_sum + arr[i];
        if(val > 0)
        {
            if(current_sum == 0) current_index = i;
            current_sum = val;
        }
        else current_sum = 0;
        
        if(current_sum > best_sum)
        {
            best_sum = current_sum;
            best_index = current_index;
            best_end_index = i;
        }
    }
    return best_sum;
}    
int main() {
    int t, n;
    cin >> t;
    while(t--)
    {
        cin >> n;
        int a[n], neg = 1, max = -2000000;
        long sum = 0;
        for(int i = 0; i < n; i++)
        {  
            cin >> a[i];
            if(a[i] > 0) { sum += a[i]; neg = 0; }
            if(a[i] > max) max = a[i];
        }
        if(neg == 0) cout<<max_subarray(a, n)<<" "<<sum<<endl;
        else cout<<max<<" "<<max<<endl;
    }
    return 0;
}
