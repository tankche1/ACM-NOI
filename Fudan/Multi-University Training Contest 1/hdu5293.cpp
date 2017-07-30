# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
#pragma comment(linker, "/STACK:1024000000,1024000000")
const int maxn=100010;
typedef long long LL;
vector<int> G[maxn];
int Step=17;
int n,m;
int first[maxn],nex[maxn<<1],v[maxn<<1];
int edge;

void add_edge(int a,int b){
    nex[edge]=first[a];v[edge]=b;first[a]=edge++;
}

int st[maxn],ed[maxn],top[maxn],w[maxn];
int dfs_clock,dfn[maxn],dfnL[maxn],dfnR[maxn];
int fa[maxn],dep[maxn];

void dfs(int x){
    dfn[x]=++dfs_clock;dfnL[x]=dfn[x];
    //printf("fa[%d]:%d\n",x,fa[x]);
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]) continue;
        dep[v[e]]=dep[x]+1;fa[v[e]]=x;dfs(v[e]);
    }
    dfnR[x]=dfs_clock;
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

struct SegmenTree{
    LL sum[maxn<<2];
    LL lazy[maxn<<2];

    void pushdown(int o,int L,int R){
        if(lazy[o]!=0){
            int M=(L+R)>>1;
            lazy[o<<1]+=lazy[o];lazy[o<<1|1]+=lazy[o];
            if(L==M) sum[o<<1]+=lazy[o];if(M+1==R) sum[o<<1|1]+=lazy[o];
            lazy[o]=0;
        }
    }

    void build(int o,int L,int R){
        lazy[o]=0;sum[o]=0;
        if(L==R) return;
        int M=(L+R)>>1;
        build(o<<1,L,M);build(o<<1|1,M+1,R);
    }

    void update(int o,int L,int R,int qL,int qR,LL val){
        if(qL<=L&&qR>=R){
            if(L==R)sum[o]+=val;
            lazy[o]+=val;return;
        }
        pushdown(o,L,R);
        int M=(L+R)>>1;
        if(qL<=M) update(o<<1,L,M,qL,qR,val);
        if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
    }

    LL query(int o,int L,int R,int pos){
        if(L==R) return sum[o];
        pushdown(o,L,R);
        int M=(L+R)>>1;
        if(pos<=M) return query(o<<1,L,M,pos);
        else return query(o<<1|1,M+1,R,pos);
    }
}seg,seg2;

LL d[maxn];
LL sumd[maxn];
void Tree_dp(int x){
    sumd[x]=0;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(fa[x]==v[e]) continue;
        Tree_dp(v[e]);sumd[x]+=d[v[e]];
    }
    d[x]=sumd[x];

    for(int j=0,i;j<(int)G[x].size();j++){
        i=G[x][j];
        //printf("st:%d seg:%d ed:%d seg:%d x:%d seg:%d\n",st[i],seg.query(1,1,n,dfn[st[i]]),ed[i],seg.query(1,1,n,dfn[ed[i]]),top[i],seg.query(1,1,n,dfn[top[i]]));
        //printf("i:%d w:%d val:%d\n",i,w[i],w[i]+sumd[x]+seg.query(1,1,n,dfn[st[i]])+seg.query(1,1,n,dfn[ed[i]])-seg2.query(1,1,n,dfn[st[i]])-seg2.query(1,1,n,dfn[ed[i]]));
        //if(x==1)
        //    printf("%I64d %I64d %I64d %I64d %I64d %I64d\n",(LL)w[i],sumd[x],seg.query(1,1,n,dfn[st[i]]),seg.query(1,1,n,dfn[ed[i]]),seg2.query(1,1,n,dfn[st[i]]),seg2.query(1,1,n,dfn[ed[i]]));
        d[x]=max(d[x],(LL)sumd[x]+seg.query(1,1,n,dfn[st[i]])-seg2.query(1,1,n,dfn[st[i]])+seg.query(1,1,n,dfn[ed[i]])-seg2.query(1,1,n,dfn[ed[i]])+w[i]);
    }
    seg.update(1,1,n,dfnL[x],dfnR[x],sumd[x]);
    seg2.update(1,1,n,dfnL[x],dfnR[x],d[x]);
    //if(d[x]>178288) printf("d[%d]:%I64d sumd:%d\n",x,d[x],sumd[x]);;
}

int main(){
    //freopen("input.txt","r",stdin);
    int tcase,a,b;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&n,&m);
        memset(first,-1,sizeof(first));edge=0;
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);
        }
        for(int i=1;i<=n;i++) G[i].clear();
        dep[1]=1;fa[1]=1;dfs_clock=0;
        dfs(1);
        prepare();
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&st[i],&ed[i],&w[i]);
            top[i]=Lca(st[i],ed[i]);G[top[i]].push_back(i);
            //printf("top:%d\n",top[i]);
        }
        seg.build(1,1,n);seg2.build(1,1,n);
        Tree_dp(1);
        printf("%I64d\n",d[1]);
    }
    return 0;
}
