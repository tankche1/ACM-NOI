# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=510;
vector<int> G[maxn];
int n,m;
int p[maxn];
int g[maxn][maxn],f[maxn][maxn];

int u[maxn],v[maxn],ti[maxn];

int pos[maxn];

int T[maxn],tblock;
int left[maxn];

bool dfs(int x){
    for(int e=0;e<(int)G[x].size();e++){
        if(T[G[x][e]]==tblock) continue;T[G[x][e]]=tblock;
        if((!left[G[x][e]])||dfs(left[G[x][e]])){
            left[G[x][e]]=x;return true;
        }
    }
    return false;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i]);

    memset(f[0],0,sizeof(f[0]));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&g[i][j]);
            if(i!=j) g[i][j]+=p[j];
            f[i][j]=g[i][j];
        }
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(f[i][k]+f[k][j]<f[i][j]) f[i][j]=f[i][k]+f[k][j];
            }
        }
    }

    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u[i],&v[i],&ti[i]);
    }

    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            if(ti[i]+g[u[i]][v[i]]+f[v[i]][u[j]]<=ti[j]) G[i].push_back(j);
        }
    }

    memset(left,0,sizeof(left));
    tblock=0;
    int ans=m;
    for(int i=1;i<=m;i++){
        tblock++;
        ans-=dfs(i);
    }
    printf("%d\n",ans);
    return 0;
}
