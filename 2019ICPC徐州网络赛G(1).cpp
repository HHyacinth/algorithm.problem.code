#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(x) (x&(-x))
const int maxn=4e5+50;

int m=0;
struct Data
{
	int l,r;
	int id;
	ll cnt;
	bool operator < (const Data& obj)
	{
		return r < obj.r;
	}
}a[maxn];
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

            if(!son[cur][s[i]])///判断cur节点表示的回文串两端加入s[i]是否形成一个新的回文串
            {
                int now=newNode(len[cur]+2);
                fail[now]=son[getFail(fail[cur],i)][s[i]];
                son[cur][s[i]]=now;
                num[now]=num[fail[now]]++;

                a[++m]={i-len[now]+1,i,m,0};///记录新增回文串的[l,r]
            }
            cnt[last=son[cur][s[i]]]++;
        }
        ///统计cnt
        for(int i=tot-1;i > 1;--i)
            cnt[fail[i]] += cnt[i];
        ///将统计好的cnt记录到a中
        for(int i=2;i < tot;++i)
            a[i-1].cnt=cnt[i];
    }
}_pam;

char s[maxn];
int bit[maxn];
int last[1000];
int ans[maxn];
void add(int t,int x)
{
	while(t < maxn)
	{
		bit[t] += x;
		t += lowbit(t);
	}
}
int sum(int t)
{
	int ans=0;
	while(t)
	{
		ans += bit[t];
		t -= lowbit(t);
	}
	return ans;
}
ll Solve()///离线树状数组求[l,r]区间内不同数的个数
{
    sort(a+1,a+1+m);
    int pre=0;
	for(int i=1;i <= m;i++)
	{
		if(a[i].r > pre)
        {
            for(int j=pre+1;j <= a[i].r;j++)
            {
                if(!last[s[j]])
                    add(j,1);
                else
                {
                    add(last[s[j]],-1);
                    add(j,1);
                }
                last[s[j]]=j;
                pre=a[i].r;
            }
        }
		ans[a[i].id]=sum(a[i].r)-sum(a[i].l-1);
	}


	ll res=0;
	for(int i=1;i<=m;i++)
        res += a[i].cnt*ans[a[i].id];

    return res;
}

int main()
{
    scanf("%s",s+1);
    _pam.pam(s);

    printf("%lld\n",Solve());

    return 0;
}
