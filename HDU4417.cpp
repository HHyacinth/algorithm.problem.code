#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+50;

int n,m;
int a[maxn];
int b[maxn];
int rt[maxn];
int num;
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
        return pos;

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
int query(int l,int r,int pos,int k)
{
    if(l == r)
        return seg[pos].sum;

    int mid=(l+r)>>1;
    if(k <= mid)
        return query(l,mid,seg[pos].ls,k);
    else
        return seg[seg[pos].ls].sum+query(mid+1,r,seg[pos].rs,k);
}
void Solve()
{
    sort(b+1,b+n+1);
    int siz=unique(b+1,b+n+1)-(b+1);

    num=0;
    rt[0]=build(0,siz,1);

    for(int i=1;i <= n;++i)
    {
        a[i]=upper_bound(b+1,b+siz+1,a[i])-(b+1);
        rt[i]=update(0,siz,rt[i-1],a[i]);
    }

    while(m--)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        l++,r++;
        k=upper_bound(b+1,b+siz+1,k)-(b+1);

        printf("%d\n",query(0,siz,rt[r],k)-query(0,siz,rt[l-1],k));
    }
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    int T;
    scanf("%d",&T);
    int kase=1;

    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i <= n;++i)
        {
            scanf("%d",a+i);
            b[i]=a[i];
        }
        printf("Case %d:\n",kase++);
        Solve();
    }
    return 0;
}
