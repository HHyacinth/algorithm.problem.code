#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int ,int >
#define INF 0x3f3f3f3f
#define F first
#define S second
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e3+50;
const int MOD=1e9+7;

int n,m;
int a[maxn][maxn];
ll dp[maxn][maxn];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
vector<pii >v;

bool isSat(int x,int y)
{
    for(int i=0;i < 4;++i)
        if(a[x+dx[i]][y+dy[i]] == a[x][y]-1)
            return false;
    for(int i=0;i < 4;++i)
        if(a[x+dx[i]][y+dy[i]] == a[x][y]+1)
            return true;
    return false;
}
ll DFS(int x,int y,int cnt)
{
    if(cnt >= 3 && dp[x][y])
        return dp[x][y];

    ll ans=0;
    bool ok=false;
    for(int i=0;i < 4;++i)
    {
        int X=x+dx[i];
        int Y=y+dy[i];

        if(a[X][Y] == a[x][y]+1)
        {
            ans += DFS(X,Y,cnt+1);
            ok=true;
        }

        ans %= MOD;
    }
    if(!ok && cnt >= 4)
        ans++;

    return dp[x][y]=ans%MOD;
}
ll Solve()
{
    mem(dp,0);
    v.clear();

    for(int i=1;i <= n;++i)
        for(int j=1;j <= m;++j)
            if(isSat(i,j))
                v.push_back({i,j});

    for(int i=0;i < v.size();++i)
        DFS(v[i].F,v[i].S,1);

    for(int i=1;i <= n;++i)
        for(int j=1;j <= n;++j)
            printf("%lld%c",dp[i][j],j == n ? '\n':' ');

    ll ans=0;
    for(int i=0;i < v.size();++i)
        ans += dp[v[i].F][v[i].S];
    return ans%MOD;
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    scanf("%d%d",&n,&m);

    mem(a,-INF);
    for(int i=1;i <= n;++i)
        for(int j=1;j <= m;++j)
            scanf("%d",&a[i][j]);

    printf("%lld\n",Solve());

    return 0;
}
