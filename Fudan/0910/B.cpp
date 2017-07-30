# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=55;
const double eps=1e-12;
double dp[2][maxn][maxn];
int n,m;
int tot;
int main(){
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&n,&m);tot=n*m;
        memset(dp,0,sizeof(dp));
        dp[0][0][0]=1;
        int last,now;
        double ans=0;
        for(int k=1;k<=tot;k++){
            now=k&1;last=now^1;
            memset(dp[now],0,sizeof(dp[now]));
            for(int i=0;i<=n;i++){
                for(int j=0;j<=m;j++){
                    if(i>=1) dp[now][i][j]+=dp[last][i-1][j]*(n-i+1)*j;
                    if(j>=1) dp[now][i][j]+=dp[last][i][j-1]*i*(m-j+1);
                    if(i>=1&&j>=1) dp[now][i][j]+=dp[last][i-1][j-1]*(n-i+1)*(m-j+1);
                    if((i!=n)||(j!=m))
                    dp[now][i][j]+=dp[last][i][j]*(i*j-k+1);
                    dp[now][i][j]=dp[now][i][j]/(tot-k+1);
                    //printf("k:%d i:%d j:%d dp:%.12lf\n",k,i,j,dp[now][i][j]);
                }
            }
            ans+=(dp[now][n][m])*k;
        }
       // puts("fuck");

        printf("%.12lf\n",ans);
    }
    return 0;
}
