#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define MAX(a,b,c) max(a,max(b,c))
const int maxn=5e4+50;

int n,m;
struct Seg
{
    int l,r;
    int lsum,rsum,sum;
    int lazy;
    int mid(){return l+((r-l)>>1);}
    int len(){return r-l+1;}
}seg[maxn<<2];

void pushUp(int pos)
{
    seg[pos].lsum=seg[ls(pos)].lsum;
    seg[pos].rsum=seg[rs(pos)].rsum;

    if(seg[ls(pos)].lsum == seg[ls(pos)].len())
        seg[pos].lsum += seg[rs(pos)].lsum;
    if(seg[rs(pos)].rsum == seg[rs(pos)].len())
        seg[pos].rsum += seg[ls(pos)].rsum;

    seg[pos].sum=MAX(seg[ls(pos)].sum,
                     seg[rs(pos)].sum,
                     seg[ls(pos)].rsum+seg[rs(pos)].lsum);
}
void pushDown(int pos)
{
    int &lazy=seg[pos].lazy;

    if(lazy == 0)
    {
        seg[ls(pos)].lsum=seg[ls(pos)].rsum=seg[ls(pos)].sum=seg[ls(pos)].len();
        seg[rs(pos)].lsum=seg[rs(pos)].rsum=seg[rs(pos)].sum=seg[rs(pos)].len();
        seg[ls(pos)].lazy=seg[rs(pos)].lazy=lazy;
    }
    else if(lazy == 1)
    {
        seg[ls(pos)].lsum=seg[ls(pos)].rsum=seg[ls(pos)].sum=0;
        seg[rs(pos)].lsum=seg[rs(pos)].rsum=seg[rs(pos)].sum=0;
        seg[ls(pos)].lazy=seg[rs(pos)].lazy=lazy;
    }
    lazy=-1;
}
void build(int l,int r,int pos)
{
    seg[pos]={l,r,r-l+1,r-l+1,r-l+1,-1};

    if(l == r)
        return ;

    int mid=l+((r-l)>>1);
    build(l,mid,ls(pos));
    build(mid+1,r,rs(pos));
}
int query(int pos,int x)
{
    if(seg[pos].l == seg[pos].r)
        return seg[pos].l;

    pushDown(pos);

    int mid=seg[pos].mid();
    if(seg[ls(pos)].sum >= x)
        return query(ls(pos),x);
    else if(seg[ls(pos)].rsum+seg[rs(pos)].lsum >= x)
        return seg[ls(pos)].r+1-seg[ls(pos)].rsum;
    else
        return query(rs(pos),x);
}
void update(int pos,int l,int r,int val)
{
    if(seg[pos].l == l && seg[pos].r == r)
    {
        seg[pos].lazy=val;
        if(val == 1)
            seg[pos].lsum=seg[pos].rsum=seg[pos].sum=0;
        else
            seg[pos].lsum=seg[pos].rsum=seg[pos].sum=seg[pos].len();
        return ;
    }
    pushDown(pos);

    int mid=seg[pos].mid();
    if(r <= mid)
        update(ls(pos),l,r,val);
    else if(l > mid)
        update(rs(pos),l,r,val);
    else
    {
        update(ls(pos),l,mid,val);
        update(rs(pos),mid+1,r,val);
    }
    pushUp(pos);
}
void Solve()
{
    build(1,n,1);

    while(m--)
    {
        int op;
        scanf("%d",&op);
        if(op == 1)
        {
            int x;
            scanf("%d",&x);

            int ans=0;
            if(seg[1].sum >= x)///先判断是否有这么多连续的空房间
                ans=query(1,x);
            printf("%d\n",ans);

            if(ans)
                update(1,ans,ans+x-1,1);
        }
        else
        {
            int x,y;
            scanf("%d%d",&x,&y);
            update(1,x,x+y-1,0);
        }
    }
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    scanf("%d%d",&n,&m);
    Solve();

    return 0;
}
