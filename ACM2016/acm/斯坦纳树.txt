# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=55;
const int maxt=(1<<10)+50;
const int INF=100000000;
int bit_count[maxt],fact[10];
int n,m,k;
int D[maxn][maxn];
int dp[maxn][maxt];

struct tank{
    int val,num;
    tank(int val=0,int num=0):val(val),num(num) {}
}New[maxn];

bool cmp(tank a,tank b){return a.val<b.val;}
bool change[maxn];

void Floyed(){
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            D[i][j]=min(D[i][j],D[i][k]+D[k][j]);
}

void Steiner_DP(){
    int now,val;
    for(int i=1;i<=n;i++)
        for(int j=0;j<(1<<(k+k));j++)
            dp[i][j]=INF;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++)
            dp[i][1<<(j-1)]=D[i][j];
        for(int j=k+1;j<=k+k;j++)
            dp[i][1<<(j-1)]=D[i][n-k+(j-k)];
    }
    for(int num=2;num<=k+k;num++){
        for(int j=1;j<(1<<(k+k));j++){
            if(bit_count[j]!=num) continue;
            for(int i=1;i<=n;i++){
                for(int k=(j-1)&j;k;k=(k-1)&j){
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[i][j^k]);
                }
                New[i]=tank(dp[i][j],i);
            }
            sort(New+1,New+n+1,cmp);
            memset(change,0,sizeof(change));
            for(int i=1;i<=n;i++){
                now=New[i].num;val=New[i].val;
                if(change[now]) continue;
                for(int k=1;k<=n;k++)
                    if(val+D[now][k]<dp[k][j]) dp[k][j]=val+D[now][k],change[k]=1;
            }
        }
    }
    return;
}

int p[10];
int Get(int s){
    int ans=s;
    for(int i=1;i<=k;i++)
        if((s>>(i-1))&1) ans=ans^(1<<(p[i]-1));
    return ans;
}

int f[maxt];
int main(){
    for(int j=0;j<(1<<10);j++){
        bit_count[j]=0;
        for(int i=0;i<10;i++)
            bit_count[j]+=(j>>i)&1;
    }
    fact[0]=1;for(int i=1;i<=5;i++) fact[i]=fact[i-1]*i;

    int tcase,a,b,c,ans;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++)for(int j=1;j<=n;j++) D[i][j]=INF;
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&a,&b,&c);D[a][b]=D[b][a]=min(D[a][b],c);
        }
        for(int i=1;i<=n;i++) D[i][i]=0;
        Floyed();
        Steiner_DP();
        for(int i=1;i<=k;i++) p[i]=k+i;
        ans=INF;
        for(int tt=1;tt<=fact[k];tt++){
            for(int j=1;j<(1<<k);j++){
                f[j]=INF;
                int k=Get(j);
                for(int i=1;i<=n;i++)
                    f[j]=min(f[j],dp[i][k]);
            }
            for(int num=2;num<=k;num++){
                for(int j=1;j<(1<<k);j++){
                    if(bit_count[j]!=num) continue;
                    for(int k=(j-1)&j;k;k=(k-1)&j)
                        f[j]=min(f[j],f[k]+f[j^k]);
                }
            }
            ans=min(ans,f[(1<<k)-1]);
            next_permutation(p+1,p+k+1);
        }
        if(ans>=INF) puts("No solution");
        else printf("%d\n",ans);
    }
	return 0;
}
