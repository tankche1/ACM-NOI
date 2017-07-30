# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL n,m,a,b,k;
int main(){
    while(scanf("%lld%lld%lld",&n,&m,&k)!=EOF){
        LL ans=0,tmp;
        for(a=1;a<=n&&2*a+2<=k;a++){
            b=min(m,(k-2*a)/2);
            tmp=(m+1)*b-(1+b)*b/2;tmp=tmp*(n+1-a);
            ans+=tmp;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
