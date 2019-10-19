#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+50;
const int N=1e6;

int n,m;
int a[maxn];
int num;
int rt[maxn];
struct Seg
{
    int l,r;
    int ls,rs;
    int sum;
    int mid(){return l+((r-l)>>1);}
}seg[maxn*60];

int build(int l,int r,int pos)
{
    pos=++num;
    seg[pos]={l,r};
    seg[pos].sum=0;

    if(l == r)
        return pos;

    int mid=seg[pos].mid();
    seg[pos].ls=build(l,mid,pos);
    seg[pos].rs=build(mid+1,r,pos);

    return pos;
}
int clone(int pos)
{
    seg[++num]=seg[pos];
    return num;
}
int update(int pos,int x)
{
    pos=clone(pos);
    seg[pos].sum++;

    if(seg[pos].l == seg[pos].r)
        return pos;

    int mid=seg[pos].mid();
    if(x <= mid)
        seg[pos].ls=update(seg[pos].ls,x);
    else
        seg[pos].rs=update(seg[pos].rs,x);

    return pos;
}
int L,R,p,k;

int query(int rtL,int rtR,int l,int r)///求解[L,R]区间中属于[l,r]的数的个数
{
    if(seg[rtL].l == l && seg[rtL].r == r)
        return seg[rtR].sum-seg[rtL].sum;

    int mid=seg[rtL].mid();
    if(r <= mid)
        return query(seg[rtL].ls,seg[rtR].ls,l,r);
    else if(l > mid)
        return query(seg[rtL].rs,seg[rtR].rs,l,r);
    else
        return query(seg[rtL].ls,seg[rtR].ls,l,mid)+query(seg[rtL].rs,seg[rtR].rs,mid+1,r);
}
bool Check(int mid)
{
    int l=max(0,p-mid);
    int r=min(N,p+mid);

    return query(rt[L-1],rt[R],l,r) >= k ? true:false;
}
void Solve()
{
    num=0;
    rt[0]=build(0,N,1);
    for(int i=1;i <= n;++i)
        rt[i]=update(rt[i-1],a[i]);

    int ans=0;
    while(m--)
    {
        scanf("%d%d%d%d",&L,&R,&p,&k);
        L ^= ans;
        R ^= ans;
        p ^= ans;
        k ^= ans;

        if(L > R)
            swap(L,R);

        int l=-1,r=N+1;
        while(r-l > 1)
        {
            int mid=l+((r-l)>>1);
            if(Check(mid))///判断[L,R]区间中属于[p-mid,p+mid]的数的个数是否大于等于k个
                r=mid;
            else
                l=mid;
        }
        ans=r;
        printf("%d\n",ans);
    }
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i <= n;++i)
            scanf("%d",a+i);
        Solve();
    }
    return 0;
}
