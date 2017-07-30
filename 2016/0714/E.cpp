# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
bool vis[maxn<<1];
int n,m,Q;
int u[maxn<<1],v[maxn<<1];
int p[maxn];
int ans;
int dep[maxn],fa[maxn];
vector<int> G[maxn];

int find(int x){
    if(x==p[x]) return x;
    return p[x]=find(p[x]);
}

void deal(int a,int b){
    int px=find(a),py=find(b);
    while(px!=py){
        if(dep[px]<dep[py]) swap(px,py);
        ans--;p[px]=fa[px];px=find(px);
    }
}

void dfs(int x){
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa[x]) continue;
        dep[G[x][e]]=dep[x]+1;fa[G[x][e]]=x;dfs(G[x][e]);
    }
}

int main(){
    int Tcase=0,x,y;
    while(scanf("%d%d",&n,&m)!=EOF){
        if(n==0&&m==0) break;
        for(int i=1;i<=m;i++)
            scanf("%d%d",&u[i],&v[i]);
        for(int i=1;i<=n;i++) p[i]=i,G[i].clear();
        memset(vis,false,sizeof(vis));

        for(int i=1;i<=m;i++){
            int px=find(u[i]),py=find(v[i]);
            if(px==py) vis[i]=true;
            else {p[px]=py;G[u[i]].push_back(v[i]);G[v[i]].push_back(u[i]);}
        }

        for(int i=1;i<=n;i++) p[i]=i;
        dep[1]=0;fa[1]=1;dfs(1);

        ans=n-1;
        for(int i=1;i<=m;i++){
            if(vis[i]){
                deal(u[i],v[i]);
            }
        }

        printf("Case %d:\n",++Tcase);
        scanf("%d",&Q);
        for(int i=1;i<=Q;i++){
            scanf("%d%d",&x,&y);deal(x,y);
            printf("%d\n",ans);

        }
        puts("");
    }
    return 0;
}
