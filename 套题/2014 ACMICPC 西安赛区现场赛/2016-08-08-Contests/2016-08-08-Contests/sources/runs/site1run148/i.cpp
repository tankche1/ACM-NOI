#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;
using namespace std;
int go[2000010][2];
int ans[2000010][6],a[5];
bool v[2000010];
int cas,l,n,t,m;
void add(int l)
{
    int k=0;
    for (int i=1; i<=4;i++)
    {
      for (int j=7;j>=0; j--)
      {
        int x=0;
        if (a[i]&(1<<j)) x=1;
        if (!go[k][x]) {go[k][x]=++t;memset(go[t],0,sizeof(go[t]));v[t]=0;}
        k=go[k][x];
        if (--l==0) {v[k]=1;return;}
      }
    }
}

void put(ll st,int l)
{
    ++m;
    memset(ans[m],0,sizeof(ans[m]));
    ans[m][5]=l;
    int j=1,k=8;
    for (int i=31;i>=0;i--)
    {
        --k;
        if (k<0) {k=7;++j;}
        if ((st&(1ll<<i))>0) ans[m][j]|=1<<k;
        if (--l==0) return;
    }
}

void dfs(int k,int i,ll st)
{
    if (i==-1) return;
    if (v[k]) return;
    if (go[k][0]) dfs(go[k][0],i-1,st);
    else put(st,32-i);
    if (go[k][1]) dfs(go[k][1],i-1,st+(1ll<<i));
    else put(st+(1ll<<i),32-i);
}

int main()
{
    scanf("%d",&cas);
    for (int tt=1;tt<=cas; tt++)
    {
        scanf("%d",&n);
        if (n==0)
        {
            printf("Case #%d:\n1\n0.0.0.0/0\n",tt);
            continue;
        }
        t=0; go[0][0]=go[0][1]=0;
        bool f=0;
        for (int i=1; i<=n; i++)
        {
          scanf("%d.%d.%d.%d/%d",&a[1],&a[2],&a[3],&a[4],&l);
          if (l==0) f=1;
          else add(l);
        }
        printf("Case #%d:\n",tt);
        if (f) {puts("0*");continue;}
        m=0;
        dfs(0,31,0);
        cout <<m<<endl;
        for (int i=1; i<=m; i++)
        {
          printf("%d",ans[i][1]);
          for (int j=2; j<=4; j++)
            printf(".%d",ans[i][j]);
          printf("/%d\n",ans[i][5]);
        }
    }
    return 0;
}

