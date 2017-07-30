# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=(LL)1000000000000000000;
LL ans;

void dfs(LL L,LL R){
    if(L<0) return;
    if(L==0) ans=min(ans,R);
    if(R>=ans) return;
    if(R-L+1>L) return;
    dfs(L,R+(R-L+1));
    if(R-L+1>1)
        dfs(L,R+(R-L+1)-1);
    dfs(L-(R-L+1),R);
    dfs(L-(R-L+1)-1,R);
}
int main(){
    LL L,R;
    while(scanf("%I64d%I64d",&L,&R)!=EOF){
        ans=INF;
        dfs(L,R);
        if(ans!=INF)
            printf("%I64d\n",ans);
            else puts("-1");
    }
    return 0;
}
