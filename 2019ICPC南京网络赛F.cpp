#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+50;

int n,k;
int a[maxn];
set<int >f;
int L[maxn];///L[i]:记录i左边的k个数中小于i的最大的数
int R[maxn];///R[i]:记录i右边的k个数中小于i的最大的数
int s[maxn];///s[i]:记录i后可以衔接的满足条件的数的总个数

void Solve()
{
    f.clear();
    f.insert(0);

    /**
        先正向遍历求出R[];
        在反向遍历求出L[];
    */
    int index=2;///正向遍历，先将1后的k个数加入到set中
    for(;index <= min(n,k+1);++index)
        f.insert(a[index]);

    for(int i=1;i <= n;++i)
    {
        ///查找a[i]右边的k个数中满足条件的最大的数
        auto it=f.upper_bound(a[i]);
        it--;
        R[a[i]]=*it;
        
        ///删掉a[i+1],插入a[index+1]
        if(i != n)
            f.erase(f.find(a[i+1]));
        if(index <= n)
            f.insert(a[index++]);
    }
    
    index=n-1;
    for(;index >= max(1,n-k);--index)
        f.insert(a[index]);
    for(int i=n;i >= 1;--i)
    {
        ///查找a[i]左边的k个数中满足条件的最大的数
        auto it=f.upper_bound(a[i]);
        it--;

        L[a[i]]=*it;

        ///删掉a[i-1],插入a[index-1]
        if(i != 1)
            f.erase(f.find(a[i-1]));
        if(index >= 1)
            f.insert(a[index--]);
    }
    
    s[0]=0;
    for(int i=1;i <= n;++i)
    {
        ///最大值优先
        s[i]=s[max(R[i],L[i])]+1;
        printf("%d%c",s[i],i==n?'\n':' ');
    }
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);

        for(int i=1;i <= n;++i)
            scanf("%d",a+i);

        Solve();
    }
    return 0;
}
