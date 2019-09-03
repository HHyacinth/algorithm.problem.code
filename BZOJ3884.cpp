#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long

int p;

ll qPow(ll a,ll b,ll mod)///a^b%mod
{
    ll ans=1;
    a %= mod;
    while(b)
    {
        if(b&1)
            ans=ans*a%mod;

        a=a*a%mod;
        b >>= 1;
    }
    return ans;
}
int getPhi(int x)
{
    int ans=1;
    for(int i=2;i*i <= x;++i)///质因子分解
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
int Calc(int a,int x,int p)
{
    if(p == 1)
        return 1;

    int t=getPhi(p);
    return qPow(a,Calc(a,INF,t)+t,p);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&p);
        printf("%d\n",Calc(2,INF,p)%p);
    }
    return 0;
}
