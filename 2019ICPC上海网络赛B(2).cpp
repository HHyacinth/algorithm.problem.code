#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+50;

int n,m;
int a[maxn];

int main()
{
    int T;
    scanf("%d",&T);
    for(int kase=1;kase <= T;++kase)
    {
        scanf("%d%d",&n,&m);

        int k=0;
        for(int i=1;i <= m;++i)
        {
            int l,r;
            scanf("%d%d",&l,&r);

            a[++k]=l;
            a[++k]=r+1;
        }
        sort(a+1,a+k+1);

        int ans=0;
        for(int i=1;i <= k;i+=2)
            ans += a[i+1]-a[i];

        printf("Case #%d: %d\n",kase,ans);
    }
}
