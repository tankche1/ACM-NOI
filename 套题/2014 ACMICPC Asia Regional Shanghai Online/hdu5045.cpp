# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n,m;
double p[11][1020];
double dp[11][1030];

double solve(int L,int R){
    dp[0][(1<<n)-1]=0;memset(dp,0,sizeof(dp));
    for(int i=0;i<(R-L+1);i++){
        for(int j=0;j<(1<<n);j++){
            for(int k=1;k<=n;k++){
                if(j&(1<<(k-1))){
                    dp[i+1][j^(1<<(k-1))]=max(dp[i+1][j^(1<<(k-1))],dp[i][j]+p[k][L+i]);
                }
            }
        }
    }
    return dp[n][0];
}
int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf("%lf",&p[i][j]);
        }
        for(int j=m+1;j<=m+n;j++) for(int i=1;i<=n;i++) p[i][j]=0;
        while(m%n>0) m++;
        int L=1,R=n;
        double ans=0;
        while(R<=m){
            ans+=solve(L,R);L=R+1;R=R+n;
        }
        printf("Case #%d: %.5lf\n",Tcase,ans);
    }
    return 0;
}
