# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef double LD;
const int maxn=210;

int n,m,a,b,c,d,r,tot;
int X[maxn];
LD K[maxn],Y[maxn];

bool find(int n){
    for(int i=tot-1;i>=0;i--) if(X[i]==n) return true;
    return false;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d%d%d%d%d%d",&n,&m,&a,&b,&c,&d,&r);
        tot=0;
        LD k=1.0,y=0.0;
        do{
            X[tot]=n;K[tot]=k;Y[tot]=y;
           // printf("tot:%d n:%d k:%.6lf y:%.6lf\n",tot,n,k,y);
            //printf("K:%.6lf y:%.6lf\n",k,y);
            tot++;
            if(n<=0){
                k=b/(r*1.0)+(n*n)/(m*m*1.0);
                //printf("%.6lf %.6lf %.6lf\n",b/(r*1.0),(n*n)/(m*m*1.0),k);
                y=a/(r*1.0);
            }
            else{
                k=d/(r*1.0)+(n*n)/(m*m*1.0);
                //printf("%.6lf %.6lf %.6lf\n",d/(r*1.0),(n*n)/(m*m*1.0),k);
                y=c/(r*1.0);
            }

            if(n<=0) n=-m-2*n;
            else n=m-2*n;
            //printf("n:%d\n",n);
        }while(!find(n));

        int pos;
        for(int i=tot-1;i>=0;i--) if(X[i]==n) {pos=i;break;}

        for(int i=tot-1;i>pos;i--){
            k=k*K[i];y=y*K[i]+Y[i];
        }
        LD x=y/((1-k)*1.0);

        k=1.0;y=0.0;

        for(int i=pos;i>=0;i--){
            k=k*K[i];y=y*K[i]+Y[i];
        }

        LD ans=k*x+y;
        printf("%.10lf\n",ans);
    }
    return 0;
}
