# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=1010;
typedef long long LL;
int n,L;
LL dp[4010][3];
int a[maxn],v[maxn];

int main(){
    int Case;
    LL ans=0;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
            ans=0;
        scanf("%d%d",&n,&L);L*=2;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i],&v[i]);a[i]*=2;
            ans=max(ans,(LL)v[i]);
        }

        for(int i=0;i<=L;i++) for(int k=0;k<3;k++) dp[i][k]=-1;
        dp[0][0]=0;

        for(int i=0;i<n;i++){
            for(int j=L-a[i+1]/2;j>=0;j--){
                for(int k=2;k>=0;k--){
                        if(dp[j][k]!=-1){
                            //printf("i:%d j:%d k:%d dp:%I64d\n",i,j,k,dp[j][k]);
                            if(j+a[i+1]<=L) dp[j+a[i+1]][k]=max(dp[j+a[i+1]][k],dp[j][k]+v[i+1]);
                            if(k<2){
                                dp[j+a[i+1]/2][k+1]=max(dp[j+a[i+1]/2][k+1],dp[j][k]+v[i+1]);
                            }
                        }
                }
            }
        }
        for(int j=0;j<=L;j++){
            if(dp[j][2]>ans) ans=dp[j][2];
        }
        printf("Case #%d: ",Tcase);
        printf("%I64d\n",ans);
    }
    return 0;
}
