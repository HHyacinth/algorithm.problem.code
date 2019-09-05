#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+50;

int n,m;
int a[maxn];
int num;
int rt[maxn];
struct Seg
{
    int ls,rs;
    int val;
}seg[maxn*20];

int build(int l,int r,int pos)
{
    pos=++num;
    if(l == r)
    {
        seg[pos].val=a[l];
        return pos;
    }

    int mid=(l+r)>>1;
    seg[pos].ls=build(l,mid,pos);
    seg[pos].rs=build(mid+1,r,pos);
    return pos;
}
int x,y;
int clone(int pos)
{
    seg[++num]=seg[pos];
    return num;
}
int update(int l,int r,int pos)
{
    pos=clone(pos);
    if(l == r)
    {
        seg[pos].val=y;
        return pos;
    }

    int mid=(l+r)>>1;
    if(x <= mid)
        seg[pos].ls=update(l,mid,seg[pos].ls);
    else
        seg[pos].rs=update(mid+1,r,seg[pos].rs);
    return pos;
}
int query(int l,int r,int pos)
{
    if(l == r)
        return seg[pos].val;

    int mid=(l+r)>>1;
    if(x <= mid)
        return query(l,mid,seg[pos].ls);
    else
        return query(mid+1,r,seg[pos].rs);
}
void Solve()
{
    num=0;
    rt[0]=build(1,n,1);

    for(int i=1;i <= m;++i)
    {
        int v,op;
        scanf("%d%d",&v,&op);

        if(op == 1)
        {
            scanf("%d%d",&x,&y);
            rt[i]=update(1,n,rt[v]);
        }
        else
        {
            scanf("%d",&x);
            rt[i]=rt[v];
            printf("%d\n",query(1,n,rt[v]));
        }
    }
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);

    scanf("%d%d",&n,&m);
    for(int i=1;i <= n;++i)
        scanf("%d",a+i);

    Solve();

    return 0;
}
