#include <bits/stdc++.h>
using namespace std;

const int MAXN=100005;

int a[MAXN];

void solve()
{
    int n,c;
    scanf("%d%d",&n,&c);
    for (int i=1,t;i<=n;i++) scanf("%d%d%d",&a[i],&t,&t);
    sort(a+1,a+n+1);
    int q;
    scanf("%d",&q);
    for (int t,k;q--;)
    {
        scanf("%d%d",&t,&k);
        int v=a[k];
        printf("%.3f\n",sqrt(1LL*v*v+2LL*t*c));
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
