#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=5e5+50;

int n,k;
int a[maxn];
ll sum;

bool CheckF(int mid)
{
    ll need=0;
    for(int i=1;i <= n;++i)
        if(a[i] > mid)
            need += a[i]-mid;
    return need <= k ? true:false;
}
int f()///求解水多的水塘最少能有多少水
{
    int ave=(sum+n-1)/n;///保证最少有 ave L 水，需向上取整
    int l=ave-1,r=(int)1e9+1;
    while(r-l > 1)
    {
        int mid=l+((r-l)>>1);
        if(CheckF(mid))
            r=mid;
        else
            l=mid;
    }
    return r;
}
bool CheckG(int mid)
{
    ll need=0;
    for(int i=1;i <= n;++i)
        if(a[i] < mid)
            need += mid-a[i];

    return need <= k ? true:false;
}
int g()///求解水少的水塘最多能有多少水
{
    int ave=sum/n;///保证最多有 ave L 水
    int l=0,r=ave+1;
    while(r-l > 1)
    {
        int mid=l+((r-l)>>1);
        if(CheckG(mid))
            l=mid;
        else
            r=mid;
    }
    return l;
}
int Solve()
{
    int Max=f();
    int Min=g();

    return Max-Min;
}
int main()
{
//    freopen("C:\\Users\\14685\\Desktop\\C++workspace\\in&out\\contest","r",stdin);
    while(~scanf("%d%d",&n,&k))
    {
        sum=0;
        for(int i=1;i <= n;++i)
        {
            scanf("%d",a+i);
            sum += a[i];
        }

        printf("%d\n",Solve());
    }
    return 0;
}
