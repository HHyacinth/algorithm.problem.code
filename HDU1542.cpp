#include<bits/stdc++.h>
using namespace std;
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
const int maxn=200;

int n;
double Hash[maxn<<1];
struct Data
{
    double l,r;///保存边的左右信息
    double h;///保存边的高度
    int f;///判断该边为所在矩形的上边还是下边，上边就赋值为-1，下边赋值为1
    bool operator < (const Data &obj)const///按照边的高度升序排列
    {
        return h < obj.h;
    }
}a[maxn<<1];
struct Seg
{
    int l,r;
    double cnt;///当前节点被覆盖的情况
    double len;///当前节点被覆盖的总长度
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
    if(seg[pos].cnt)///cnt>0，表明该区间被整段覆盖
        seg[pos].len=Hash[seg[pos].r+1]-Hash[seg[pos].l];
    else if(seg[pos].l == seg[pos].r)///已经不是一条线段
        seg[pos].len=0;
    else///是一条线段，但是没有整段覆盖，那么只能从左右儿子的信息中获取
        seg[pos].len=seg[ls(pos)].len+seg[rs(pos)].len;
}
void update(int l,int r,int pos,int f)
{
    if(seg[pos].l == l && seg[pos].r == r)
    {
        /**
            f=1:矩形的下边，插入到cnt中
            f=-1:矩形的上边，从cnt中减掉
        */
        seg[pos].cnt += f;///更新此区间被覆盖的情况
        pushUp(pos);///更新这个区间被覆盖的总长度
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
double Solve()
{
    sort(a+1,a+2*n+1);
    sort(Hash+1,Hash+2*n+1);
    int siz=unique(Hash+1,Hash+2*n+1)-(Hash+1);

    build(1,siz,1);

    double ans=0;
    for(int i=1;i <= 2*n;++i)
    {
        if(i != 1)
            ans += seg[1].len*(a[i].h-a[i-1].h);

        ///横坐标离散化，加入到线段树中
        int l=lower_bound(Hash+1,Hash+siz+1,a[i].l)-Hash;
        int r=lower_bound(Hash+1,Hash+siz+1,a[i].r)-Hash;
        
        /**
            注意此处有个小技巧
            更新的时候，不是更新的[l,r]区间，而是[l,r-1]区间
            而在pushUp()的时候，相应的[l,r]区间记录的是[l,r+1]的长度
        */
        update(l,r-1,1,a[i].f);
    }
    return ans;
}
int main()
{
    int kase=1;
    while(scanf("%d",&n) && n)
    {
        for(int i=1;i <= n;++i)
        {
            double x1,y1;
            double x2,y2;
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);

            a[2*i-1]={x1,x2,y1,1};///记录下边界信息
            a[2*i]={x1,x2,y2,-1};///记录上边界信息

            Hash[2*i-1]=x1;
            Hash[2*i]=x2;
        }
        printf("Test case #%d\n",kase++);
        printf("Total explored area: %.2f\n\n",Solve());
    }
    return 0;
}
