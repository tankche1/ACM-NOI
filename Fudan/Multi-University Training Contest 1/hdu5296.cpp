# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n,q;
int first[maxn],nex[maxn<<1],v[maxn<<1],w[maxn<<1],edge;
int Step=17;

void add_edge(int a,int b,int c){
    nex[edge]=first[a];v[edge]=b;w[edge]=c;first[a]=edge++;
}
int dep[maxn],fa[maxn],dfn[maxn],dfs_clock,rdfn[maxn],dis[maxn];
void dfs(int x){
    dfn[x]=++dfs_clock;rdfn[dfn[x]]=x;//printf("dfn[%d]:%d\n",x,dfn[x]);
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]) continue;
        dis[v[e]]=dis[x]+w[e];fa[v[e]]=x;dep[v[e]]=dep[x]+1;
        dfs(v[e]);
    }
}

int dp[maxn][18];
void prepare(){
    for(int i=1;i<=n;i++)
        dp[i][0]=fa[i];
    for(int j=1;j<=Step;j++){
        for(int i=1;i<=n;i++){

            dp[i][j]=dp[dp[i][j-1]][j-1];//printf("dp[%d][%d]:%d\n",i,j,dp[i][j]);
        }
    }
}

int Lca(int a,int b){
    //printf("a:%d b:%d\n",a,b);
    if(dep[a]>dep[b]) swap(a,b);
    if(a==b) return a;
    for(int j=Step;j>=0;j--){
        if(((dep[b]-dep[a])>>(j))&1) b=dp[b][j];
    }
    //printf("then: %d %d\n",a,b);
    int j=Step;
    while(a!=b&&j>=0){
        if(dp[a][j]!=dp[b][j]) a=dp[a][j],b=dp[b][j];
        j--;
    }
    if(a!=b) a=fa[a],b=fa[b];
    return a;
}

set<int> s;
set<int> :: iterator it1,it2;
int solve(int u){
    bool ok=true;
    it1=s.lower_bound(dfn[u]);if(it1==s.begin()) ok=false;it1--;
    it2=s.lower_bound(dfn[u]);if(it2==s.end()) ok=false;
    if(!ok){
        it1=s.begin();it2=s.end();it2--;
    }
    int x=rdfn[*it1],y=rdfn[*it2];
    //printf("%d %d\n",*it1,*it2);
    //printf("u:%d x:%d y:%d %d %d %d\n",u,x,y,Lca(u,x),Lca(u,y),Lca(x,y));
    return dis[u]-dis[Lca(u,x)]-dis[Lca(u,y)]+dis[Lca(x,y)];
}

bool used[maxn];
int main(){

    int tcase,tnum=0;
    int a,b,c;
    int op,x;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&n,&q);
        printf("Case #%d:\n",++tnum);
        memset(first,-1,sizeof(first));edge=0;
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&a,&b,&c);
            add_edge(a,b,c);add_edge(b,a,c);
        }
        dis[1]=0;fa[1]=1,dep[1]=1;dfs_clock=0;dfs(1);
        prepare();
        int num=0,ans=0;s.clear();
        memset(used,false,sizeof(used));
        for(int i=1;i<=q;i++){
            scanf("%d%d",&op,&x);
            if(op==1){
                if(used[x]){printf("%d\n",ans);continue;}
                if(num>0) ans+=solve(x);
                num++;
                s.insert(dfn[x]);used[x]=1;
                printf("%d\n",ans);
            }
            else{
                if(!used[x]) {printf("%d\n",ans);continue;}
                s.erase(dfn[x]);used[x]=0;
                num--;
                if(num>0) ans-=solve(x);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
