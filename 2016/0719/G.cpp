# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=12;
int mod=1000000007;
int m,n;
int C[maxn][maxn];
typedef long long LL;
LL g[maxn][maxn],f[maxn][maxn];

int main(){

    memset(C,0,sizeof(C));
    C[0][0]=1;
    for(int i=1;i<=10;i++){
        C[i][0]=1;C[i][1]=i;
        for(int j=2;j<=i;j++){
            C[i][j]=C[i-1][j]+C[i-1][j-1];
        }
    }

    LL res;
    memset(g,0,sizeof(g));
    for(int i=1;i<=10;i++) g[0][i]=1;
    for(int i=1;i<=10;i++){
        g[i][0]=1;
        for(int j=1;j<=10;j++){
            res=0;
            for(int k=0;k<=j;k++) res+=C[j][k]*(1<<k);
            g[i][j]=g[i-1][j]*res%mod;
            //printf("g[%d][%d]:%I64d\n",i,j,g[i][j]);
        }
    }

    for(int i=0;i<=10;i++) f[1][i]=(1<<i);
    for(int i=2;i<=10;i++){
        f[i][0]=0;
        for(int j=1;j<=10;j++){
            res=0;
            for(int x=1;x<=i;x++){
                for(int y=0;y<=j;y++){
                    if(x==i&&j==y) continue;
                    res+=(f[x][y]*C[i-1][x-1]*C[j][y]%mod)*g[i-x][j-y]%mod;
                    /*if(i==2&&j==3) {
                            printf("x:%d y:%d %I64d\n",x,y,(f[x][y]*C[i-1][x-1]*C[j][y]%mod)*g[i-x][j-y]%mod);
                            printf("%I64d %I64d %I64d %I64d\n",f[x][y],C[i-1][x-1],C[j][y],g[i-x][j-y]);
                    }*/
                }
            }
            res%=mod;
            f[i][j]=(g[i][j]-res+mod)%mod;
            //printf("f[%d][%d]:%I64d res:%I64d\n",i,j,f[i][j],res);
        }
    }

    while(scanf("%d%d",&m,&n)!=EOF){
        printf("%I64d\n",f[m][n]);
    }
    return 0;
}
