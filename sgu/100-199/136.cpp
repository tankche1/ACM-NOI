# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const double eps=1e-8;
const int maxn=10010;
int n;
double midx[maxn],midy[maxn];
double x[maxn],y[maxn];
double sumx,sumy;

void print(){
    puts("YES");
    for(int i=1;i<=n;i++)
        printf("%.3lf %.3lf\n",x[i],y[i]);
}

int main(){
    scanf("%d",&n);sumx=0;sumy=0;
    for(int i=1;i<=n;i++){
        scanf("%lf%lf",&midx[i],&midy[i]);sumx+=midx[i];sumy+=midy[i];
    }
    if(n&1){
        x[1]=sumx;y[1]=sumy;
        for(int i=2;i<=n;i+=2){
            x[1]-=2*midx[i];y[1]-=2*midy[i];
        }
        for(int i=1;i<n;i++)
            x[i+1]=midx[i]*2-x[i],y[i+1]=midy[i]*2-y[i];
        if((!(fabs(x[1]+x[n]-midx[n]*2)<eps))||(!(fabs(y[1]+y[n]-midy[n]*2)<eps)))
            puts("NO");
        else{
            print();
        }
    }
    else{
        x[1]=-1.0;y[1]=0.0;
        for(int i=1;i<n;i++)
            x[i+1]=midx[i]*2-x[i],y[i+1]=midy[i]*2-y[i];
        if((!(fabs(x[1]+x[n]-midx[n]*2)<eps))||(!(fabs(y[1]+y[n]-midy[n]*2)<eps)))
            puts("NO");
        else{
            print();
        }
    }
    return 0;
}
