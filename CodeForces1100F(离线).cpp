#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+50;

int n,m;
int a[maxn];
struct Query
{
    int l,r;
    int id;
    bool operator < (const Query &obj)const
    {
        return r < obj.r;
    }
}q[maxn];
int base[20];
int p[20];

void Insert(int pos,int x)
{
    for(int i=20;i >= 0;--i)
    {
        if((x>>i)&1)
        {
            if(!base[i])
            {
                base[i]=x;
                p[i]=pos;
                return ;
            }
            else if(pos > p[i])
            {
                swap(pos,p[i]);
                swap(x,base[i]);
            }
            x ^= base[i];
        }
    }
}
int Max(int l,int r)
{
    int ans=0;
    for(int i=20;i >= 0;--i)
        if(p[i] >= l && p[i] <= r)
            ans=max(ans,ans^base[i]);
    return ans;
}

int ans[maxn];
void Solve()
{
    sort(q+1,q+m+1);

    int index=1;
    for(int i=1;i <= m;++i)
    {
        while(index <= q[i].r)
        {
            Insert(index,a[index]);
            index++;
        }
        ans[q[i].id]=Max(q[i].l,q[i].r);
    }
    for(int i=1;i <= m;++i)
        printf("%d\n",ans[i]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i <= n;++i)
        scanf("%d",a+i);
    scanf("%d",&m);
    for(int i=1;i <= m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        q[i]={l,r,i};
    }
    Solve();
}
