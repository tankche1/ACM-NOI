# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxp=(1<<20)+5;
const int maxm=100010;
const int INF=~0U>>1;
int dp[21][maxp];
char s[21][maxm];
int col[maxm];

int n,m;

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]+1);
    }

    for(int j=1;j<=m;j++){
        col[j]=0;
        for(int i=1;i<=n;i++)
            col[j]=col[j]*2+s[i][j]-'0';
    }

    for(int j=1;j<=m;j++){
        dp[0][col[j]]++;
    }

    for(int k=1;k<=n;k++){
        for(int mask=0;mask<(1<<n);mask++){
            if(k>=2){
                dp[k][mask]+=(k-2-n)*dp[k-2][mask];
            }
            for(int p=0;p<n;p++) dp[k][mask]+=dp[k-1][mask^(1<<p)];
            dp[k][mask]/=k;
        }
    }

    int ans=INF;
    int tmp=0;
    for(int mask=0;mask<(1<<n);mask++){
        tmp=0;
        for(int k=0;k<=n;k++) tmp+=dp[k][mask]*min(k,n-k);
        ans=min(ans,tmp);
    }
    printf("%d\n",ans);
    return 0;
}
