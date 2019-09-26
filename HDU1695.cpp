#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+50;

int a,b,c,d,k;
int mu[maxn];
vector<int >prime;
bool isPrime[maxn];

void preCalc(int n)
{
    mem(isPrime,true);
    isPrime[1]=false;
    prime.clear();
    mu[1]=1;

    for(int i=2;i < n;++i)
    {
        if(isPrime[i])
        {
            mu[i]=-1;
            prime.push_back(i);
        }

        int tmp;
        for(int j=0;j < prime.size() && (tmp=i*prime[j]) < n;++j)
        {
            isPrime[tmp]=false;
            mu[tmp]=-mu[i];

            if(i%prime[j] == 0)
            {
                mu[tmp]=0;
                break;
            }
        }
    }
}
ll Calc(ll n,ll m,ll k)
{
    if(k == 0)///特判k=0的情况
        return 0;
    
    int x=min(n,m)/k;
    ll ans=0;
    for(int i=1;i <= x;++i)
        ans += mu[i]*(n/(i*k))*(m/(i*k));
    return ans;
}
int main()
{
    preCalc(maxn);

    int T;
    scanf("%d",&T);
    for(int kase=1;kase <= T;++kase)
    {
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);

        int ans=Calc(b,d,k)-Calc(min(b,d),min(b,d),k)/2;

        printf("Case %d: %lld\n",kase,ans);
    }
}
