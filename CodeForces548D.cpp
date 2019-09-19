#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+50;

int n;
struct Data
{
    int h;
    int len;
    bool operator < (const Data &obj)const
    {
        return h > obj.h;
    }
}a[maxn];
int L[maxn];
int R[maxn];
stack<int >sta;

void Work()
{
    while(!sta.empty())
        sta.pop();
    for(int i=1;i <= n;++i)
    {
        while(!sta.empty() && a[sta.top()].h >= a[i].h)
            sta.pop();
        L[i]=sta.empty() ? 1:sta.top()+1;
        sta.push(i);
    }
    while(!sta.empty())
        sta.pop();
    for(int i=n;i >= 1;--i)
    {
        while(!sta.empty() && a[sta.top()].h >= a[i].h)
            sta.pop();
        R[i]=sta.empty() ? n:sta.top()-1;
        sta.push(i);
    }
}
void Solve()
{
    Work();
    for(int i=1;i <= n;++i)
        a[i].len=R[i]-L[i]+1;
    sort(a+1,a+n+1);

    int len=1;
    for(int i=1;i <= n && len <= n;++i)
        for(int j=len;j <= a[i].len && len <= n;++j,++len)
            printf("%d%c",a[i].h,len == n ? '\n':' ');
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i <= n;++i)
        scanf("%d",a+i);
    Solve();

    return 0;
}
