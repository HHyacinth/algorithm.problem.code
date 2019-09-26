#include<bits/stdc++.h>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
#define ll long long
const int maxn=10000+50;

int n,m;
ll a[maxn];
ll base[70];
vector<ll >th;

void Insert(ll x)
{
    for(int i=60;i >= 0;--i)
    {
        if(x>>i&1)
        {
            if(!base[i])
            {
                base[i]=x;
                return ;
            }
            x ^= base[i];
        }
    }
}
vector<ll >th;
void reBuild()///重构线性基
{
    th.clear();
    for(int i=60;i >= 0;--i)
        for(int j=i-1;j >= 0;--j)
            if(base[i]>>j&1)
                base[i] ^= base[j];
    for(int i=0;i <= 60;++i)
        if(base[i])
            th.push_back(base[i]);
}
ll Kth(ll k)
{
    int siz=th.size();
    if(siz != n)///判断是否存在异或为0的情况
        k--;
    if(k >= (1ll<<siz))///判断是否可以组成这么多数
        return -1;

    ll ans=0;
    for(int i=0;i < siz;++i)
        if(k>>i&1)
            ans ^= th[i];
    return ans;

}
void Solve()
{
    mem(base,0);

    for(int i=1;i <= n;++i)
        Insert(a[i]);
    reBuild();

    scanf("%d",&m);
    while(m--)
    {
        ll k;
        scanf("%lld",&k);

        printf("%lld\n",Kth(k));
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    for(int kase=1;kase <= T;++kase)
    {
        scanf("%d",&n);
        for(int i=1;i <= n;++i)
            scanf("%lld",a+i);

        printf("Case #%d:\n",kase);
        Solve();
    }
    return 0;
}
