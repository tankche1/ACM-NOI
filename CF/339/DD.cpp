# include<stdio.h>
# include<string.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=100010;
int first[maxn],next[maxn<<1],v[maxn<<1],edge=0;
int n;
int fa[maxn],dep[maxn];
int dfn[maxn],dfs_clock=0;

void add_edge(int a,int b){
    next[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void dfs(int x){
    dfn[x]=++dfs_clock;
    for(int e=first[x];e!=-1;e=next[e]){
        if(v[e]==fa[x]) continue;
        fa[v[e]]=x;dep[v[e]]=dep[x]+1;dfs(v[e]);
    }
}

int step=17;
int dp[maxn][20];
void prepare(){
    for(int i=1;i<=n;i++)
        dp[i][0]=fa[i];
    for(int j=1;j<=step;j++){
        for(int i=1;i<=n;i++){
            dp[i][j]=dp[dp[i][j-1]][j-1];
        }
    }
}

int Lca(int a,int b){
    //printf("a:%d b:%d \n",a,b);
    int j=step;
    if(dep[a]>dep[b]) swap(a,b);
    int t=dep[b]-dep[a];
    for(int j=step;j>=0;j--){
        if((t>>j)&1) b=dp[b][j];
    }
    while(a!=b){
        while(j>0&&dp[a][j]==dp[b][j]) j--;
        a=dp[a][j];b=dp[b][j];
    }
    return a;
}

int len,c[maxn];
bool vis[maxn];
int f[maxn][2];

bool cmp(int a,int b){
    return dfn[a]<dfn[b];
}
int S[maxn],S_top;
vector<int> G[maxn];

void query(){
    int q,t,u,v,tot;
    int nn;
    bool ok;
    scanf("%d",&q);
    for(int tt=1;tt<=q;tt++){
        ok=true;
        scanf("%d",&len);
        for(int i=1;i<=len;i++) scanf("%d",&c[i]),vis[c[i]]=1;

        for(int i=1;i<=len;i++) if(vis[fa[c[i]]]&&fa[c[i]]!=c[i]) {ok=false;break;}
        if(!ok) {puts("-1");for(int i=1;i<=len;i++) vis[c[i]]=0;continue;}

        sort(c+1,c+len+1,cmp);nn=len;
        for(int i=2;i<=len;i++) t=Lca(c[i-1],c[i]),c[++nn]=t;
        sort(c+1,c+nn+1,cmp);c[0]=-1;int nnn=0;
        for(int i=1;i<=nn;i++){
            if(c[i]!=c[i-1]) c[++nnn]=c[i];
        }nn=nnn;
        S[S_top=0]=c[1];
        for(int i=2;i<=nn;i++){
            t=Lca(c[i],S[S_top]);
            while(dep[t]<dep[S[S_top]]) S_top--;
            G[S[S_top]].push_back(c[i]);
            S[++S_top]=c[i];
        }

        for(int p=nn;p>=1;p--){
            u=c[p];
            if((int)G[u].size()==0){
                f[u][0]=INF;f[u][1]=0;
            }
            else{
                if(vis[u]){
                    f[u][0]=INF;f[u][1]=0;
                    for(int e=0;e<G[u].size();e++){
                        v=G[u][e];
                        f[u][1]+=min(f[v][0],f[v][1]+1);
                    }
                }
                else{
                    f[u][0]=0;tot=0;f[u][1]=0;
                    for(int e=0;e<G[u].size();e++){
                        v=G[u][e];
                        f[u][0]+=min(f[v][0],f[v][1]+1);tot+=min(f[v][0],f[v][1]);
                    }f[u][1]=INF;
                    for(int e=0;e<G[u].size();e++){
                        v=G[u][e];
                        f[u][1]=min(f[u][1],f[u][0]-min(f[v][0],f[v][1]+1)+f[v][1]);
                    }
                    f[u][0]=min(f[u][0],tot+1);
                }
            }
        }
        printf("%d\n",min(f[c[1]][0],f[c[1]][1]));
        for(int i=1;i<=nn;i++) G[c[i]].clear(),vis[c[i]]=0;
        for(int i=1;i<=nn;i++) vis[c[i]]=0;
    }
}

int main(){
    int a,b,q;
    scanf("%d",&n);
    memset(first,-1,sizeof(first));edge=0;
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);
    }
    fa[1]=1;dep[1]=1;dfs(1);

    prepare();
    query();
    return 0;
}
