#include<bits/stdc++.h>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=2e5+50;

int n,k;
int p[maxn];
int num;
int head[maxn];
struct Edge
{
    int to;
    int next;
}G[maxn<<2];
void addEdge(int u,int v)
{
    G[num]={v,head[u]};
    head[u]=num++;
}
int col[maxn];///col[i]:节点i所处的强连通分量的标号
///标号越小，形成的强连通入度越小
struct SCC
{
    bool vis[maxn];
    vector<int >vs;
    void DFS(int u)
    {
        vis[u]=true;
        for(int i=head[u];~i;i=G[i].next)
        {
            int v=G[i].to;
            if((i&1) || vis[v])///正向边，num为偶数
                continue;
            DFS(v);
        }
        vs.push_back(u);///拓扑序
    }
    void RDFS(int u,int k)///反向求解强连通分量
    {
        vis[u]=true;
        col[u]=k;
        for(int i=head[u];~i;i=G[i].next)
        {
            int v=G[i].to;
            if(!(i&1) || vis[v])///反向边，num为奇数
                continue;
            RDFS(v,k);
        }
    }
    int scc()
    {
        vs.clear();
        mem(vis,false);
        for(int i=1;i <= n;++i)///注意编号，根据题意而定，有的是从0开始的
            if(!vis[i])
                DFS(i);

        int k=0;
        mem(vis,false);
        for(int i=vs.size()-1;i >= 0;--i)///从拓扑序的最大值开始查找SCC
            if(!vis[vs[i]])
                RDFS(vs[i],++k);
        return k;///强连通分量的个数
    }
}_scc;
int in[maxn];
int ch[maxn];
int newNum;
int newHead[maxn];
Edge newG[maxn<<2];
queue<int >q;
void addNewEdge(int u,int v)
{
    newG[newNum]={v,newHead[u]};
    newHead[u]=newNum++;
}
void BFS(int t)
{
    while(!q.empty())
        q.pop();
    for(int i=1;i <= t;++i)
        if(!in[i])///入度为0的点对应的字母最小
            q.push(i);

    int cnt=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();

        ch[u]='a'+cnt;
        if(cnt < k-1)///取前k个小写字母
            cnt++;

        for(int i=newHead[u];~i;i=newG[i].next)
        {
            int v=newG[i].to;

            in[v]--;
            if(!in[v])
                q.push(v);
        }
    }
}
void Solve()
{
    int t=_scc.scc();
    if(t < k)
        return puts("NO"),void(0);

    mem(in,0);
    newNum=0;
    mem(newHead,-1);
    for(int u=1;u <= n;++u)
    {
        for(int i=head[u];~i;i=G[i].next)
        {
            int v=G[i].to;
            if((i&1) || col[u] == col[v])
                continue;
            
            ///将属于不同强连通分量的元素加入到新图中
            ///并更新col[v]的入度
            in[col[v]]++;
            addNewEdge(col[u],col[v]);
        }
    }
    BFS(t);
    
    puts("YES");
    for(int i=1;i <= n;++i)
        putchar(ch[col[i]]);
    printf("\n");
}
void Init()
{
    num=0;
    mem(head,-1);///一定要记得初始化head数组
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    Init();

    scanf("%d%d",&n,&k);
    for(int _=1;_ <= 2;++_)
    {
        for(int i=1;i <= n;++i)
        {
            scanf("%d",p+i);
            if(i != 1)
            {
                addEdge(p[i-1],p[i]);
                addEdge(p[i],p[i-1]);
            }
        }
    }

    Solve();

    return 0;
}
