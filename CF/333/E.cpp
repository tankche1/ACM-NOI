# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=35010;
const int mod=1000000007;
const int pmod=10000019;
int n,k,q;

struct Thing{
    int v,w,st,ed;
}th[maxn];

int ask=0;
vector<int> G[maxn<<2];

void insert(int o,int L,int R,int qL,int qR,int bh){
    if(qL<=L&&qR>=R){
        G[o].push_back(bh);return;
    }
    int M=(L+R)>>1;
    if(qL<=M) insert(o<<1,L,M,qL,qR,bh);
    if(qR>M) insert(o<<1|1,M+1,R,qL,qR,bh);
}

int dp[20][1010];

void solve(int o,int L,int R,int step){
    int x;
    for(int i=0;i<=k;i++) dp[step][i]=dp[step-1][i];
    for(int e=0;e<(int)G[o].size();e++){
        x=G[o][e];
        for(int j=k;j>=th[x].w;j--){
            dp[step][j]=max(dp[step][j],dp[step][j-th[x].w]+th[x].v);
        }
    }
    if(L==R) {
        LL ans=0,p=1;
        //printf("L:%d\n",L);
        for(int i=1;i<=k;i++){
            //printf("dp[%d]:%d\n",i,dp[step][i]);
            ans=(ans+dp[step][i]*p)%mod;p=p*pmod%mod;
        }
        printf("%I64d\n",ans);
        return;
    }
    int M=(L+R)>>1;
    solve(o<<1,L,M,step+1);
    solve(o<<1|1,M+1,R,step+1);
}

int main(){
    int type,x;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&th[i].v,&th[i].w);th[i].st=1;th[i].ed=-1;
    }
    scanf("%d",&q);
    for(int tt=1;tt<=q;tt++){
        scanf("%d",&type);
        if(type==1){
            n++;
            scanf("%d%d",&th[n].v,&th[n].w);th[n].st=ask+1;th[n].ed=-1;
        }
        else if(type==2){
            scanf("%d",&x);th[x].ed=ask;
        }
        else{
            ask++;
        }
    }
    for(int i=1;i<=n;i++){
        if(th[i].ed==-1) th[i].ed=ask;
        if(th[i].st<=th[i].ed) insert(1,1,ask,th[i].st,th[i].ed,i);
    }
    memset(dp[0],0,sizeof(dp[0]));
    solve(1,1,ask,1);
    return 0;
}
