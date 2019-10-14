#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long
const int maxn=1e3+50;

int n,k;
double x;
struct Data
{
    int a,b;
    bool operator < (const Data &obj)const
    {
        return a-x*b > obj.a-x*obj.b;
    }
}v[maxn];

bool Check(double mid)
{
    x=mid;
    sort(v+1,v+n+1);

    double ans1=0;
    double ans2=0;
    for(int i=1;i <= n-k;++i)
    {
        ans1 += v[i].a;
        ans2 += v[i].b;
    }
    return ans1/ans2 >= x ? true:false;
}
int Solve()
{
    double l=0,r=1;
    for(int i=1;i <= 100;++i)///挑战程序设计竞赛中关于高精二分技巧
    {
        double mid=(l+r)/2;
        if(Check(mid))
            l=mid;
        else
            r=mid;
    }

    return (int)(l*100+0.5);
}
int main()
{
    while(~scanf("%d%d",&n,&k) && (n+k))
    {
        for(int i=1;i <= n;++i)
            scanf("%d",&v[i].a);
        for(int i=1;i <= n;++i)
            scanf("%d",&v[i].b);

        printf("%d\n",Solve());
    }
    return 0;
}
