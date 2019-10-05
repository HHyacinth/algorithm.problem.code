#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
const int maxn=2e5+50;

int n;
int c[maxn],d[maxn];

int Div(int rat)
{
    return rat >= 1900 ? 1:2;
}
int Calc(int rat,int k)
{
    for(int i=k-1;i >= 1;--i)
        rat -= c[i];

    for(int i=1;i <= n;++i)
    {
        if(Div(rat) != d[i])
            return -INF;
        rat += c[i];
    }
    return rat;
}
void Solve()
{
    if(count(d+1,d+n+1,1) == n)///情况（1）
        return puts("Infinity"),void(0);

    for(int i=1;i < n;++i)
    {
        if(d[i] == d[i+1])
            continue;

        ///情况（2）
        for(int rat=2000;rat >= 1799;rat--)
        {
            int ans=Calc(rat,i);
            if(ans != -INF)
                return printf("%d\n",ans),void(0);
        }
        return puts("Impossible"),void(0);
    }

    ///情况（3）
    int s=1;
    int rat=1899;
    int sum=0;
    int Max=0;
    for(int i=1;i < n;++i)
    {
        sum += c[i];
        if(sum >= 0 && sum >= Max)
        {
            Max=sum;
            s=i+1;
        }
    }
    for(int i=s;i <= n;++i)
        rat += c[i];
    printf("%d\n",rat);
}
int main()
{
//    freopen("C:\\Users\\14685\\Desktop\\C++workspace\\in&out\\contest","r",stdin);
    scanf("%d",&n);
    for(int i=1;i <= n;++i)
        scanf("%d%d",c+i,d+i);

    Solve();

    return 0;
}
