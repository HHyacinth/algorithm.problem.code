#include<bits/stdc++.h>
using namespace std;
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define pii pair<int ,int >
#define F first
#define S second
#define MAX(a,b,c) max(a,max(b,c))
const int maxn=5e4+50;

int n,m;
struct Seg
{
    int l,r;
    int lsum,rsum;
    int sum;
    int lazy;
    int mid(){return l+((r-l>>1));}
    int len(){return r-l+1;}

    void Set(int len,int laz)
    {
        lsum=rsum=sum=len;
        lazy=laz;
    }
}seg[maxn<<2];
set<pii >_set;

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

    if(lazy == -1)
        return ;

    seg[ls(pos)].Set(lazy == 1 ? 0:seg[ls(pos)].len(),lazy);
    seg[rs(pos)].Set(lazy == 1 ? 0:seg[rs(pos)].len(),lazy);

    lazy=-1;
}
void build(int l,int r,int pos)
{
    seg[pos]={l,r,r-l+1,r-l+1,r-l+1,-1};

    if(l == r)
        return ;

    int mid=seg[pos].mid();
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
void update(int pos,int l,int r,int lazy)
{
    if(seg[pos].l == l && seg[pos].r == r)
    {
        seg[pos].Set(lazy == 1 ? 0:seg[pos].len(),lazy);
        return ;
    }
    pushDown(pos);

    int mid=seg[pos].mid();
    if(r <= mid)
        update(ls(pos),l,r,lazy);
    else if(l > mid)
        update(rs(pos),l,r,lazy);
    else
    {
        update(ls(pos),l,mid,lazy);
        update(rs(pos),mid+1,r,lazy);
    }
    pushUp(pos);
}
void Solve()
{
    _set.clear();
    build(1,n,1);

    while(m--)
    {
        char op[10];
        int x;
        scanf("%s",op);
        if(op[0] != 'R')
            scanf("%d",&x);

        if(op[0] == 'R')
        {
            puts("Reset Now");
            update(1,1,n,0);
            _set.clear();
        }
        else if(op[0] == 'N')
        {
            int s=0;
            if(seg[1].sum >= x)
                s=query(1,x);
            if(s == 0)
                puts("Reject New");
            else
            {
                printf("New at %d\n",s);
                update(1,s,s+x-1,1);
                _set.insert({s,s+x-1});
            }
        }
        else if(op[0] == 'F')
        {
            auto it=_set.upper_bound({x,n+1});
            if(it == _set.begin() || (--it)->S < x)
            {
                puts("Reject Free");
                continue;
            }

            printf("Free from %d to %d\n",it->F,it->S);
            update(1,it->F,it->S,0);
            _set.erase(it);
        }
        else if(op[0] == 'G')
        {
            if(_set.size() < x)
            {
                puts("Reject Get");
                continue;
            }
            auto it=_set.begin();
            for(int i=1;i < x;++i,++it);
            printf("Get at %d\n",it->F);
        }
    }
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    while(~scanf("%d%d",&n,&m))
    {
        Solve();
        puts("");
    }

    return 0;
}
