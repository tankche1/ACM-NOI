#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    scanf("%d",&n);
    bool flag=true;
    for (int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        if (x%3) flag=false;
    }
    puts(flag?"Yes":"No");
}

int main()
{
    //freopen("A.in","r",stdin);
    int T;
    scanf("%d",&T);
    for (int i=1;i<=T;i++)
    {
        printf("Case #%d: ",i);
        solve();
    }
    return 0;
}
