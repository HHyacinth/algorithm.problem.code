#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e6+50;

int n,m,cnt;
char s[maxn];
char t[maxn];
int a[30];
int b[30];
vector<char >v;

bool Check(ll mid)
{
    ll need=0;
    for(int i=0;i < 26;++i)
        need += max(b[i]*mid-a[i],1ll*0);///求解至少需要字符('a'+i)多少个

    return need <= cnt ? true:false;
}
char *Solve()
{
    n=strlen(s+1);
    m=strlen(t+1);
    cnt=0;
    for(int i=1;i <= n;++i)
    {
        if(s[i] != '?')
            a[s[i]-'a']++;
        else
            cnt++;
    }
    for(int i=1;i <= m;++i)
        b[t[i]-'a']++;

    int l=0;
    int r=maxn;
    while(r-l > 1)
    {
        int mid=(l+r)>>1;
        if(Check(mid))
            l=mid;
        else
            r=mid;
    }
    
    for(int i=0;i < 26;++i)
        for(int j=1;j <= max(b[i]*l-a[i],0);++j)
            v.push_back('a'+i);

    int index=0;
    for(int i=1;i <= n;++i)
        if(s[i] == '?' && index < v.size())
            s[i]=v[index++];

    for(int i=1;i <= n;++i)
        if(s[i] == '?')
            s[i]='a';

    return s+1;
}
int main()
{
    scanf("%s%s",s+1,t+1);

    puts(Solve());

    return 0;
}
