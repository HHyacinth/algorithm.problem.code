#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
const int maxn=5e3+50;

int n;
int Hash[maxn<<1];
struct Data
{
    int x1,y1;
    int x2,y2;
}rec[maxn];
struct Edge
{
    int l,r;
    int h;
    int f;
    bool operator < (const Edge &obj)const
    {
        if(h != obj.h)
            return h < obj.h;
        return f > obj.f;
    }
}e[maxn<<1];
struct Seg
{
    int l,r;
    int cnt;
    int len;
    int mid(){return (l+r)>>1;}
}seg[maxn<<3];

void build(int l,int r,int pos)
{
    seg[pos]={l,r,0,0};
    if(l == r)
        return ;
    int mid=(l+r)>>1;
    build(l,mid,ls(pos));
    build(mid+1,r,rs(pos));
}
void pushUp(int pos)
{
    if(seg[pos].cnt)
        seg[pos].len=Hash[seg[pos].r+1]-Hash[seg[pos].l];
    else if(seg[pos].l == seg[pos].r)
        seg[pos].len=0;
    else
        seg[pos].len=seg[ls(pos)].len+seg[rs(pos)].len;
}
void update(int l,int r,int pos,int f)
{
    if(seg[pos].l == l && seg[pos].r == r)
    {
        seg[pos].cnt += f;
        pushUp(pos);
        return ;
    }
    int mid=seg[pos].mid();
    if(r <= mid)
        update(l,r,ls(pos),f);
    else if(l > mid)
        update(l,r,rs(pos),f);
    else
    {
        update(l,mid,ls(pos),f);
        update(mid+1,r,rs(pos),f);
    }
    pushUp(pos);
}
int Calc()
{
    sort(e+1,e+2*n+1);
    sort(Hash+1,Hash+2*n+1);
    int siz=unique(Hash+1,Hash+2*n+1)-(Hash+1);
    build(1,siz,1);

    ll ans=0;
    ll pre=0;
    for(int i=1;i <= 2*n;++i)
    {
        int l=lower_bound(Hash+1,Hash+siz+1,e[i].l)-Hash;
        int r=lower_bound(Hash+1,Hash+siz+1,e[i].r)-Hash;
        update(l,r-1,1,e[i].f);

        ans += abs(seg[1].len-pre);
        pre=seg[1].len;
    }
    return ans;
}
int Solve()
{
    if(n == 0)
        return 0;

    ///计算横线面积并
    for(int i=1;i <= n;++i)
    {
        e[2*i-1]={rec[i].x1,rec[i].x2,rec[i].y1,1};
        e[2*i]={rec[i].x1,rec[i].x2,rec[i].y2,-1};

        Hash[2*i-1]=rec[i].x1;
        Hash[2*i]=rec[i].x2;
    }
    int ans=Calc();
    
    ///计算竖线面积并
    for(int i=1;i <= n;++i)
    {
        e[2*i-1]={rec[i].y1,rec[i].y2,rec[i].x1,1};
        e[2*i]={rec[i].y1,rec[i].y2,rec[i].x2,-1};

        Hash[2*i-1]=rec[i].y1;
        Hash[2*i]=rec[i].y2;
    }
    ans += Calc();

    return ans;
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    while(~scanf("%d",&n))
    {
        for(int i=1;i <= n;++i)
            scanf("%d%d%d%d",&rec[i].x1,&rec[i].y1,&rec[i].x2,&rec[i].y2);

        printf("%d\n",Solve());
    }
    return 0;
}
