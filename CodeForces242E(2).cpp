/**
  原网站还无法提交，暂不知此做法的正确性
  不过，本地写了个暴力程序对拍此程序 n min，无错误样例
  当然，拿这个程序提交 CF242E 的题目还是可以 AC 的
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=3e5+50;

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
    for(int i=0;i < 25;++i)
        seg[pos].bit[i]=seg[ls(pos)].bit[i]+seg[rs(pos)].bit[i];
}
void build(int l,int r,int pos)
{
    seg[pos].l=l;
    seg[pos].r=r;
    mem(seg[pos].lazy,-1);

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
void work(int pos,int i,int val,int laz)///更新pos节点的bit[i],lazy[i]
{
    seg[pos].bit[i]=val;
    seg[pos].lazy[i]=laz;
}
void pushDown(int pos)
{
    for(int i=0;i < 25;++i)
    {
        ///分类讨论pos的lazy[i]
        if(seg[pos].lazy[i] == 0)
        {
            work(ls(pos),i,0,0);
            work(rs(pos),i,0,0);
        }
        else if(seg[pos].lazy[i] == 1)
        {
            work(ls(pos),i,seg[ls(pos)].len(),1);
            work(rs(pos),i,seg[rs(pos)].len(),1);
        }
        else if(seg[pos].lazy[i] == 2)
        {
            ///seg[pos].lazy[i] == 2 时，分类讨论左右儿子节点的lazy[i]
            if(seg[ls(pos)].lazy[i] == -1)///之前无操作，反转
                work(ls(pos),i,seg[ls(pos)].len()-seg[ls(pos)].bit[i],2);
            else if(seg[ls(pos)].lazy[i] == 0)///&0^1 = 1
                work(ls(pos),i,seg[ls(pos)].len(),1);
            else if(seg[ls(pos)].lazy[i] == 1)///|1^1 = 0
                work(ls(pos),i,0,0);
            else if(seg[ls(pos)].lazy[i] == 2)///^1^1 = 无操作
                work(ls(pos),i,seg[ls(pos)].len()-seg[ls(pos)].bit[i],-1);

            ///分类同ls(pos)
            if(seg[rs(pos)].lazy[i] == -1)
                work(rs(pos),i,seg[rs(pos)].len()-seg[rs(pos)].bit[i],2);
            else if(seg[rs(pos)].lazy[i] == 0)
                work(rs(pos),i,seg[rs(pos)].len(),1);
            else if(seg[rs(pos)].lazy[i] == 1)
                work(rs(pos),i,0,0);
            else if(seg[rs(pos)].lazy[i] == 2)
                work(rs(pos),i,seg[rs(pos)].len()-seg[rs(pos)].bit[i],-1);
        }
        seg[pos].lazy[i]=-1;
    }
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
int op;
void update(int l,int r,int pos,int x)
{
    if(seg[pos].l == l && seg[pos].r == r)
    {
        for(int i=0;i < 25;++i)
        {
            if(op == 2 && (x>>i&1))
            {
                if(seg[pos].lazy[i] == -1)///之前无操作
                    work(pos,i,seg[pos].len()-seg[pos].bit[i],2);
                else if(seg[pos].lazy[i] == 0)///之前有 &0 操作，^1 后相当于 |1 操作
                    work(pos,i,seg[pos].len(),1);
                else if(seg[pos].lazy[i] == 1)///之前有 |1 操作，^1 后相当于 &0 操作
                    work(pos,i,0,0);
                else if(seg[pos].lazy[i] == 2)///^1^1 = -1(无操作)
                    work(pos,i,seg[pos].len()-seg[pos].bit[i],-1);
            }
            if(op == 3 && (x>>i&1))///|1 = 1
                work(pos,i,seg[pos].len(),1);
            if(op == 4 && !(x>>i&1))///&0 = 0
                work(pos,i,0,0);
        }

        return ;
    }
    pushDown(pos);

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
    pushUp(pos);
}
void Solve()
{
    build(1,n,1);

    while(m--)
    {
        int l,r,x;
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
