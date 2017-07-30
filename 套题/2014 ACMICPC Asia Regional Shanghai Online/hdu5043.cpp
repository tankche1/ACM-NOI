# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=10;
const int mod=100000009;
int n,P;
int k[maxn];
int Bit[maxn][33];
int Max=1;
LL dp[maxn][33][22][1030];
bool vis[maxn][33][22][1030];

LL dfs(int id,int pos,int sum,int st){
    if(id==n){
        id=0;pos--;sum=0;
        if(pos<0) return 1;
    }
    if(vis[id][pos][sum][st]) return dp[id][pos][sum][st];
    vis[id][pos][sum][st]=1;
    LL ans=0;
    if((st&(1<<id))&&(sum+Bit[id][pos]<P)) ans+=dfs(id+1,pos,sum+Bit[id][pos],st);
    int end=(st&(1<<id))?Bit[id][pos]:P;
    for(int i=0;i<end&&i+sum<P;i++){
        ans+=dfs(id+1,pos,sum+i,(st&(1<<id))?(st^(1<<id)):st);
    }
    while(ans>=mod) ans-=mod;
    return dp[id][pos][sum][st]=ans;
}

void prepare(){
    int x,cnt;Max=0;
    memset(Bit,0,sizeof(Bit));
    for(int i=0;i<n;i++){
        x=k[i];cnt=0;
        while(x!=0){
            Bit[i][cnt++]=x%P;x/=P;
        }
        Max=max(Max,cnt);
    }
}

LL solve(){
    memset(vis,false,sizeof(vis));
    return dfs(0,Max-1,0,(1<<n)-1);
}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&P);
        for(int i=0;i<n;i++)
            scanf("%d",&k[i]);
        prepare();
        LL ans=1;
        for(int i=0;i<n;i++) ans=ans*(k[i]+1)%mod;
        ans-=solve();
        ans=(ans+mod)%mod;
        printf("Case #%d: %I64d\n",Tcase,ans);
    }
    return 0;
}
