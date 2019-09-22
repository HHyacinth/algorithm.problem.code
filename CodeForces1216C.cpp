#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

int num;
struct Point
{
    int x1,y1;
    int x2,y2;
}p[10];
struct Data
{
    int a;
    int b,c;
    int f;
    int id;
    bool operator < (const Data& obj)const
    {
        return a < obj.a;
    }
}line[20],white[2];
multiset<int >_set;

void update(int &b,int &c)
{
    if(!_set.empty())
    {
        b=*_set.begin();
        auto it=_set.end();
        it--;
        c=*it;
    }
}
bool isCover()
{
    _set.clear();
    sort(line+1,line+num+1);

    int index=1;
    while(index <= num)
    {
        int cur=index;
        for(;cur <= num && line[cur].a == line[index].a;cur++);

        int b=INF;
        int c=-1;
        update(b,c);
        
        if(white[0].a < line[index].a && !(white[0].b >= b && white[0].c <= c))
            return false;///未完全被覆盖

        for(int i=index;i < cur;++i)
            if(line[i].id != 1 && line[i].f == 1)
            {
                _set.insert(line[i].b);
                _set.insert(line[i].c);
            }

        update(b,c);
        ///来到white矩形的右边（或上边），判断是否被完全覆盖
        if(white[1].a == line[index].a)
            return white[1].b >= b && white[1].c <= c ? true:false;

        for(int i=index;i < cur;++i)
            if(line[i].id != 1 && line[i].f == -1)
            {
                _set.erase(_set.find(line[i].b));
                _set.erase(_set.find(line[i].c));
            }
        index=cur;
    }
}
char *Solve()
{
    ///先扫描x，并判断是否将white的竖直边完全覆盖
    num=0;
    for(int i=1;i <= 3;++i)
    {
        line[++num]={p[i].x1,p[i].y1,p[i].y2,1,i};
        line[++num]={p[i].x2,p[i].y1,p[i].y2,-1,i};
    }
    white[0]={p[1].x1,p[1].y1,p[1].y2,1,1};
    white[1]={p[1].x2,p[1].y1,p[1].y2,-1,1};

    if(!isCover())
        return "YES";

    ///在扫描y，并判断是否将white的水平边完全覆盖
    num=0;
    for(int i=1;i <= 3;++i)
    {
        line[++num]={p[i].y1,p[i].x1,p[i].x2,1,i};
        line[++num]={p[i].y2,p[i].x1,p[i].x2,-1,i};
    }
    white[0]={p[1].y1,p[1].x1,p[1].x2,1,1};
    white[1]={p[1].y2,p[1].x1,p[1].x2,-1,1};

    if(!isCover())
        return "YES";

    ///只有竖直边和水平边都被完全覆盖时，才能说明矩形1被矩形2，3完全覆盖
    return "NO";
}
int main()
{
//    freopen("C:\\Users\\hyacinthLJP\\Desktop\\C++WorkSpace\\in&&out\\contest","r",stdin);
    for(int i=1;i <= 3;++i)
        scanf("%d%d%d%d",&p[i].x1,&p[i].y1,&p[i].x2,&p[i].y2);
    puts(Solve());

    return 0;
}
