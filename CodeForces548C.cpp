#include<bits/stdc++.h>
using namespace std;
#define GCD(a,b) __gcd(a,b)
#define ll long long

int m;
int h[3];
int a[3];
int x[3];
int y[3];
vector<int >p[3];

void Work(int k)
{
    ll cur=h[k];
    for(int i=1;i <= 2*m;++i)
    {
        cur=(cur*x[k]+y[k])%m;

        if(cur == a[k])
            p[k].push_back(i);
    }
}
void extGCD(ll a,ll b,ll &x,ll &y,ll c)
{
    if(b == 0)
    {
        x=c/a;
        y=0;
        return ;
    }
    extGCD(b,a%b,y,x,c);
    y -= a/b*x;
}
ll Solve()
{
    Work(1);
    Work(2);

    if(p[1].empty() || p[2].empty())///情况（1）
        return -1;
    if(p[1].size() == 1 && p[2].size() == 1)///情况（2）
        return p[1][0] == p[2][0] ? p[1][0]:-1;

    if(p[1].size() == 1)///情况（3）
        return p[1][0] >= p[2][0] && (p[1][0]-p[2][0])%(p[2][1]-p[2][0]) == 0 ? p[1][0]:-1;
    else if(p[2].size() == 1)///情况（4）
        return p[2][0] >= p[1][0] && (p[2][0]-p[1][0])%(p[1][1]-p[1][0]) == 0 ? p[2][0]:-1;

    ///情况（5）
    ll p1=p[1][0];
    ll d1=p[1][1]-p[1][0];
    ll p2=p[2][0];
    ll d2=p[2][1]-p[2][0];
    ll gcd=GCD(d1,d2);

    if((p2-p1)%gcd)
        return -1;

    ll x1,y1;
    extGCD(d1,-d2,x1,y1,p2-p1);

    ///查找最小的操作次数，并满足 x1 >= 0 && y >= 0
    while(x1 >= 0 && y1 >= 0)
    {
        x1 -= d2/gcd;
        y1 -= d1/gcd;
    }
    while(x1 < 0 || y1 < 0)
    {
        x1 += d2/gcd;
        y1 += d1/gcd;
    }

    return x1*d1+p1;
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);

    scanf("%d",&m);
    scanf("%d%d",h+1,a+1);
    scanf("%d%d",x+1,y+1);
    scanf("%d%d",h+2,a+2);
    scanf("%d%d",x+2,y+2);

    printf("%lld\n",Solve());

    return 0;
}
