#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define lowbit(x) (x&(-x))
#define mem(a,b) memset(a,b,sizeof(a))
const int N=1e5+50;
const int M=N<<1;

int n,q,s;
int w[N];///存储第i条边的权值
int e[M];
int num;
int head[N];
struct Edge
{
    int to;
    int w;
    int next;
    int id;
}G[M];
void addEdge(int u,int v,int w,int id)
{
    G[num]={v,w,head[u],id};
    head[u]=num++;
}

struct BIT
{
    int bit[M];
    void Init()
    {
        mem(bit,0);
    }
    void Add(int t,int x)
    {
        while(t < M)
        {
            bit[t] += x;
            t += lowbit(t);
        }
    }
    int Sum(int t)
    {
        int ans=0;
        while(t > 0)
        {
            ans += bit[t];
            t -= lowbit(t);
        }
        return ans;
    }
}_bit;
struct LCA
{
    int cnt;
    int vs[M];///欧拉序列
    int pos[M];///pos[i]:节点i在欧拉序列中第一次出现的位置
    int dep[M];///深度序列
    int lb[M];///lb[i]:以2为底i的对数
    int dp[M][20];
    void DFS(int u,int f,int depth)
    {
        vs[++cnt]=u;
        dep[cnt]=depth;
        pos[u]=cnt;

        for(int i=head[u];~i;i=G[i].next)
        {
            int v=G[i].to;
            int w=G[i].w;
            int id=G[i].id;

            if(v == f)
                continue;

            ///u->v:叶子方向 +w
            ///将其权值存储在v对应的编号，即cnt+1
            e[id<<1]=cnt+1;
            _bit.Add(cnt+1,w);

            DFS(v,u,depth+1);

            ///v->u:根方向 -w
            ///将其权值存储在u对应的编号中，即cnt
            vs[++cnt]=u;
            dep[cnt]=depth;
            e[id<<1|1]=cnt;
            _bit.Add(cnt,-w);
        }
    }
    void ST()
    {
        lb[0]=-1;
        for(int i=1;i <= cnt;++i)
        {
            dp[i][0]=i;
            lb[i]=lb[i-1]+((i&(i-1)) == 0 ? 1:0);
        }

        for(int k=1;k <= lb[cnt];++k)
            for(int u=1;u+(1<<k)-1 <= cnt;++u)
                if(dep[dp[u][k-1]] > dep[dp[u+(1<<(k-1))][k-1]])
                    dp[u][k]=dp[u+(1<<(k-1))][k-1];
                else
                    dp[u][k]=dp[u][k-1];
    }
    void Init()
    {
        cnt=0;
        DFS(1,1,0);
        ST();
    }
    int lca(int u,int v)
    {
        u=pos[u];
        v=pos[v];
        if(u > v)
            swap(u,v);

        int k=lb[v-u+1];
        if(dep[dp[u][k]] > dep[dp[v-(1<<k)+1][k]])
            return vs[dp[v-(1<<k)+1][k]];
        else
            return vs[dp[u][k]];
    }
    int Calc(int u,int v)
    {
        int x=lca(u,v);
        return _bit.Sum(pos[u])+_bit.Sum(pos[v])-2*_bit.Sum(pos[x]);
    }
}_lca;

void Solve()
{
    _lca.Init();

    while(q--)
    {
        int op;
        scanf("%d",&op);
        if(op == 0)
        {
            int u;
            scanf("%d",&u);
            printf("%d\n",_lca.Calc(u,s));
            s=u;
        }
        else
        {
            int x,val;
            scanf("%d%d",&x,&val);
            
            ///找到第x条边的对应的朝向叶子方向和根方向的两条边所在的位置
            ///e[x<<1],e[x<<1|1]
            ///分别将其值变为 val 和 -val
            _bit.Add(e[x<<1],val-w[x]);
            _bit.Add(e[x<<1|1],w[x]-val);
            w[x]=val;
        }
    }
}
void Init()
{
    num=0;
    mem(head,-1);
}
int main()
{
    Init();
    scanf("%d%d%d",&n,&q,&s);
    for(int i=1;i < n;++i)
    {
        int u,v;
        scanf("%d%d%d",&u,&v,w+i);
        addEdge(u,v,w[i],i);
        addEdge(v,u,w[i],i);
    }
    Solve();

    return 0;
}
