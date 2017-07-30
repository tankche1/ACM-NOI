# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int n;
typedef long long LL;
double len;
LL L;
int main(){
    LL v,t;
    LL d,now=0;
    scanf("%lf%d",&len,&n);
    L=round(len*10000);
    //printf("%lld\n",L);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&v,&t);
        d=v*t*10000;
        now=now+d;
        if(now>=L) now%=L;
    }
    double ans=(double)now/10000.0;
    ans=min(len-ans,ans);
    //double a=(double)ans/10000.0;
    printf("%.4lf\n",ans);
    return 0;
}
