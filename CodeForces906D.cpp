#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e5+50;

int n,m,q;
int w[maxn];
map<int ,int >phi;

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
    while(b)
    {
        if(b&1)
            ans=modulo(ans*a,mod);
        a=modulo(a*a,mod);
        b >>= 1;
    }
    return ans;
}
int Calc(int l,int r,int m)
{
    if(l == r)
        return w[l];
    if(m == 1)
        return 1;
    
    ///相比上一个版本，此处并不需要在Calc()后加phi[m]
    ///因为在快速幂中已经处理了
    return qPow(w[l],Calc(l+1,r,phi[m]),m);
}
void Solve()
{
    ///提前预处理出m的φ(m)以及φ(m)的φ(φ(m))
    phi.clear();
    int cur=m;
    while(cur != 1)
    {
        phi[cur]=getPhi(cur);
        cur=phi[cur];
    }

    scanf("%d",&q);
    while(q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",Calc(l,r,m)%m);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i <= n;++i)
        scanf("%d",w+i);

    Solve();

    return 0;
}
