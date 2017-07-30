#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <list>
#define maxn 110
using namespace std;
list<int>map[maxn];
int f[maxn][maxn][2];
bool vis[maxn][maxn][2];
int n,m;
int DFS(int i,int j,bool k)
{
    if(f[i][j][k]!=-1) return f[i][j][k];
    if(i==j) return f[i][j][k]=1;
    if(vis[i][j][k]) return 0;
    vis[i][j][k]=true;
    if(k==0)
    {
        for(list<int>::iterator p=map[i].begin();p!=map[i].end();p++)
            if(DFS(*p,j,k^1)==0) f[i][j][k]=0;
        if(f[i][j][k]==-1) f[i][j][k]=1;
    }
    else
    {
        for(list<int>::iterator p=map[j].begin();p!=map[j].end();p++)
            if(DFS(i,*p,k^1)==1) f[i][j][k]=1;
        if(f[i][j][k]==-1) f[i][j][k]=0;
    }
    vis[i][j][k]=false;
    return f[i][j][k];
}
int main()
{
    int T;
    cin>>T;
    for(int ii=1;ii<=T;++ii)
    {
        printf("Case #%d: ",ii);
        memset(f,-1,sizeof f);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;++i)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            map[u].push_back(v);
        }
        int x,y;
        scanf("%d%d",&x,&y);
        if(DFS(x,y,0)==0) printf("Yes\n");
        else printf("No\n");
        for(int i=1;i<=n;++i)
            map[i].clear();
    }
    return 0;
}
