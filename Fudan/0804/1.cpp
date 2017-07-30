# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int main(){
    int T;
    LL n,m,z,l;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%I64d%I64d%I64d%I64d",&n,&m,&z,&l);
        LL ans=0,a=0;
        for(int i=2;i<=n;++i)
        {
            a=(a*m+z)%l;
            ans^=(a<<1);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
