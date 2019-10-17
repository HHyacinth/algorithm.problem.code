#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+50;

int n,q;
int a[maxn];
struct Data
{
    int id;
    int sum;
    bool operator < (const Data &obj)const
    {
        if(sum != obj.sum)
            return sum < obj.sum;
        return id < obj.id;
    }
};
set<Data >_set;

void Solve()
{
    _set.clear();
    for(int i=1;i <= n;++i)
        _set.insert({i,a[i]});

    while(q--)
    {
        char op[10];
        int x;
        scanf("%s%d",op,&x);

        if(op[0] == 'i')
        {
            auto it=_set.lower_bound({0,x});
            if(it == _set.end())
                puts("-1");
            else
            {
                printf("%d\n",it->id);
                _set.erase(it);
            }
        }
        else
            _set.insert({x,a[x]});
    }
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i <= n;++i)
        scanf("%d",a+i);
    Solve();

    return 0;
}
