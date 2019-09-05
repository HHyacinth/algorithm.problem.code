#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int ,int >
#define mem(a,b) memset(a,b,sizeof(a))
#define lowbit(x) (x&(-x))
const int maxn=1e6+50;

int n,m,q;
int num;
struct Point
{
    int x,y;
    int f;
    int id;
    ///按照先x,在y,最后f的策略排序
    bool operator < (const Point& obj)const
    {
        if(x != obj.x)
            return x < obj.x;
        else if(y != obj.y)
            return y < obj.y;
        else
            return f > obj.f;
    }
}p[maxn];

///计算(x,y)对应的权值
int Calc(int x,int y)
{
    int t=min(min(x,y),min(n+1-x,n+1-y));
    ll num=1+1ll*4*(t-1)*(n-t+1);

    num += 1ll*2*(n-2*t+1);
    int cnt=abs(x-t)+abs(y-t);
    num += (x >= y ? -cnt:cnt);

    int ans=0;
    while(num)
    {
        ans += num%10;
        num /= 10;
    }
    return ans;
}

ll bit[maxn];
void Add(int t,int x)
{
    while(t < maxn)
    {
        bit[t] += x;
        t += lowbit(t);
    }
}
ll Sum(int t)
{
    ll ans=0;
    while(t > 0)
    {
        ans += bit[t];
        t -= lowbit(t);
    }
    return ans;
}
ll ans[maxn];
void Solve()
{
    sort(p+1,p+num+1);

    mem(ans,0);
    mem(bit,0);

    for(int i=1;i <= num;++i)
    {
        ///如果f=2,将权值加入到树状数组中
        if(p[i].f == 2)
            Add(p[i].y,Calc(p[i].x,p[i].y));
        else
            ans[p[i].id] += p[i].f*Sum(p[i].y);
    }
    for(int i=1;i <= q;++i)
        printf("%lld\n",ans[i]);
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);

    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&q);

        num=0;
        for(int i=1;i <= m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            p[++num]={x,y,2,0};
        }
        for(int i=1;i <= q;++i)
        {
            int x1,y1;
            int x2,y2;
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            p[++num]={x2,y2,1,i};
            p[++num]={x1-1,y1-1,1,i};
            p[++num]={x1-1,y2,-1,i};
            p[++num]={x2,y1-1,-1,i};
        }
        Solve();
    }
    return 0;
}
