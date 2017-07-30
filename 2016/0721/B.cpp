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

void dfs(int o){
    //if(Tcase==245&&o>=25960) printf("o:%d\n",o);
    int a=w[o]>>8,b=w[o]&((1<<8)-1);
    dp[o]=0;
    if(o==1){
        dp[o]=0;
    }
    else{
        for(int x=0;x<(1<<8);x++){
            if(ds[x][b]!=-1)
                dp[o]=max(dp[o],ds[x][b]+((calc(x,a))<<8));
        }
    }


    for(int y=0;y<(1<<8);y++){
        if(dp[o]+calc(b,y)>ds[a][y]||ds[a][y]==-1){
            backup[o][y]=ds[a][y];
            ds[a][y]=dp[o]+calc(b,y);
        }
    }

    for(int e=0;e<(int)G[o].size();e++){
        dfs(G[o][e]);
    }

    for(int y=0;y<256;y++){
        ds[a][y]=backup[o][y];
    }

    return;
}

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
            for(int x=0;x<(1<<8);x++){
                if(ds[x][b]!=-1)
                    dp[o]=max(dp[o],ds[x][b]+((calc(x,a))<<8));
            }
            //printf("dp[%d]:%I64d\n",o,dp[o]);


            for(int y=0;y<(1<<8);y++){
                    backup[o][y]=ds[a][y];
                if(dp[o]+calc(b,y)>ds[a][y]||ds[a][y]==-1){

                    ds[a][y]=dp[o]+calc(b,y);
                }
            }
        }

        for(;cur[o]<(int)G[o].size();){
            S[++top]=G[o][cur[o]];cur[o]++;goto Loop;
        }

        for(int y=0;y<256;y++){
            ds[a][y]=backup[o][y];
        }

        top--;
    }
}

long long ans;
int main(){
    //freopen("1002.in","r",stdin);
   // freopen("output.b","w",stdout);
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

        /*if(Tcase==203){
            printf("%d %s\n",n,ops);
            for(int i=1;i<=n;i++) printf("%d ",w[i]);puts("");
        for(int i=2;i<=n;i++){
            printf("%d ",fa[i]);
        }puts("");
        }*/

        for(int i=0;i<(1<<8);i++) for(int j=0;j<(1<<8);j++) ds[i][j]=-1;


        //dfs(1);
        solve();
        ans=0;
        for(int i=1;i<=n;i++){
            dp[i]+=w[i];dp[i]%=mod;
            ans+=dp[i]*i;
            if(ans>=mod) ans%=mod;
        }
        ans%=mod;
        printf("%I64d\n",ans);
    }

    return 0;
}
