#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INFll 0x3f3f3f3f3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e6+50;

int n,m;
ll a[maxn];
ll dp[maxn];
ll Max[maxn];

ll Solve()
{
    mem(Max,0);
    for(int i=1;i <= m;++i)
    {
        dp[i-1]=-INFll;///i-1个数不能划分成i段，所以将dp[i-1]赋值为-INFll
        for(int j=i;j <= n-m+i;++j)
            dp[j]=max(dp[j-1],Max[j-1])+a[j];
            
        Max[i-1]=-INFll;///i-1个数不能划分成i段，所以将Max[i-1]赋值为-INFll
        for(int j=i;j <= n-m+i;++j)
            Max[j]=max(Max[j-1],dp[j]);
    }
    return *max_element(dp+m,dp+n+1);
}
int main()
{
    while(~scanf("%d%d",&m,&n))
    {
        for(int i=1;i <= n;++i)
            scanf("%lld",a+i);
        printf("%lld\n",Solve());
    }

    return 0;
}
