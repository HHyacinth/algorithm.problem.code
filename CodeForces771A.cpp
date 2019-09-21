#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define INFll 0x3f3f3f3f3f3f3f3f
#define ll long long
#define ul unsigned long long
#define pii pair<int ,int >
#define pll pair<ll , ll >
#define pb(x) push_back(x)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define GCD(a,b) __gcd(a,b)
#define PI acos(-1)
#define mem(a,b) memset(a,b,sizeof(a))
#define endl '\n'
#define isLeap(x) (x%4==0&&x%100!=0||x%400==0)
#define Close() std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
const int day[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},
                      {0,31,29,31,30,31,30,31,31,30,31,30,31}/**leap*/};
const int maxn=2e5+50;

int n,m;
int num;
int head[maxn];
struct Edge
{
    int to;
    int next;
}G[maxn<<1];
void addEdge(int u,int v)
{
    G[num]={v,head[u]};
    head[u]=num++;
}
ll out[maxn];
bool vis[maxn];

void DFS(int u,ll &cnt,ll &sum)
{
    cnt++;
    vis[u]=true;
    for(int i=head[u];~i;i=G[i].next)
    {
        out[u]++;
        int v=G[i].to;
        if(!vis[v])
            DFS(v,cnt,sum);
    }
    sum += out[u];
}
char *Solve()
{
    mem(vis,false);
    for(int i=1;i <= n;++i)
    {
        if(vis[i])
            continue;
        ll cnt=0;
        ll sum=0;
        DFS(i,cnt,sum);

        ///cnt个节点共有sum个出度
        ///判断sum 是否等于 cnt*(cnt-1)
        if(sum != cnt*(cnt-1))
            return "NO";
    }
    return "YES";
}
void Init()
{
    num=0;
    mem(head,-1);
    mem(out,0);
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contestOut","w",stdout);
    Init();

    scanf("%d%d",&n,&m);
    for(int i=1;i <= m;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    puts(Solve());

    return 0;
}
