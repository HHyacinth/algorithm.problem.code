#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e3+50;
const int MOD=1e9+7;

int n;
ll k;
ll a[maxn];

int Solve()
{
    int ans=0;
    sort(a+1,a+n+1);
    for(int i=1;i <= n;++i)
    {
        while(k*2 < a[i])
        {
            ans++;
            k *= 2;///去其他评测系统解决困难为 k*2 的题目
        }
        k=max(k,a[i]);
    }
    return ans;
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    scanf("%d%lld",&n,&k);
    for(int i=1;i <= n;++i)
        scanf("%lld",a+i);
        
    printf("%d\n",Solve());
    return 0;
}
