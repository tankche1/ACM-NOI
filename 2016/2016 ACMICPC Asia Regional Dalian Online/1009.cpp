#include <bits/stdc++.h>
using namespace std;

typedef pair <int,int> pii;

#define mp make_pair

const int MAXN=200005;

int p[MAXN],d[MAXN];
queue <int> q;
set <pii> s;

int find(int x)
{
    return p[x]==x?x:p[x]=find(p[x]);
}

void solve()
{
    int n,m;
    scanf("%d%d",&n,&m);
    s.clear();
    while (m--)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        s.insert(mp(u,v));
        s.insert(mp(v,u));
    }
    int S;
    scanf("%d",&S);
    q.push(S);
    for (int i=1;i<=n;i++) p[i]=i;
    p[n+1]=n+1;
    p[S]=S+1;
    for (int i=1;i<=n;i++) d[i]=-1;
    d[S]=0;
    while (!q.empty())
    {
        int u=q.front();q.pop();
        for (int i=find(1);i<=n;i=find(i+1))
        {
            if (s.find(mp(u,i))!=s.end()) continue;
            d[i]=d[u]+1;
            p[i]=i+1;
            q.push(i);
        }
    }
    int last;
    for (int i=n;i>=1;i--)
        if (i!=S)
        {
            last=i;
            break;
        }
    for (int i=1;i<=n;i++)
        if (i!=S)
        {
            printf("%d",d[i]);
            if (i!=last) putchar(' ');
        }
    puts("");
}

int main()
{
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
