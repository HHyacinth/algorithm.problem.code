#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll L,R,S;
int cnt;
ll a[20];

int Calc()
{
    int ans=0;
    for(int i=1;i <= cnt;++i)
    {
        ll now=0;
        for(int j=i;j <= cnt;++j)
        {
            now ^= a[j];
            if(now <= S)
                ans=max(ans,j-i+1);
        }
    }
    return ans;
}
ll Solve()
{
    cnt=0;
    if(R-L+1 <= 10)
    {
        for(ll i=L;i <= R;++i)
            a[++cnt]=i;
        ll ans=Calc();
        return ans == 0 ? -1:ans;
    }

    ll l=L;
    ll r=R;
    for(;(l&1)+(l>>1&1) != 0;l++);
    for(;(r&1)+(r>>1&1) != 2;r--);

    ll ans=r-l+1;
    for(ll i=L;i < l;++i)
        a[++cnt]=i;
    for(ll i=r+1;i <= R;++i)
        a[++cnt]=i;

    return ans+Calc();
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld%lld",&L,&R,&S);
        printf("%lld\n",Solve());
    }
    return 0;
}
