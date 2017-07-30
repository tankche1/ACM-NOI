# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=55;
const int mod=1000000007;
typedef long long LL;
int L[maxn],R[maxn];
int u[maxn<<1],v[maxn<<1],edge;
int n;
vector<int> G[maxn];
LL dp[maxn<<1][50010];
LL sum[maxn<<1][50010];
bool vis[maxn<<1];
int prime[50010][70];int op[50010][70];
int pri[1000];

void prepare(){
    int x,tmp;
    for(int i=1;i<=50000;i++){
           // printf("i:%d\n",i);
        pri[0]=0;
        prime[i][prime[i][0]=1]=1;op[i][1]=1;
        x=i;
        for(int j=2;j*j<=x;j++){
                if(x%j==0){
                    pri[++pri[0]]=j;
                    while(x%j==0) x/=j;
                }
        }
        if(x>1) pri[++pri[0]]=x;

        for(int k=1;k<(1<<pri[0]);k++){
            x=k;tmp=0;
            while(x) {tmp+=x&1;x>>=1;}
            prime[i][0]++;op[i][prime[i][0]]=(tmp&1)?-1:1;
            tmp=1;
            for(int j=1;j<=pri[0];j++){
                if((k>>(j-1))&1){
                    tmp*=pri[j];
                }
            }
            prime[i][prime[i][0]]=tmp;
        }

    }
}

void add_edge(int a,int b){
    u[edge]=a;v[edge]=b;G[a].push_back(edge);edge++;
}

void solve(int e){
    if(vis[e]) return;
    vis[e]=1;
    int x=v[e],_e;
    LL tmp;
    memset(dp[e],0,sizeof(dp[e]));
    for(int t=0;t<(int)G[x].size();t++){
        if(v[G[x][t]]!=u[e]){
            solve(G[x][t]);
        }
    }
    for(int j=L[x];j<=R[x];j++){
        dp[e][j]=1;
        for(int t=0;t<(int)G[x].size();t++){
            tmp=0;_e=G[x][t];
            if(v[_e]!=u[e]){
                for(int i=1;i<=prime[j][0];i++){
                    tmp+=op[j][i]*sum[_e][prime[j][i]];

                }
                tmp=(tmp%mod+mod);
                if(tmp>=mod) tmp-=mod;
                dp[e][j]=dp[e][j]*tmp%mod;
            }
        }
        //if(dp[e][j]>0) printf("u:%d v:%d j:%d dp:%d\n",u[e],v[e],j,dp[e][j]);
    }

    for(int i=1;i<=50000;i++){
        sum[e][i]=0;
        for(int j=i;j<=50000;j+=i){
            sum[e][i]+=dp[e][j];
        }
        if(sum[e][i]>=mod) sum[e][i]%=mod;
    }
}

LL ans[maxn];

int main(){
    int T,a,b;
    prepare();
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        edge=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&L[i]);
            G[i].clear();
        }
        for(int i=1;i<=n;i++) scanf("%d",&R[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            add_edge(a,b);add_edge(b,a);
        }

        memset(vis,0,sizeof(vis));
        for(int i=0;i<edge;i++){
            solve(i);
        }
        for(int i=1;i<=n;i++){
            ans[i]=0;
            add_edge(n+1,i);
            solve(edge-1);
            for(int j=L[i];j<=R[i];j++){
                ans[i]+=j*dp[edge-1][j];
            }
            ans[i]%=mod;
            edge--;vis[edge]=0;
        }
        printf("%lld",ans[1]);
        for(int i=2;i<=n;i++){
            printf(" %lld",ans[i]);
        }
        puts("");
    }
    return 0;
}
