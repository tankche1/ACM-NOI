# include<stdio.h>
# include<string.h>
# include<math.h>
# include<iostream>
# include<algorithm>
using namespace std;
const int maxn=2010;
const double eps=1e-8;
int n,m,k;
double p1,p2,p3,p4;
double f[maxn][maxn];

void Dp(int i){
    double a=1,b=0;
    for(int j=2;j<=i&&j<=k;j++) a=a*p2/(1-p1),b=b*p2/(1-p1),b=b+p3/(1-p1)*f[i-1][j-1]+p4/(1-p1);
    for(int j=k+1;j<=i;j++) a=a*p2/(1-p1),b=b*p2/(1-p1),b=b+p3/(1-p1)*f[i-1][j-1];
    f[i][1]=p2/(1-p1)*b+p4/(1-p1);f[i][1]=f[i][1]/(1-p2*a/(1-p1));
    for(int j=2;j<=k&&j<=i;j++) f[i][j]=p2/(1-p1)*f[i][j-1]+p3/(1-p1)*f[i-1][j-1]+p4/(1-p1);
    for(int j=k+1;j<=i;j++) f[i][j]=p2/(1-p1)*f[i][j-1]+p3/(1-p1)*f[i-1][j-1];
    return;
}

int main(){
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        scanf("%lf%lf%lf%lf",&p1,&p2,&p3,&p4);
        if(fabs(1-p1)<eps) {printf("0.00000\n");continue;}
        if(fabs(p4)<eps) {printf("0.00000\n");continue;}
        f[1][1]=p4/(1-p1-p2);
        for(int i=2;i<=n;i++){
            Dp(i);
        }
        printf("%.5lf\n",f[n][m]);
       //cout << f[n][m] << endl;
    }
    return 0;
}
