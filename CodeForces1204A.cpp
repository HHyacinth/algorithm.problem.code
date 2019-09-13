#include<bits/stdc++.h>
using namespace std;
const int maxn=100+50;

char s[maxn];

int Solve()
{
    int len=strlen(s+1);

    if(len%2 == 0)
        return len/2;

    int ans=(len-1)/2;
    for(int i=2;i <= len;++i)
        if(s[i] == '1')///如果非最高位出现1，说明 s > 4^((k-1)/2)
        {
            ans++;
            break;
        }

    return ans;
}
int main()
{
    scanf("%s",s+1);
    printf("%d\n",Solve());

    return 0;
}
