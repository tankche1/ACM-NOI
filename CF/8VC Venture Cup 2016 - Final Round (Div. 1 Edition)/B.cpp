# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL s,x;
LL dp[100][2];
int main(){
    scanf("%I64d%I64d",&s,&x);
    dp[0][0]=1;dp[0][1]=0;
    int n=0;
    for(int i=0;(s>>i)>0;i++,n++){
        for(int j=0;j<2;j++){
            if(dp[i][j]==0) continue;

            int vs=(s>>i)&1,vx=(x>>i)&1;
            for(int a=0;a<2;a++){
                if((((a^vx)+a+j)&1)==vs){
                    if((a^vx)+a+j>1) dp[i+1][1]+=dp[i][j];
                    else dp[i+1][0]+=dp[i][j];
                }
            }
        }
    }
    /*for(int i=0;i<=n;i++)
        for(int j=0;j<2;j++)
            if(dp[i][j]!=0) printf("dp[%d][%d]:%I64d\n",i,j,dp[i][j]);*/
            if((x>>n)>0) {puts("0");return 0;}
    if((s^0)==x) dp[n][0]-=2;
    printf("%I64d\n",dp[n][0]);
    return 0;
}
