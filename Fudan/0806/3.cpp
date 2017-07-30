# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
vector<int> ans[maxn];
bool vis[maxn];
LL n;
int m;
int main(){
    int tcase;
    LL sum,need,now;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%I64d%d",&n,&m);
        sum=0;
        for(int i=1;i<=n;i++) sum+=i;
        if(sum%m) {puts("NO");continue;}
        need=sum/m;
        bool ok=true;
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=m;i++){
                ans[i].clear();
            now=need;
            for(int j=n;j>=1;j--){
                if(!vis[j]&&now>=j) {ans[i].push_back(j);vis[j]=1;now-=j;if(now==0) break;}
            }
            if(now>0) {ok=false;break;}
        }
        if(!ok){puts("NO");continue;}
        puts("YES");
        for(int i=1;i<=m;i++){
            printf("%d",(int)ans[i].size());
            for(int j=0;j<(int)ans[i].size();j++){
                printf(" %d",ans[i][j]);
            }puts("");
        }
    }
    return 0;
}
