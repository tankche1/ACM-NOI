# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<map>
# include<algorithm>
using namespace std;
const int maxn=3010;
typedef long long LL;
const LL INF=(LL)1<<60;
int n;
int a[maxn],b[maxn];

LL dp[maxn][maxn];
LL _min[maxn][maxn];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]-=i,b[i]=a[i];
    sort(b+1,b+n+1);

    _min[1][0]=INF;
    for(int i=1;i<=n;i++) dp[1][i]=abs(a[1]-b[i]),_min[1][i]=min(_min[1][i-1],dp[1][i]);

    for(int i=2;i<=n;i++){
        _min[i][0]=INF;
        for(int j=1;j<=n;j++){
            dp[i][j]=_min[i-1][j]+abs(a[i]-b[j]);
            _min[i][j]=min(_min[i][j-1],dp[i][j]);
        }
    }

    LL ans=INF;
    for(int j=1;j<=n;j++){
        ans=min(ans,dp[n][j]);
    }
    printf("%I64d\n",ans);
    return 0;
}
