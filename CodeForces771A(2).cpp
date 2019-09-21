#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+50;

int n,m;
vector<int >G[maxn];
bool vis[maxn];

void addEdge(int u,int v)
{
    G[u].push_back(v);
}

char *Solve()
{
    for(int i=1;i <= n;++i)
    {
        addEdge(i,i);///加入其自身
        sort(G[i].begin(),G[i].end());///排序，方便判断同一个图中的所有节点连接的最小的节点是否相同
    }

    for(int u=1;u <= n;++u)
    {
        if(vis[u])
            continue;

        vis[u]=true;
        for(int i=0;i < G[u].size();++i)
        {
            int v=G[u][i];
            vis[v]=true;

            ///size不同或u,v所在子图的最小节点不同，表明节点u与v所在子图构不成完全图
            if(G[u].size() != G[v].size() || G[u][0] != G[v][0])
                return "NO";
        }
    }
    return "YES";
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i <= m;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    puts(Solve());
}
