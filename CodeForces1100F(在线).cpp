#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+50;

int n,q;
int a[maxn];
int base[maxn][30];
int p[maxn][30];

void Insert(int pos,int x,int k)
{
    for(int i=20;i >= 0;--i)
    {
        if(x&(1<<i))
        {
            if(!base[k][i])
            {
                base[k][i]=x;
                p[k][i]=pos;
            }
            else if(pos > p[k][i])
            {
                swap(pos,p[k][i]);
                swap(x,base[k][i]);
            }
            x ^= base[k][i];
        }
    }
}
int Max(int l,int r)
{
    int ans=0;
    for(int i=20;i >= 0;--i)
        if(p[r][i] >= l)
            ans=max(ans,ans^base[r][i]);
    return ans;
}
void Solve()
{
    for(int i=1;i <= n;++i)
    {
        memcpy(base[i],base[i-1],sizeof(base[i-1]));
        memcpy(p[i],p[i-1],sizeof(p[i-1]));

        Insert(i,a[i],i);
    }

    while(q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);

        printf("%d\n",Max(l,r));
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i <= n;++i)
        scanf("%d",a+i);
    scanf("%d",&q);

    Solve();

    return 0;
}
