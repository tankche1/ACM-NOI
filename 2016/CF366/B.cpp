# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=5010;
typedef long long LL;
LL INF=(LL)1<<60;
LL dp[maxn][maxn];
int n,s,t;
int x[maxn],a[maxn],b[maxn],c[maxn],d[maxn];

void update(LL &x,LL y){
    if(y<=x) x=y;
}

int main(){
    scanf("%d%d%d",&n,&s,&t);
    for(int i=1;i<=n;i++)
        scanf("%d",&x[i]);

    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);

    for(int i=1;i<=n+2;i++){
        for(int j=0;j<=n+2;j++){
            dp[i][j]=INF;
        }
    }
    dp[1][1]=b[1]+d[1];

    //printf("%lld\n",dp[1][0]);

    for(int i=2;i<=n;i++){
        for(int j=0;j<=i;j++){
            if(i!=n&&j==0) continue;
            if(j+1<=i-1&&(j!=0||i==n)){
                if(i!=s&&i!=t)    update(dp[i][j],dp[i-1][j+1]+a[i]+c[i]+(LL)2*(j+1)*(x[i]-x[i-1]));
                if(i==s&&(t<s)) update(dp[i][j],dp[i-1][j+1]+a[i]+c[i]+(LL)2*(j+1)*(x[i]-x[i-1]));
                if(i==t&&s<t) update(dp[i][j],dp[i-1][j+1]+a[i]+c[i]+(LL)2*(j+1)*(x[i]-x[i-1]));
            }
            if(i!=s&&i!=t) update(dp[i][j],dp[i-1][j]+(LL)2*(j)*(x[i]-x[i-1])+min(b[i]+c[i],a[i]+d[i]));

            if(i==s&&s<t) update(dp[i][j],dp[i-1][j]+(LL)2*(j)*(x[i]-x[i-1])+b[i]+c[i]);
            else if(i==s&&s>t) update(dp[i][j],dp[i-1][j]+(LL)2*(j)*(x[i]-x[i-1])+a[i]+d[i]);

            if(i==t&&s<t) update(dp[i][j],dp[i-1][j]+(LL)2*(j)*(x[i]-x[i-1])+b[i]+c[i]);
            else if(i==t&&s>t) update(dp[i][j],dp[i-1][j]+(LL)2*(j)*(x[i]-x[i-1])+a[i]+d[i]);

            if(j>=1){
                if(i!=s&&i!=t)
                    update(dp[i][j],dp[i-1][j-1]+(LL)2*(j-1)*(x[i]-x[i-1])+b[i]+d[i]);
                if(i==s&&t>s) update(dp[i][j],dp[i-1][j-1]+(LL)2*(j-1)*(x[i]-x[i-1])+b[i]+d[i]);
                if(i==t&&s>t) update(dp[i][j],dp[i-1][j-1]+(LL)2*(j-1)*(x[i]-x[i-1])+b[i]+d[i]);
            }

            printf("dp[%d][%d]:%lld\n",i,j,dp[i][j]);
        }
    }

    LL ans=dp[n][0];
    if(s<t) ans-=b[s]+c[t];
    if(s>t) ans-=a[s]+d[t];
    ans-=abs(x[s]-x[t]);

    printf("%lld\n",ans);
    return 0;
}
