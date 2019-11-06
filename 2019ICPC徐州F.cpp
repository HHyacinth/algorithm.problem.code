#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int ,int >
#define F first
#define S second
const int N=5000;

ll x;
unordered_map<ll ,pii >f;
unordered_map<ll ,int >g;


void Solve()
{
    for(auto it=g.begin();it != g.end();++it)
    {
        ll now=it->F;
        if(f.count(x-now))
        {
            ll a=f[x-now].F;
            ll b=f[x-now].S;
            ll c=it->S;

            printf("%lld %lld %lld\n",a,b,c);
            return ;
        }
    }
    puts("Impossible");
}
void Init()
{
    ll Max=200-(-N)*(-N)*(-N);
    ll Min=-N*N*N;

    int cnt=0;
    for(ll i=-N;i <= N;++i)
        for(ll j=-N;j <= N;++j)
        {
            ll cur=i*i*i+j*j*j;
            if(cur > Max)
                break;

            cnt++;
            if(cur >= Min)
                f[cur]={i,j};
        }
    for(ll i=-N;i <= N;++i)
        g[i*i*i]=i;
}
int main()
{
    Init();

    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&x);
        Solve();
    }
}
