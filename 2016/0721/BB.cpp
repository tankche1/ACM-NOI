# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=(1<<16)+5;
const int maxbit=(1<<8)+5;
int mod=1000000007;
int n,w[maxn],fa[maxn];
int op;
char ops[10];
vector<int> G[maxn];
long long ds[maxbit][maxbit];
long long dp[maxn];
long long backup[maxn][maxbit];

int calc(int a,int b){
    if(op==1) return a&b;
    else if(op==2) return a^b;
    else return a|b;
}

int Tcase;

int cur[maxn];
bool vis[maxn];
int S[maxn],top;

void solve(){
    int x,o,a,b;
    top=-1;S[++top]=1;
    memset(cur,0,sizeof(cur));memset(vis,0,sizeof(vis));
    while(top>=0){
        Loop:
        o=S[top];a=w[o]>>8,b=w[o]&((1<<8)-1);
        //printf("o:%d\n",o);
        if(!vis[o]){
            vis[o]=1;
            dp[o]=0;
            if(o==1){
                dp[o]=0;
            }
            else{
                for(int i=0;i<(1<<8);i++){
                    if(ds[i][a]!=-1)
                        dp[o]=max(dp[o],ds[i][a]+((calc(i,b))));
                }
            }


            for(int i=0;i<(1<<8);i++){
                if(dp[o]+(calc(a,i)<<8)>ds[b][i]||ds[b][i]==-1){
                    backup[o][i]=ds[b][i];
                    ds[b][i]=dp[o]+(calc(a,i)<<8);
                }
            }
        }

        for(;cur[o]<(int)G[o].size();){
            S[++top]=G[o][cur[o]];cur[o]++;goto Loop;
        }

        for(int i=0;i<256;i++){
            ds[b][i]=backup[o][i];
        }

        top--;
    }
}

long long ans;
int main(){
    freopen("1002.in","r",stdin);
    freopen("output.b","w",stdout);
    //freopen("input.txt","r",stdin);
    int T;
    scanf("%d",&T);
    for(Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%s",&n,ops);
        for(int i=1;i<=n;i++) G[i].clear();
        if(ops[0]=='A') op=1;
        else if(ops[0]=='X') op=2;
        else op=3;

        for(int i=1;i<=n;i++) scanf("%d",&w[i]);
        for(int i=2;i<=n;i++){
            scanf("%d",&fa[i]);G[fa[i]].push_back(i);
        }

        for(int i=0;i<(1<<8);i++) for(int j=0;j<(1<<8);j++) ds[i][j]=-1;


        //dfs(1);
        solve();
        ans=0;
        for(int i=1;i<=n;i++){
            ans+=((long long)dp[i]+w[i])*i;
            if(ans>=mod) ans%=mod;
        }
        ans%=mod;
        printf("%d:%I64d\n",Tcase,ans);
    }

    return 0;
}
