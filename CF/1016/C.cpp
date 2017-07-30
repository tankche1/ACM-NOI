# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int Step=17;
int n,m,q;
int dp[maxn][18][11];
int f[maxn][18];
int first[maxn],nex[maxn<<1],v[maxn<<1],edge=0;
void add_edge(int a,int b){
    nex[edge]=first[a];v[edge]=b;first[a]=edge++;
}
int fa[maxn],dep[maxn];

void dfs(int x){
    for(int e=first[x];e!=-1;e=nex[e]){
        if(fa[x]==v[e]) continue;
        fa[v[e]]=x;dep[v[e]]=dep[x]+1;
        dfs(v[e]);
    }
}

void prepare(){
    for(int i=1;i<=n;i++)
        f[i][0]=fa[i];
    for(int j=1;j<=Step;j++){
        for(int i=1;i<=n;i++){
            f[i][j]=f[f[i][j-1]][j-1];//printf("dp[%d][%d]:%d\n",i,j,dp[i][j]);
        }
    }
}

int Lca(int a,int b){
    if(dep[a]>dep[b]) swap(a,b);
    if(a==b) return a;
    for(int j=Step;j>=0;j--){
        if(((dep[b]-dep[a])>>(j))&1) b=f[b][j];
    }
    int j=Step;
    while(a!=b&&j>=0){
        if(f[a][j]!=f[b][j]) a=f[a][j],b=f[b][j];
        j--;
    }
    if(a!=b) a=fa[a],b=fa[b];
    return a;
}

int tank[30];
void Union(int i1,int j1,int i2,int j2){
    tank[0]=0;
    for(int i=1;i<=dp[i1][j1][0];i++)
        tank[++tank[0]]=dp[i1][j1][i];
    for(int i=1;i<=dp[i2][j2][0];i++)
        tank[++tank[0]]=dp[i2][j2][i];
    sort(tank+1,tank+tank[0]+1);
    int i,len=0;
    for(i=1;i<=tank[0];i++){
        if(i==1||tank[i]!=tank[i-1]) tank[++len]=tank[i];
    }
    tank[0]=min(len,10);
}

void predp(){
    for(int j=1;j<=Step;j++){
        for(int i=1;i<=n;i++){
            Union(i,j-1,f[i][j-1],j-1);
            for(int k=0;k<=tank[0];k++)
                dp[i][j][k]=tank[k];
        }
    }
}
int ans[30];

void get(int x,int j,int a){
    for(int i=1;i<=dp[x][j][0];i++)
        ans[++ans[0]]=dp[x][j][i];
    sort(ans+1,ans+ans[0]+1);
    int i,len=0;
    for(i=1;i<=ans[0];i++){
        if(i==1||ans[i]!=ans[i-1]) ans[++len]=ans[i];
    }
    len=min(len,a);
    ans[0]=len;
    return;
}

void solve(int x,int y,int a){
    int len=dep[x]-dep[y]+1;
    //printf("x:%d y:%d len:%d\n",x,y,len);
    for(int j=Step;j>=0;j--){
        if((len>>j)&1) get(x,j,a),x=f[x][j];
    }
}

int main(){
    int a,b;
    int u,v,t;
    scanf("%d%d%d",&n,&m,&q);
    memset(first,-1,sizeof(first));edge=0;
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);
    }
    fa[1]=1;dfs(1);
    prepare();
    for(int i=1;i<=m;i++){
        scanf("%d",&a);
        if(dp[a][0][0]<10)
            dp[a][0][++dp[a][0][0]]=i;
    }
    predp();
    for(int i=1;i<=q;i++){
        scanf("%d%d%d",&u,&v,&a);
        t=Lca(u,v);
        //printf("t:%d\n",t);
        ans[0]=0;
        solve(u,t,a);
        solve(v,t,a);
        printf("%d",ans[0]);
        for(int i=1;i<=ans[0];i++)
            printf(" %d",ans[i]);
        puts("");
    }
    return 0;
}
