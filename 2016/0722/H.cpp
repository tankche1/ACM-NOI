# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=80;
const LL INF=(LL)1<<60;

int n,m;
LL dis[maxn][maxn];
LL f[maxn][maxn];

LL big,ans,big2;

int main(){
    int a,b,c;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=INF;
        }
        dis[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a,&b,&c);
        dis[b][a]=dis[a][b]=min(dis[a][b],(LL)c);
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dis[i][j]-dis[i][k]>dis[k][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
            }
        }
    }

    big=0;
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) {big=max(big,dis[i][j]);//printf("dis[%d][%d]:%I64d\n",i,j,dis[i][j]);
    }

    ans=big;int aa,bb;

    for(a=1;a<=n;a++){
        for(b=a+1;b<=n;b++){
            for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=dis[i][j];
            for(int i=1;i<=n;i++){
                for(int j=i+1;j<=n;j++){
                    if(f[i][j]-f[i][a]>f[b][j]){
                        f[j][i]=f[i][j]=f[i][a]+f[b][j];
                    }
                    if(f[i][j]-f[i][b]>f[a][j]){
                        f[j][i]=f[i][j]=f[i][b]+f[a][j];
                    }
                }
            }

            big2=0;
            for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) big2=max(big2,f[i][j]);

            if(big2<ans) ans=big2;
        }
    }

    if(ans==INF) {printf("-1.00000 -1.00000\n");return 0;}
    printf("%I64d.00000 ",ans);

    LL ans2=0;

    for(a=1;a<=n;a++){
        for(b=a+1;b<=n;b++){
            for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=dis[i][j];
            for(int i=1;i<=n;i++){
                for(int j=i+1;j<=n;j++){
                    if(f[i][j]-f[i][a]>f[b][j]){
                        f[j][i]=f[i][j]=f[i][a]+f[b][j];
                    }
                    if(f[i][j]-f[i][b]>f[a][j]){
                        f[j][i]=f[i][j]=f[i][b]+f[a][j];
                    }
                }
            }

            big2=0;
            for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) big2=max(big2,f[i][j]);

            if(big2==ans){
                //printf("a:%d b:%d\n",a,b);
                int L=0,R=100000001,M;
                while(L<=R){
                    M=(L+R)>>1;
                    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=dis[i][j];
                    //f[a][b]=f[b][a]=0;
                    for(int i=1;i<=n;i++){
                        for(int j=i+1;j<=n;j++){
                            if(f[i][j]-f[i][a]>f[b][j]+M){
                                f[j][i]=f[i][j]=f[i][a]+f[b][j]+M;
                            }
                            if(f[i][j]-f[i][b]>f[a][j]+M){
                                f[j][i]=f[i][j]=f[i][b]+f[a][j]+M;
                            }
                        }
                    }
                    big2=0;
                    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) big2=max(big2,f[i][j]);
                    if(big2<=ans) L=M+1;
                    else R=M-1;
                }
                ans2=max(ans2,(LL)L-1);
            }

        }
    }
    if(ans2==100000001) printf("-1.00000\n");
    else printf("%I64d.00000\n",ans2);
    return 0;
}

