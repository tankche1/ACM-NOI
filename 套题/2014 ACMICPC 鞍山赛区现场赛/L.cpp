# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
vector<int> Tree[maxn];
int n,m;
int fa[maxn];
int fail[maxn];

int G[maxn][27];

int q[maxn];

int Step=17,dp[maxn][19];
void get_Fail(){
    int l,r,x,t;
    for(q[l=r=1]=0;l<=r;l++){
        x=q[l];
        for(int e=0;e<26;e++){
            if(!G[x][e]) continue;
            q[++r]=G[x][e];
        }
    }

    fail[0]=0;
    for(int i=0;i<26;i++) fail[G[0][i]]=0;
    for(int i=2;i<=r;i++){
        x=q[i];
        for(int c=0;c<26;c++){
            int u=G[x][c];
            if(!u) {G[x][c]=G[fail[x]][c];continue;}
            fail[u]=G[fail[x]][c];
        }
    }

    for(int i=0;i<n;i++) Tree[i].clear();
    for(int i=0;i<n;i++) {
            fa[i]=dp[i][0]=fail[i];
            if(i>0) Tree[fa[i]].push_back(i);
            //printf("fa[%d]:%d\n",i,fa[i]);
    }
    for(int j=1;j<=Step;j++){
        for(int i=0;i<n;i++){
            dp[i][j]=dp[dp[i][j-1]][j-1];
        }
    }

}

int dep[maxn],dfs_clock,L[maxn],R[maxn];
void dfs(int x){
    L[x]=++dfs_clock;
    for(int e=0;e<(int)Tree[x].size();e++){
        dep[Tree[x][e]]=dep[x]+1;
        dfs(Tree[x][e]);
    }
    R[x]=++dfs_clock;
    //printf("x:%d L:%d R:%d\n",x,L[x],R[x]);
}

int query[maxn];

bool cmp(int a,int b){
    return L[a]<L[b];
}

int Lca(int a,int b){
    if(dep[a]<dep[b]) swap(a,b);
    int j=dep[a]-dep[b],k=0;
    while(j>0){
        if(j&1) a=dp[a][k];
        j>>=1;k++;
    }
    j=Step;
    while(a!=b){
        while(dp[a][j]==dp[b][j]&&j>0) j--;
        a=dp[a][j];b=dp[b][j];
    }
    return a;
}

inline int lowbit(int x) { return x&(-x);}

struct FenwickTree{
    LL C[maxn<<1];
    int n;

    void init(int nn){
        n=nn;
        for(int i=1;i<=n;i++) C[i]=0;
    }

    void insert(int x,int v){
        while(x<=n){
            C[x]+=v;x+=lowbit(x);
        }
    }

    LL sum(int x){
        LL res=0;
        while(x>0){
            res+=C[x];x-=lowbit(x);
        }
        return res;
    }
}fwt1,fwt2;

LL calc(int t){
    //("t:%d fwt1:%I64d fwt2:%I64d\n",t,fwt1.sum(L[t]),fwt2.sum(L[t]));
    return fwt1.sum(L[t])+(LL)dep[t]*fwt2.sum(L[t]);
}

int main(){
    int T;
    char t;
    int K,op,len;
    LL ans;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=0;i<=n;i++) memset(G[i],0,sizeof(G[i]));
        for(int i=1;i<n;i++){
            scanf("%d",&fa[i]);fa[i]--;
            while((t=getchar())&&(t<'a'||t>'z'));
            G[fa[i]][t-'a']=i;
        }

        get_Fail();
        dep[0]=1;dfs_clock=0;dfs(0);

        scanf("%d",&m);
        fwt1.init(dfs_clock);fwt2.init(dfs_clock);
        for(int tt=1;tt<=m;tt++){
            scanf("%d%d",&op,&K);
            for(int i=1;i<=K;i++) scanf("%d",&query[i]),query[i]--;
            sort(query+1,query+K+1,cmp);

            if(op==1){
                len=1;
                for(int i=2;i<=K;i++){
                    if(R[query[len]]>L[query[i]]) continue;
                    query[++len]=query[i];
                }

                for(int i=1;i<=len;i++){
                    fwt1.insert(L[query[i]],1-dep[query[i]]);fwt1.insert(R[query[i]],dep[query[i]]-1);
                    fwt2.insert(L[query[i]],1);fwt2.insert(R[query[i]],-1);
                }
            }
            else{
                int t=query[1];ans=0;len=K;
                for(int i=1;i<=len;i++){
                    if(i>1) t=Lca(query[i],query[i-1]);
                    ans+=calc(query[i]);
                    if(i>1) ans-=calc(t);
                }
                printf("%I64d\n",ans);
            }
        }
    }
    return 0;
}
