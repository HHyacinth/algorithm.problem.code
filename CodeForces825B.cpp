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
const int dx[10]={0,1,-1,0,0,1,1,-1,-1};
const int dy[10]={0,0,0,1,-1,1,-1,1,-1};
const int MOD=1e9+7;
const int maxn=1e5+50;

int n;
char s[20][20];

char *Solve()
{
    int ans=0;
    for(int i=1;i <= n;++i)
        for(int j=1;j <= n;++j)
            for(int d=1;d <= 8;++d)
            {
                int len=0;
                bool ok=false;
                int x=i,y=j;
                while(true)
                {
                    if(x < 1 || y < 1 || x > n || y > n || s[x][y] == 'O')
                        break;
                    if(s[x][y] == '.')
                    {
                        if(ok)///判断Alice是否下了一个棋子
                            break;
                        ok=true;
                    }
                    len++;
                    x += dx[d];
                    y += dy[d];
                }
                ans=max(ans,len);
            }
    if(ans >= 5)
        return "YES";
    return "NO";
}
int main()
{
    n=10;
    for(int i=1;i <= n;++i)
        scanf("%s",s[i]+1);
    puts(Solve());

    return 0;
}
