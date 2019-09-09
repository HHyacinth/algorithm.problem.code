#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+50;

int n,m;
int w[maxn];

struct RMQ
{
    int lb[maxn];
    int dp[maxn][30];
    void ST()
    {
        lb[0]=-1;
        for(int i=1;i <= n;++i)
        {
            dp[i][0]=w[i];
            lb[i]=lb[i-1]+((i&(i-1)) == 0 ? 1:0);
        }

        for(int k=1;k <= lb[n];++k)
            for(int i=1;i+(1<<k)-1 <= n;++i)
                if(dp[i][k-1] > dp[i+(1<<(k-1))][k-1])
                    dp[i][k]=dp[i][k-1];
                else
                    dp[i][k]=dp[i+(1<<(k-1))][k-1];
    }
    int rmq(int a,int b)
    {
        if(a > b)
            swap(a,b);
        int k=lb[b-a+1];
        return max(dp[a][k],dp[b-(1<<k)+1][k]);
    }
}_st;
void Solve()
{
    _st.ST();

    for(int i=1;i < n;++i)
    {
        if(_st.rmq(i+1,n) < w[i]+m)
            printf("-1 ");
        else
        {
            int l=i+1;
            int r=n;
            while(r-l > 1)
            {
                int mid=l+((r-l)>>1);
                ///优先判断[mid,r]
                if(_st.rmq(mid,r) >= w[i]+m)
                    l=mid;
                else
                    r=mid-1;
            }
            ///答案区间为[l,r]，因此必须得判断r是否为可行解
            printf("%d ",w[r] >= w[i]+m ? r-i-1:l-i-1);
        }
    }
    puts("-1");
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i <= n;++i)
        scanf("%d",w+i);

    Solve();

    return 0;
}
