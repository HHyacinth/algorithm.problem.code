/**
    博客园挂了，暂时先存在github里
题意
    给你 n 个矩形，求矩形并的周长；
题解1（两次扫描线）
    周长可以分成两部分计算，横线和竖线；
    如何求解横线的所有并的长度呢？
    和求矩阵面积并的做法一样，先将 x 离散化；
    每次更新的时候，记录一下上次更新后的横线总长度；
    ans += [现在这次总区间被覆盖的长度和上一次总区间被覆盖的长度之差的绝对值];
    求解竖线的所有并的长度何求解横线的长度相同；
    需要注意的是，在求解矩形面积并的时候，排序策略是按照 h 从小到大排序，并不需要考虑 h 相同的情况；
    但是求矩形周长并的时候就不行了，必须得考虑 h 相同的情况下的排序策略；
    以下例求解横线并的长度为例；
        n=2
        (2,1),(4,3)
        (3,3),(4,5)
    定义如下数据结构存储横线；
    struct Edge
    {
        int l,r;
        int h;
        int f;
        bool operator < (const Edge &obj)const
        {
                return h < obj.h;
        }
}e[maxn<<1];
    假设与处理矩形面积并的排序策略相同，只考虑按 h 升序排列，那么排列后的数据为：
        $e_{1}:\{l=2\ ,\ r=4\ ,\ h=1\ ,\ f=1 \}$
        $e_{2}:\{l=2\ ,\ r=4\ ,\ h=3\ ,\ f=-1 \}$
        $e_{3}:\{l=3\ ,\ r=4\ ,\ h=3\ ,\ f=1 \}$
        $e_{1}:\{l=3\ ,\ r=4\ ,\ h=5\ ,\ f=-1 \}$
    让我们手动模拟一下这个求解过程；
    定义 ans 表示答案，len 表示当前更新后的横线并的总长度，pre 表示上一次更新后的 len 值；
    初始化 ans=0,len=0,pre=0;
    首先处理 $e_{1}$，update() 后，len = 2;
    更新 ans += |len-pre| = 2 , pre=len=2;
    处理 $e_{2}$，update() 后，len = 0;
    此时，更新 ans += |len-pre| = 2+2 = 4 , pre=len=0，出现问题了是吧，因为来到此处的时候，ans=3才对；
    继续向上更新， $e_{3}$，update() 后，len=1;
    更新 ans += |len-pre| = 4+1 = 5 , pre=len=1;
    $e_{4}$，update() 后，len=0；
    更新 ans += |len-pre| = 5+1 = 6；
    但是正确答案应该是 ans = 4；
    多的 2 就是因为排序策略不当而产生的；
    所以，当 h 相同的时候，应该先处理 f = 1 的边，即如果可以先加入边，那就优先执行加边操作；
    所以，需要将 Edge 中的排序策略更改一下，改成如下模式：
    bool operator < (const Edge &obj)const
    {
        if(h != obj.h)
            return h < obj.h;
        return f > obj.f;
    }
    （ps:f = 1 表示下边界，所以当 h 相同时，按照 f 降序排列）
    到这，这道题就这么愉快的解决了；
*/
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
