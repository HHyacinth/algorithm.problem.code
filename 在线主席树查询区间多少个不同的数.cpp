#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+50;

int n,m;
int a[maxn];
int last[maxn];
int num;
int rt[maxn];
struct Seg
{
    int l,r;
    int ls,rs;
    int sum;
    int mid(){return l+((r-l)>>1);}
}seg[maxn*40];

int build(int l,int r)
{
    int pos=num++;
    seg[pos].l=l;
    seg[pos].r=r;
    seg[pos].sum=0;

    if(l == r)
        return pos;

    int mid=(l+r)>>1;
    seg[pos].ls=build(l,mid);
    seg[pos].rs=build(mid+1,r);

    return pos;
}
int clone(int pos)
{
    seg[num]=seg[pos];
    return num++;
}
void pushUp(int pos)
{
    seg[pos].sum=seg[seg[pos].ls].sum+seg[seg[pos].rs].sum;
}
int update(int pos,int x,int val)
{
    pos=clone(pos);

    if(seg[pos].l == seg[pos].r)
    {
        seg[pos].sum += val;
        return pos;
    }

    int mid=seg[pos].mid();
    if(x <= mid)
        seg[pos].ls=update(seg[pos].ls,x,val);
    else
        seg[pos].rs=update(seg[pos].rs,x,val);

    pushUp(pos);
    return pos;
}
int query(int pos,int l,int r)
{
    if(seg[pos].l == l && seg[pos].r == r)
        return seg[pos].sum;

    int mid=seg[pos].mid();
    if(r <= mid)
        return query(seg[pos].ls,l,r);
    else if(l > mid)
        return query(seg[pos].rs,l,r);
    else
        return query(seg[pos].ls,l,mid)+query(seg[pos].rs,mid+1,r);
}
void Solve()
{
    num=0;
    rt[0]=build(1,n);
    for(int i=1;i <= n;++i)
    {
        int tmp=rt[i-1];
        if(last[a[i]])
            tmp=update(rt[i-1],last[a[i]],-1);
        rt[i]=update(tmp,i,1);
        last[a[i]]=i;
    }

    scanf("%d",&m);
    while(m--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",query(rt[r],l,r));
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i <= n;++i)
    {
        scanf("%d",a+i);
        last[a[i]]=0;
    }

    Solve();

    return 0;
}
