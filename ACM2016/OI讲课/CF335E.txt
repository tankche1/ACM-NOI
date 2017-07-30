# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
int n;
double p[1010][1010];
double dis[1010];
double A[1010],B[1010];

double tank(int x){
    return (1+B[x])/(1-A[x]);
}

int main(){
    int x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&x);p[i][j]=x/100.0;
        }
    }
    for(int i=1;i<=n;i++) dis[i]=INF;
    dis[n]=0;
    x=n;
    for(int i=1;i<=n;i++) A[i]=1.0,B[i]=0.0;
    while(1){
        if(x!=n) dis[x]=(1+B[x])/(1-A[x]);
        //printf("dis[%d]:%.3lf\n",x,dis[x]);
        if(x==1) break;
        for(int i=1;i<=n;i++){
            if(dis[i]==INF){
                B[i]=B[i]+dis[x]*p[i][x]*A[i];
                A[i]=A[i]*(1-p[i][x]);
            }
        }
        x=-1;
        for(int i=1;i<=n;i++){
            if(dis[i]==INF){
                if(x==-1||tank(i)<tank(x)) x=i;
            }
        }
    }
    printf("%.10lf\n",dis[1]);
    return 0;
}
