#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
const int maxn=80;

int n;
char s[maxn];
int dp[maxn][maxn][maxn][2];
vector<int >v[4];

int Solve()
{
    for(int i=1;i <= n;++i)
    {
        if(s[i] == 'V')
            v[1].push_back(i);
        else if(s[i] == 'K')
            v[2].push_back(i);
        else
            v[3].push_back(i);
    }
    for(int i=0;i <= v[1].size();++i)
        for(int j=0;j <= v[2].size();++j)
            for(int k=0;k <= v[3].size();++k)
                dp[i][j][k][0]=dp[i][j][k][1]=INF;
    dp[0][0][0][0]=0;

    for(int i=0;i <= v[1].size();++i)
        for(int j=0;j <= v[2].size();++j)
            for(int k=0;k <= v[3].size();++k)
                if(i || j || k)
                {
                    if(i)///以第i个'V'作为”用前i个'V',前j个'K'和前'K'个'其他字符'所形成的字符串“的结尾
                    {
                        int cnt=min(dp[i-1][j][k][0],dp[i-1][j][k][1]);
                        for(int l=0;l < j;++l)
                            if(v[1][i-1] < v[2][l])
                                cnt++;
                        for(int l=0;l < k;++l)
                            if(v[1][i-1] < v[3][l])
                                cnt++;
                        dp[i][j][k][1]=cnt;
                    }
                    if(j)///以第j个'K'作为”用前i个'V',前j个'K'和前'K'个'其他字符'所形成的字符串“的结尾
                    {
                        int cnt=dp[i][j-1][k][0];
                        for(int l=0;l < i;++l)
                            if(v[2][j-1] < v[1][l])
                                cnt++;
                        for(int l=0;l < k;++l)
                            if(v[2][j-1] < v[3][l])
                                cnt++;
                        dp[i][j][k][0]=cnt;
                    }
                    if(k)///以第k个'其他字符'作为”用前i个'V',前j个'K'和前'K'个'其他字符'所形成的字符串“的结尾
                    {
                        int cnt=min(dp[i][j][k-1][0],dp[i][j][k-1][1]);
                        for(int l=0;l < i;++l)
                            if(v[3][k-1] < v[1][l])
                                cnt++;
                        for(int l=0;l < j;++l)
                            if(v[3][k-1] < v[2][l])
                                cnt++;
                        dp[i][j][k][0]=min(dp[i][j][k][0],cnt);
                    }

                    if(i == v[1].size() && j == v[2].size() && k == v[3].size())
                        return min(dp[i][j][k][0],dp[i][j][k][1]);
                }
}
int main()
{
    scanf("%d%s",&n,s+1);

    printf("%d\n",Solve());

    return 0;
}
