# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
const int maxm=1010;
double dp[2][maxn*maxm];
double sum[2][maxn*maxm];
int x[maxn];
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    int tot=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&x[i]);tot+=x[i];
    }
    if(m==1){
        printf("1.000000000000\n");return 0;
    }
    double p=1/((m-1)*1.0);
    for(int i=1;i<=m;i++){
        if(i==x[1]) dp[1][i]=0;
        else dp[1][i]=p;
       // printf("i:%d j:%d dp:%.3lf\n",1,i,dp[1][i]);
    }
    sum[1][0]=0;
    for(int j=1;j<=2*m;j++) sum[1][j]=sum[1][j-1]+dp[1][j];

    for(int i=2;i<=n;i++){
        int now=i&1;int last=now^1;
        memset(dp[now],0,sizeof(dp[now]));
        for(int j=i;j<=i*m;j++){
            dp[now][j]=sum[last][j-1]-sum[last][max(j-m-1,0)];
            if(j-x[i]>=0) dp[now][j]-=dp[last][j-x[i]];
            dp[now][j]*=p;
            //printf("i:%d j:%d dp:%.3lf\n",i,j,dp[now][j]);
        }
        sum[now][0]=0;
        for(int j=1;j<=(i+1)*m;j++) sum[now][j]=sum[now][j-1]+dp[now][j];
    }

    double ans=0;
    for(int i=n;i<tot;i++){
        ans+=dp[n&1][i];
    }
    ans=ans*(m-1)+1;
    printf("%.12lf\n",ans);
    return 0;
}
