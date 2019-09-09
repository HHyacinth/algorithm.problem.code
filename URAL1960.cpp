#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=3e5+50;

ll ans[maxn];
struct PAM
{
    char s[maxn];
    int tot;///构造的回文树共tot个节点，编号为0~tot-1，其中只有[2,tot-1]节点包含回文串
    int last;///新添加一个字母后所形成的最长回文串表示的节点
    int num[maxn];///num[i]:以“节点i所表示的回文串的结束字符”为结尾的回文串的个数
    int cnt[maxn];///cnt[i]:节点i所表示的回文串在s中的总个数（建树时求出的不是完全的，最后统计一下才是正确的）
    int son[maxn][30];///son[i][c]:i节点所表示的回文串两端增加字符c所表示的回文串所在的节点编号，如果不存在,son[i][c]=0
    int fail[maxn];///fail[i]:节点i所表示的回文串的最长后缀回文串（不包括节点i本身）所在的节点编号，如果不存在,fail[i]=0
    int len[maxn];///len[i]:节点i所表示的回文串的长度

    int newNode(int Len)
    {
        for(int i=0;i < 30;++i)
            son[tot][i]=0;
        cnt[tot]=0;
        num[tot]=0;
        fail[tot]=0;
        len[tot]=Len;
        return tot++;
    }
    int getFail(int p,int i)///类似KMP，失配后找一个尽量最长的后缀回文串
    {
        while(s[i-len[p]-1] != s[i])
            p=fail[p];
        return p;
    }
    void Init()
    {
        s[0]='#';///添加一个s中不会出现的字符
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

            ans[i]=ans[i-1];
            if(!son[cur][s[i]])///判断cur节点表示的回文串两端加入s[i]是否形成一个新的回文串
            {
                int now=newNode(len[cur]+2);
                fail[now]=son[getFail(fail[cur],i)][s[i]];
                son[cur][s[i]]=now;
                num[now]=num[fail[now]]++;

                ans[i]++;///如果可以形成本质不同的字符串，ans[i]=ans[i-1]+1;
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

    int len=strlen(s+1);
    for(int i=1;i <= len;++i)
        printf("%lld%c",ans[i],i == len ? '\n':' ');
}
