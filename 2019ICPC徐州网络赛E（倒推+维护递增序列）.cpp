#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+50;

int n,m;
int w[maxn];
int ans[maxn];
int a[maxn];
int b[maxn];

void Solve()
{
    int k=1;
    ans[n]=-1;
    a[k]=w[n];
    b[k++]=n;

    for(int i=n-1;i >= 1;--i)
    {
        int t=lower_bound(a+1,a+k,w[i]+m)-a;
        if(t == k)
            ans[i]=-1;
        else
            ans[i]=b[t]-i-1;

        if(w[i] > a[k-1])
        {
            a[k]=w[i];
            b[k++]=i;
        }
    }
    for(int i=1;i <= n;++i)
        printf("%d%c",ans[i],i == n ? '\n':' ');
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i <= n;++i)
        scanf("%d",w+i);

    Solve();

    return 0;
}
