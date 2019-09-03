#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define INFll 0x3f3f3f3f3f3f3f3f
#define ll long long
#define ul unsigned long long
#define pii pair<int ,int >
#define pll pair<ll , ll >
#define pb(x) push_back(x)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define GCD(a,b) __gcd(a,b)
#define PI acos(-1)
#define mem(a,b) memset(a,b,sizeof(a))
#define endl '\n'
#define isLeap(x) (x%4==0&&x%100!=0||x%400==0)
#define Close() std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
const int day[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},
                      {0,31,29,31,30,31,30,31,31,30,31,30,31}/**leap*/};
const int maxn=1e5+50;

int a,b,m;

int getPhi(int x)
{
    int ans=1;
    for(int i=2;i*i <= x;++i)
    {
        if(x%i == 0)
        {
            ans *= i-1;
            x /= i;
            while(x%i == 0)
            {
                ans *= i;
                x /= i;
            }
        }
    }
    if(x > 1)
        ans *= x-1;
    return ans;
}
ll modulo(ll x,ll mod)
{
    return x > mod ? x%mod+mod:x;
}
ll qPow(ll a,ll b,ll mod)
{
    ll ans=1;
    for(;b;b>>=1)
    {
        if(b&1)
            ans=modulo(ans*a,mod);
        a=modulo(a*a,mod);
    }
    return ans;
}
int Calc(int a,int b,int p)///b个a的组成的幂对p取模
{
    if(p == 1 || a == 1 || b == 0)
        return 1;

    int t=getPhi(p);
    return qPow(a,Calc(a,b-1,t),p);
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contestOut","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&a,&b,&m);
        printf("%d\n",Calc(a,b,m)%m);
    }
    return 0;
}
