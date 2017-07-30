# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=200010;
const int mod=1000000007;
typedef long long LL;
vector<int> G[maxn];
int n,m;
LL dp[maxn];
int w[maxn],low[maxn],pre[maxn],dfs_clock,fa[maxn],belong[maxn];
bool iscut[maxn];

int first[maxn],_next[maxm<<1],v[maxm<<1],edge;

void add_edge(int a,int b){
    _next[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void dfs(int x){
    //printf("x:%d\n",x);
    low[x]=pre[x]=++dfs_clock;
    int sz=0;
    for(int e=first[x];e!=-1;e=_next[e]){
        if(v[e]==fa[x]) continue;
        if(!pre[v[e]]){
            G[x].push_back(v[e]);sz++;
            belong[v[e]]=belong[x];
            fa[v[e]]=x;dfs(v[e]);
            low[x]=min(low[x],low[v[e]]);
            if(low[v[e]]>=pre[x]&&fa[x]!=-1){
                iscut[x]=1;
            }
        }
        else{
            low[x]=min(low[x],pre[v[e]]);
        }
    }

    if(fa[x]==-1&&sz>1) iscut[x]=1;
}

void get_dp(int x){
    dp[x]=w[x];
    //printf("xx:%d fa:%d\n",x,fa[x]);//int aa;scanf("%d",&aa);
    for(int e=0;e<(int)G[x].size();e++){
        //if(G[x][e]==fa[x]) continue;
        get_dp(G[x][e]);
        dp[x]=dp[x]*dp[G[x][e]]%mod;
    }
}

LL fast_pow(int a,int b){
    LL res=1,tmp=a;
    while(b>0){
        if(b&1) res=res*tmp%mod;
        b>>=1;tmp=tmp*tmp%mod;
    }
    return res;
}

LL inv(int a){
    return fast_pow(a,mod-2);
}

int main(){
    freopen("1006.in","r",stdin);
    freopen("output.txt","w",stdout);
    int Case,a,b;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d%d",&n,&m);
        //printf("Tcase:%d n:%d m:%d\n",Tcase,n,m);
        for(int i=1;i<=n;i++) scanf("%d",&w[i]),G[i].clear();
        memset(first,-1,sizeof(first));edge=0;
        for(int i=1;i<=m;i++) {
            scanf("%d%d",&a,&b);//G[a].push_back(b);G[b].push_back(a);
            add_edge(a,b);add_edge(b,a);
        }

        LL tot=0;
        dfs_clock=0;
        memset(pre,0,sizeof(pre));memset(iscut,0,sizeof(iscut));
        for(int i=1;i<=n;i++) if(!pre[i]) {fa[i]=-1,belong[i]=i,dfs(i);get_dp(i),tot+=dp[i];}
        tot%=mod;

        //puts("what!");

        LL sum=0;
        LL ans;
        LL tmp;
        for(int i=1;i<=n;i++){
            if(!iscut[i]){
                if((int)G[belong[i]].size()==0&&fa[i]==-1) ans=(tot-dp[belong[i]]+mod)%mod;
                else ans=(tot-dp[belong[i]]+dp[belong[i]]*inv(w[i])+mod)%mod;
            }
            else{
                ans=tot-dp[belong[i]];
                tmp=dp[belong[i]]*inv(w[i])%mod;
                //if(fa[i]!=-1) ans+=dp[belong[i]]*inv(dp[i])%mod;
                for(int e=0;e<(int)G[i].size();e++){
                    if(low[G[i][e]]>=pre[i])
                    {//printf("add:%d\n",G[i][e]);
                    ans+=dp[G[i][e]];tmp=tmp*inv(dp[G[i][e]])%mod;
                    }
                }
                if(fa[i]!=-1) ans+=tmp;
                ans=(ans%mod+mod)%mod;
            }
            //printf("i:%d ans:%I64d iscut:%d\n",i,ans,iscut[i]);
            sum=(sum+ans*i)%mod;
        }

        //printf("Case %d:%I64d\n",Tcase,sum);
        printf("%I64d\n",sum);
    }
    return 0;
}
