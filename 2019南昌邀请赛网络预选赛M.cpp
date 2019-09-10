#include<bits/stdc++.h>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+50;

char s[maxn];
char t[maxn];
int a[30];
vector<int >v[30];
int p[maxn];

bool Find()
{
    int m=strlen(t+1);

    mem(a,0);
    int pre=0;
    for(int i=1;i <= m;++i)
    {
        int x=t[i]-'a';
        for(;a[x] < v[x].size() && v[x][a[x]] <= pre;a[x]++);

        if(a[x] == v[x].size())
            return false;
        pre=v[x][a[x]];
    }
    return true;
}
void Solve()
{
    int n=strlen(s+1);
    for(int i=1;i <= n;++i)
        v[s[i]-'a'].push_back(i);

    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",t+1);

        if(Find())
            puts("YES");
        else
            puts("NO");
    }
}
int main()
{
    scanf("%s",s+1);
    Solve();

    return 0;
}
