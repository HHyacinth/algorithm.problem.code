#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=5e4+50;

int n,m;
struct Seg
{
    int l,r;
    ll base[40];
    int mid(){return l+((r-l)>>1);}

    void Insert(ll x)
    {
        for(int i=31;i >= 0;--i)
        {
            if((x>>i)&1)
            {
                if(!base[i])
                {
                    base[i]=x;
                    return ;
                }
                x ^= base[i];
            }
        }
    }
    ll Max()
    {
        ll ans=0;
        for(int i=31;i >= 0;--i)
            ans=max(ans,ans^base[i]);
        return ans;
    }
}seg[maxn<<2];

void build(int l,int r,int pos)
{
    seg[pos]={l,r};
    mem(seg[pos].base,0);

    if(l == r)
        return ;

    int mid=l+((r-l)>>1);
    build(l,mid,ls(pos));
    build(mid+1,r,rs(pos));
}
Seg Merge(Seg a,Seg b)///合并线性基a.base,b.base
{
    Seg ans=a;
    ans.r=b.r;

    for(int i=31;i >= 0;--i)
        if(b.base[i])
            ans.Insert(b.base[i]);

    return ans;
}
void update(int pos,int k,int x)
{
    if(seg[pos].l == seg[pos].r)
    {
        seg[pos].Insert(x);
        return ;
    }

    int mid=seg[pos].mid();
    if(k <= mid)
        update(ls(pos),k,x);
    else
        update(rs(pos),k,x);

    seg[pos].Insert(x);///直接将x插入到pos的base中即可
}
Seg query(int pos,int l,int r)
{
    if(seg[pos].l == l && seg[pos].r == r)
        return seg[pos];

    int mid=seg[pos].mid();
    if(r <= mid)
        return query(ls(pos),l,r);
    else if(l > mid)
        return query(rs(pos),l,r);
    else
        return Merge(query(ls(pos),l,mid),query(rs(pos),mid+1,r));
}
void Solve()
{
    build(1,m,1);

    while(n--)
    {
        int op;
        scanf("%d",&op);
        if(op == 1)
        {
            int k;
            ll x;
            scanf("%d%lld",&k,&x);
            update(1,k,x);
        }
        else
        {
            int l,r;
            scanf("%d%d",&l,&r);
            Seg ans=query(1,l,r);

            printf("%lld\n",ans.Max());
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    Solve();

    return 0;
}
