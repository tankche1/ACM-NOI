#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<list>
#define maxn 10010
#define mod 21092013
using namespace std;
typedef long long LL;
list<int>map[maxn];
LL f[maxn][55];
LL ans[55];
int n;
int l[maxn],r[maxn];
int GCD[55][55];
int gcd(int a,int b)
{
    int c=a;
    while(b)
    {
        a=b;
        b=c%b;
        c=a;
    }
    return a;
}
void DFS(int u,int fa)
{
    for(int i=l[u];i<=r[u];++i)
    {
        f[u][i]=1;
        ans[i]=(ans[i]+1)%mod;
    }
    for(list<int>::iterator p=map[u].begin();p!=map[u].end();p++)
        if(*p!=fa)
        {
            DFS(*p,u);
            for(int i=1;i<=50;++i)
                for(int j=1;j<=50;++j)
                {
                    int k=GCD[i][j];
                    ans[k]=(ans[k]+f[u][i]*f[*p][j]%mod)%mod;
                }
            for(int i=l[u];i<=r[u];++i)
                for(int j=1;j<=50;++j)
                {
                    int k=GCD[i][j];
                    f[u][k]=(f[u][k]+f[*p][j])%mod;
                }
        }
    return ;
}
int main()
{
    int T;
    cin>>T;
    for(int i=1;i<=50;++i)
        for(int j=1;j<=50;++j)
            GCD[i][j]=gcd(i,j);
    for(int ii=1;ii<=T;++ii)
    {
        printf("Case %d:\n",ii);
        scanf("%d",&n);
        for(int i=1;i<n;++i)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            map[u].push_back(v);
            map[v].push_back(u);
        }
        for(int i=1;i<=n;++i)
            scanf("%d",l+i);
        for(int i=1;i<=n;++i)
            scanf("%d",r+i);
        DFS(1,0);
        for(int i=1;i<=50;++i)
            printf("%d: %lld\n",i,ans[i]%mod);
        memset(ans,0,sizeof ans);
        memset(f,0,sizeof f);
        for(int i=1;i<=n;++i) map[i].clear();
    }
}
