#include<iostream>
//author: Propk

using namespace std;
class stacks{
private:
    char arr[3000];
    int head;
public:
    stacks(){head = 0;}
    bool Stack_Empty();
    void Push(char);
    void Print();
    void Clear();
    char Pop();
};

void stacks::Clear()
{
    head = 0;
}
bool stacks::Stack_Empty()
{
    if(head == 0) return true;
    else return false;
}
char stacks::Pop()
{
    if(Stack_Empty() == 1) {throw exception();}
    else{
        head--;
        return arr[head];
    }
}

void stacks::Print()
{
    for(int i = 0; i<head; i++)
        cout<<arr[i];
    cout<<endl;
}
void stacks::Push(char x)
{
    arr[head] = x;
    head++;
}
int main()
{
    char str[2101];
    int indexv = 1;
    stacks s;
    cin>>str;
    while(str[0] != '-')
    {
        int i = 0, j = 0, count1 = 0, count2 = 0;
        char ch;
        //char test[2101], head = 0;
        while(str[i]!= '\0')
        {
            if(str[i] == '{') count1++;
            else count2++;

            if(s.Stack_Empty()==1) { s.Push(str[i]); }
            else
            {
               ch = s.Pop();
               if(ch == '{' && str[i] == '}') { count1--; count2--;}
               else
               {
                 s.Push(ch);
                 s.Push(str[i]);
               }
            }
             i++;
        }
        int ans;

        if( count1==0) ans = count2/2;
        else if (count2==0) ans = count1/2;
        else if((count1%2) ==0) ans = (count1+ count2)/2;
        else ans = (count1+count2 - 2)/2+2;
        //s.Print();
        s.Clear();
        cout<<indexv++<<". "<<ans<<endl;
        cin>>str;
    }

    return 0;
}
