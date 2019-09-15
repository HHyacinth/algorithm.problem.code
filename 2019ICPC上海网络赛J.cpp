#include<bits/stdc++.h>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
#define ll long long
const int maxn=300*500+50;
const int MOD=1e9+7;

int n;
int a[350];
ll dp[350];
ll b[maxn];

ll Solve()
{
    int sum=0;
    for(int i=1;i <= n;++i)
    {
        sum += a[i];
        dp[i]=0;
    }
    for(int i=1;i <= sum;++i)
        b[i]=0;
    b[0]=1;
    
    sort(a+1,a+n+1);
    
    for(int i=n;i >= 1;--i)
    {
        for(int j=sum;j >= 0;--j)
        {
            if(!b[j])
                continue;
            b[j+a[i]] += b[j];
            b[j+a[i]] %= MOD;
            
            int u=j+a[i];///a[i]作为u中的最小堆石子
            int v=sum-u;
            if(u >= v && u-a[i] <= v)
                dp[i] += b[j];
                
            dp[i] %= MOD;
        }
    }
    ll ans=0;
    for(int i=1;i <= n;++i)
        ans=ans+dp[i];
        
    return ans%MOD;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i <= n;++i)
            scanf("%d",a+i);
            
        printf("%lld\n",Solve());
    }
    return 0;
}
