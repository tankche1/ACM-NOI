# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=500010;
typedef long long LL;
LL a[maxn];
LL n,m,z,l;
LL ans;


int main(){
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%I64d%I64d%I64d%I64d",&n,&m,&z,&l);
        a[1]=0;ans=0;
        for(int i=2;i<=n;i++){
            a[i]=((LL)a[i-1]*m+z)%l,ans=ans^(a[i]+a[i]);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
