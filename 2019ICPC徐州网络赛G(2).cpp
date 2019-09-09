#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=3e5+50;

int cnt[maxn];
unordered_set<char >_set[maxn];
struct PAM
{
    char s[maxn];
    int tot;
    int last;
    int son[maxn][30];
    int fail[maxn];
    int len[maxn];

    int newNode(int Len)
    {
        for(int i=0;i < 30;++i)
            son[tot][i]=0;
        cnt[tot]=0;
        fail[tot]=0;
        len[tot]=Len;
        _set[tot].clear();
        return tot++;
    }
    int getFail(int p,int i)
    {
        while(s[i-len[p]-1] != s[i])
            p=fail[p];
        return p;
    }
    void Init()
    {
        s[0]='#';
        tot=0;
        last=0;
        newNode(0);
        newNode(-1);
        fail[0]=1;
    }
    void pam(const char *obj)///个人习惯传入的数组obj下标从1开始
    {
        Init();

        int n=strlen(obj+1);
        for(int i=1;i <= n;++i)
        {
            s[i]=obj[i]-'a';
            int cur=getFail(last,i);

            if(!son[cur][s[i]])///x+(cur节点表示的字符串)+x形成一个新的回文串
            {
                int now=newNode(len[cur]+2);
                fail[now]=son[getFail(fail[cur],i)][s[i]];
                son[cur][s[i]]=now;

                _set[now]=_set[cur];///插入cur的所有字符
                _set[now].insert(s[i]);///插入s[i]

            }
            cnt[last=son[cur][s[i]]]++;
        }
        for(int i=tot-1;i > 1;--i)
            cnt[fail[i]] += cnt[i];
    }
}_pam;

char s[maxn];

int main()
{
    scanf("%s",s+1);

    _pam.pam(s);

    ll ans=0;
    for(int i=2;i < _pam.tot;++i)
        ans += 1ll*cnt[i]*_set[i].size();

    printf("%lld\n",ans);
    return 0;
}
