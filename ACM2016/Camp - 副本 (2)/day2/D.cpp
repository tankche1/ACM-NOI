# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int mod=1000000007;
typedef long long LL;
int n,k;
int p[maxn];
LL inv;
LL dpL[2][maxn][maxn],dpR[2][maxn][maxn];
LL sumL[2][maxn][maxn],sumR[2][maxn][maxn];

LL fast_pow(LL a,LL b){
    if(b==0) return 1;
    LL half=fast_pow(a,b>>1);
    half=half*half%mod;
    if(b&1) half=half*a%mod;
    return half;
}

int main(){
    freopen("input.txt","r",stdin);
    int now,last;
    inv=fast_pow(2,mod-2);
    while(scanf("%d%d",&n,&k)!=EOF){
        for(int i=1;i<=n;i++) scanf("%d",&p[i]);
        memset(dpL,0,sizeof(dpL));memset(dpR,0,sizeof(dpR));
        memset(sumL,0,sizeof(sumL));memset(sumR,0,sizeof(sumR));

        dpL[1][p[1]][0]=inv;
        dpR[1][p[1]][0]=inv;
        for(int j=1;j<=n;j++){
            sumL[1][j][0]=sumL[1][j-1][0]+dpL[1][j][0];
            sumR[1][j][0]=sumR[1][j-1][0]+dpR[1][j][0];
        }

        for(int i=2;i<=n;i++){
            now=i&1;last=now^1;
            memset(dpL[now],0,sizeof(dpL[now]));memset(dpR[now],0,sizeof(dpR[now]));
            memset(sumL[now],0,sizeof(sumL[now]));memset(sumR[now],0,sizeof(sumR[now]));
            for(int R=1;R<=n;R++){
                for(int j=0;j<=n;j++){
                    dpL[now][R][j]=dpL[last][R][j-(p[i]>p[i-1])];
                    if(p[i-1]==R){
                        dpL[now][R][j]+=sumR[last][n][j]-sumR[last][p[i]][j];
                        if(j>=1) dpL[now][R][j]+=sumR[last][p[i]-1][j-1];
                    }
                    dpL[now][R][j]+=mod;
                    dpL[now][R][j]*=inv;
                    dpL[now][R][j]%=mod;
                }
            }

            for(int L=1;L<=n;L++){
                for(int j=0;j<=n;j++){
                    dpR[now][L][j]=dpR[last][L][j-(p[i]<p[i-1])];
                    if(p[i-1]==L){
                        dpR[now][L][j]+=sumL[last][p[i]-1][j];
                        if(j>=1) dpR[now][L][j]+=sumL[last][n][j-1]-sumL[last][p[i]][j-1];
                    }
                    dpR[now][L][j]+=mod;
                    dpR[now][L][j]*=inv;
                    dpR[now][L][j]%=mod;
                }
            }

            for(int L=1;L<=n;L++){
                for(int j=0;j<=n;j++){
                    sumL[now][L][j]=sumL[now][L-1][j]+dpL[now][L][j];
                    if(sumL[now][L][j]>=mod) sumL[now][L][j]-=mod;
                    sumR[now][L][j]=sumR[now][L-1][j]+dpR[now][L][j];
                    if(sumR[now][L][j]>=mod) sumR[now][L][j]-=mod;
                }
            }
        }
        now=n&1;
        LL ans=0;
        for(int L=1;L<=n;L++){
            for(int j=1;j<=n;j++){
                ans=ans+dpL[now][L][j]*fast_pow(j,k)+dpR[now][L][j]*fast_pow(j,k);
                ans%=mod;
            }
        }
        ans=ans*fast_pow(2,n)%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
