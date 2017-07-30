# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=2010;
const int mod=1000000007;
int m,n;
LL f[maxn][maxn];
int main(){
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&n,&m);
        f[0][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=i&&j<=m;j++){
                f[i][j]=0;
                if(j>0) f[i][j]+=f[i-1][j-1]*(m-j+1);
                if(j<i&&j<m) f[i][j]+=f[i-1][j+1]*(j+1);
                if(f[i][j]>=mod) f[i][j]%=mod;
                //printf("i:%d j:%d f:%d\n",i,j,f[i][j]);
            }
        }
        LL ans=0,tmp=1;
        for(int l=n;l>=1;l--){
            ans=ans+((n-l+1)*f[l][l&1]%mod)*tmp;
            if(ans>=mod) ans%=mod;
            tmp=tmp*m%mod;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
