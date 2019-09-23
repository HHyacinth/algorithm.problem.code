#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&(-x))
const int maxn=1e6+50;

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
int bit[maxn];
void Add(int x,int val)
{
    while(x < maxn)
    {
        bit[x] += val;
        x += lowbit(x);
    }
}
int Sum(int x)
{
    int ans=0;
    while(x > 0)
    {
        ans += bit[x];
        x -= lowbit(x);
    }
    return ans;
}
int last[maxn];
int ans[maxn];

void Solve()
{
    sort(q+1,q+m+1);

    int index=1;
    for(int i=1;i <= m;++i)
    {
        while(index <= q[i].r)
        {
            if(last[a[index]])
                Add(last[a[index]],-1);
            Add(index,1);

            last[a[index]]=index;
            index++;
        }
        ans[q[i].id]=Sum(q[i].r)-Sum(q[i].l-1);
    }
    for(int i=1;i <= m;++i)
        printf("%d\n",ans[i]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i <= n;++i)
    {
        scanf("%d",a+i);
        last[a[i]]=0;
    }
    scanf("%d",&m);
    for(int i=1;i <= m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        q[i]={l,r,i};
    }
    Solve();

    return 0;
}
