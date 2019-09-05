#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+50;

int n,m;
int a[maxn];
int b[maxn];
int num;
int rt[maxn];
struct Seg
{
    int ls,rs;
    int sum;
}seg[maxn*20];

int build(int l,int r,int pos)
{
    pos=++num;
    seg[pos].sum=0;

    if(l == r)
        return 0;

    int mid=(l+r)>>1;
    seg[pos].ls=build(l,mid,pos);
    seg[pos].rs=build(mid+1,r,pos);

    return pos;
}
int clone(int pos)
{
    seg[++num]=seg[pos];
    return num;
}
int update(int l,int r,int pos,int x)
{
    pos=clone(pos);
    seg[pos].sum++;

    if(l == r)
        return pos;

    int mid=(l+r)>>1;
    if(x <= mid)
        seg[pos].ls=update(l,mid,seg[pos].ls,x);
    else
        seg[pos].rs=update(mid+1,r,seg[pos].rs,x);

    return pos;
}
int query(int l,int r,int rtR,int rtL,int k)
{
    if(l == r)
        return b[l];

    ///这里的x求的是rtR的左儿子比rtL的左儿子多的数的个数
    int x=seg[seg[rtR].ls].sum-seg[seg[rtL].ls].sum;

    int mid=(l+r)>>1;
    if(k <= x)
        return query(l,mid,seg[rtR].ls,seg[rtL].ls,k);
    else
        return query(mid+1,r,seg[rtR].rs,seg[rtL].rs,k-x);
}
void Solve()
{
    sort(b+1,b+n+1);
    int siz=unique(b+1,b+n+1)-(b+1);

    ///去重后，不管是建树，还是查询，都是[1,siz]而不是[1,n]
    num=0;
    rt[0]=build(1,siz,1);
    for(int i=1;i <= n;++i)
    {
        a[i]=upper_bound(b+1,b+siz+1,a[i])-(b+1);
        rt[i]=update(1,siz,rt[i-1],a[i]);
    }

    for(int i=1;i <= m;++i)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",query(1,siz,rt[r],rt[l-1],k));
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i <= n;++i)
        {
            scanf("%d",a+i);
            b[i]=a[i];
        }
        Solve();
    }
    return 0;
}
