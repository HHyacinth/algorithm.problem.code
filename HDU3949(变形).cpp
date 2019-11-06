#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=10000+50;

int n,m;
ll a[maxn];
ll base[maxn][70];
int p[maxn][70];

void Insert(int pos,ll x,int k)
{
    for(int i=60;i >= 0;--i)
    {
        if(x>>i&1)
        {
            if(!base[k][i])
            {
                base[k][i]=x;
                p[k][i]=pos;
                return ;
            }
            else if(pos > p[k][i])
            {
                swap(pos,p[k][i]);
                swap(x,base[k][i]);
            }
            x ^= base[k][i];
        }
    }
}

vector<ll >th;
ll tmp[70];
void reBuild(int l,int r)
{
    th.clear();
    mem(tmp,0);
    for(int i=0;i <= 60;++i)///找到[l,r]的基底
        if(p[r][i] >= l)
            tmp[i]=base[r][i];

    for(int i=60;i >= 0;--i)///重构线性基
        for(int j=i-1;j >= 0;--j)
            if(tmp[i]>>j&1)
                tmp[i] ^= tmp[j];

    for(int i=0;i <= 60;++i)
        if(tmp[i])
            th.push_back(tmp[i]);
}
ll Kth(int l,int r,ll k)///求解区间[l,r]异或第k小
{
    reBuild(l,r);///重构[l,r]的th
    int siz=th.size();
    if(siz != (r-l+1))///判断是否存在几个数异或和为0的情况，也就是判断线性基是否为满秩
        k--;
    if(k >= (1ll<<siz))
        return -1;

    ll ans=0;
    for(int i=0;i < siz;++i)
        if(k>>i&1)
            ans ^= th[i];
    return ans;
}
void Solve()
{
    mem(base[0],0);
    for(int i=1;i <= n;++i)
    {
        memcpy(base[i],base[i-1],sizeof(base[i-1]));
        memcpy(p[i],p[i-1],sizeof(p[i-1]));

        Insert(i,a[i],i);
    }

    scanf("%d",&m);
    while(m--)
    {
        int l,r;
        ll k;
        scanf("%d%d",&l,&r);
        scanf("%lld\n",&k);

        printf("%lld\n",Kth(l,r,k));
    }
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
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
