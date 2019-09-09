#include<bits/stdc++.h>
using namespace std;
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+50;

int n,m;
int a[maxn];
struct Seg
{
    int l,r;
    int bit[25];
    int lazy[25];
    int mid(){return l+((r-l)>>1);}
    int len(){return r-l+1;}
}seg[maxn<<2];

void pushUp(int pos)
{
    ///向上更新，取左右儿子bit[i]的加和即可
    for(int i=0;i < 25;++i)
        seg[pos].bit[i]=seg[ls(pos)].bit[i]+seg[rs(pos)].bit[i];
}
void pushDown(int pos)
{
    for(int i=0;i < 25;++i)
    {
        if(seg[pos].lazy[i])
        {
            seg[ls(pos)].bit[i]=seg[ls(pos)].len()-seg[ls(pos)].bit[i];
            seg[rs(pos)].bit[i]=seg[rs(pos)].len()-seg[rs(pos)].bit[i];

            seg[ls(pos)].lazy[i] ^= 1;
            seg[rs(pos)].lazy[i] ^= 1;
        }
        seg[pos].lazy[i]=0;
    }
}
void build(int l,int r,int pos)
{
    seg[pos].l=l;
    seg[pos].r=r;
    mem(seg[pos].lazy,0);

    if(l == r)
    {
        for(int i=0;i < 25;++i)
            seg[pos].bit[i]=(a[l]>>i)&1;

        return ;
    }

    int mid=l+((r-l)>>1);
    build(l,mid,ls(pos));
    build(mid+1,r,rs(pos));

    pushUp(pos);
}
ll query(int l,int r,int pos)
{
    if(seg[pos].l == l && seg[pos].r == r)
    {
        ll ans=0;
        for(int i=0;i < 25;++i)
            ans += 1ll*(1<<i)*seg[pos].bit[i];
        return ans;
    }
    pushDown(pos);

    int mid=seg[pos].mid();
    if(r <= mid)
        return query(l,r,ls(pos));
    else if(l > mid)
        return query(l,r,rs(pos));
    else
        return query(l,mid,ls(pos))+query(mid+1,r,rs(pos));
}
void update(int l,int r,int pos,int x)
{
    if(seg[pos].l == l && seg[pos].r == r)
    {
        for(int i=0;i < 25;++i)
        {
            if(x>>i&1)
            {
                seg[pos].lazy[i] ^= 1;
                seg[pos].bit[i]=seg[pos].len()-seg[pos].bit[i];///反转第i位的1的个数
            }
        }
        return ;
    }
    pushDown(pos);///向下传递懒惰标记

    int mid=seg[pos].mid();
    if(r <= mid)
        update(l,r,ls(pos),x);
    else if(l > mid)
        update(l,r,rs(pos),x);
    else
    {
        update(l,mid,ls(pos),x);
        update(mid+1,r,rs(pos),x);
    }
    pushUp(pos);///记得pushUp()
}
void Solve()
{
    build(1,n,1);

    while(m--)
    {
        int op,l,r,x;
        scanf("%d%d%d",&op,&l,&r);
        if(op == 1)
            printf("%lld\n",query(l,r,1));
        else
        {
            scanf("%d",&x);
            update(l,r,1,x);
        }
    }
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    scanf("%d",&n);
    for(int i=1;i <= n;++i)
        scanf("%d",a+i);
    scanf("%d",&m);

    Solve();

    return 0;
}
