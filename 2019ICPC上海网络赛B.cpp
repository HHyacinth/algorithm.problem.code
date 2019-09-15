#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+50;

int n,m;
int k;
struct Data
{
    int x;///l or r
    int f;///f=1:x为l , f=-1:x为r
    bool operator < (const Data &obj) const
    {
        return x < obj.x;
    }
}a[4*maxn];
int x[maxn<<2];
int cnt[maxn<<2];

int Solve()
{
    sort(a+1,a+k+1);

    int index=1;
    int num=0;
    int tot=0;
    while(index <= k)
    {
        int cur=index;
        ///[index,...,cur-1]对应着相同的 x
        ///先将l加入到tot中，并记录到x[num],cnt[num]中
        for(;cur <= k && a[cur].x == a[index].x;++cur)
            if(a[cur].f == 1)
                tot++;
        
        x[++num]=a[index].x;
        cnt[num]=tot;

        ///再将r从tot中去掉
        for(int i=index;i < cur;++i)
            if(a[i].f == -1)
                tot--;
        index=cur;
    }

    int ans=0;
    for(int i=1;i <= num;++i)
    {
        ///cnt[i],cnt[i+1]有一个为奇数，就说明(x[i],...,x[i+1])被反转了奇数次
        ///那么，(x[i],...,x[i+1])之间的灯泡全部是亮着的
        if(i+1 <= num && ((cnt[i]&1) || (cnt[i+1]&1)))
            ans += x[i+1]-x[i]-1;
        if(cnt[i]&1)///判断x[i]是否被反转了奇数次
            ans++;
    }
    return ans;
}
int main()
{
    int T;
    scanf("%d",&T);

    for(int kase=1;kase <= T;++kase)
    {
        scanf("%d%d",&n,&m);

        k=0;
        for(int i=1;i <= m;++i)
        {
            int l,r;
            scanf("%d%d",&l,&r);

            a[++k]={l,1};
            a[++k]={r,-1};
            a[++k]={l-1,0};
            a[++k]={r+1,0};
        }
        printf("Case #%d: %d\n",kase,Solve());
    }
    return 0;
}
