# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=310;
int n,T;
int dp[maxn][maxn];
int f[310],g[maxn];
int a[maxn];

void getF(int len){
    for(int i=1;i<=len;i++){
        for(int j=300;j>=1;j--){
            for(int k=j;k>=1;k--)
                f[j]=max(f[j],f[k]+dp[k][j]);
        }
        /*printf("i:%d\n",i);
        for(int j=1;j<=n;j++)
            printf("f[%d]:%d\n",a[j],f[a[j]]);*/
    }
}

void getG(int len){
    for(int i=len;i>=1;i--){
        for(int j=1;j<=300;j++){
            for(int k=j;k<=300;k++)
                g[j]=max(g[j],g[k]+dp[j][k]);
        }
    }
}

int main(){
    scanf("%d%d",&n,&T);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int L=1;L<=300;L++){
        for(int i=1;i<=n;i++){
            if(a[i]<L) {f[i]=0;continue;}
            f[i]=1;
            for(int j=i-1;j>=1;j--){
                if(a[i]>=a[j]) f[i]=max(f[i],f[j]+1);
            }
        }
        for(int i=1;i<=n;i++){
            dp[L][a[i]]=max(dp[L][a[i]],f[i]);
        }
        for(int i=L;i<=300;i++) dp[L][i]=max(dp[L][i],dp[L][i-1]);
    }

    /*for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[j]>=a[i]) printf("dp[%d][%d]:%d\n",a[i],a[j],dp[a[i]][a[j]]);
        }
    }*/

    memset(f,0,sizeof(f));
    if(T<=600) {getF(T);printf("%d\n",f[300]);return 0;}

    getF(300);
    getG(300);

    int ans=0;
    for(int L=1;L<=300;L++){
        ans=max(ans,f[L]+g[L]+(T-600)*dp[L][L]);
    }
    printf("%d\n",ans);
    return 0;
}
