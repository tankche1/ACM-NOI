# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
const double eps=1e-12;
int n;
double p[maxn];
int c[maxn];
double pc[maxn];
int main(){
    int x;
    double ans,now=1.0,best;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&x);
        p[i]=x/100.0;
        pc[i]=1-p[i];
        c[i]=1;
        now=now*(1-pc[i]);
    }ans=n;ans=ans*1.0;
    ans=ans+1-now;
    if(n==1) {printf("1.0000000000\n");return 0;}

    int pos;
    for(int t=n+2;t<=400000;t++){
        //printf("t:%d now:%.10lf\n",t,now);
        best=now*(1-pc[1]*(1-p[1]))/((1-pc[1]));
        pos=1;
        for(int i=2;i<=n;i++){
            if(now*(1-pc[i]*(1-p[i]))/((1-pc[i]))>best){
                best=now*(1-pc[i]*(1-p[i]))/((1-pc[i]));pos=i;
            }
        }
        now=best;c[pos]++;pc[pos]=pc[pos]*(1-p[pos]);
        //printf("best:%.10lf pos:%d\n",best,pos);
        //if(1-now<eps) break;
        //printf("t:%d now:%.10lf\n",t,now);
        ans+=1-now;
        //printf("t:%d p:%.10lf\n",t,1-now);
    }
    printf("%.10lf\n",ans);
    return 0;
}
