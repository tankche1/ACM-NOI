# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=1010;
int tcase;
int go[maxn];
vector<int> from[maxn];
int n;
int S[maxn],top=-1;
bool vis[maxn];
int huan[maxn],cnt=0;
int ans,tot=0;
int dp[maxn];
bool in[maxn];

void dfs(int x){
    //printf("x:%d\n",x);
    vis[x]=1;
    dp[x]=1;
    for(int e=0;e<(int)from[x].size();e++){
        if(!in[from[x][e]]){
            dfs(from[x][e]);dp[x]=max(dp[x],dp[from[x][e]]+1);
        }
    }
}

int main(){
   // freopen("C-large.in","r",stdin);
    //freopen("output.txt","w",stdout);
    int a,b;
    scanf("%d",&tcase);
    for(int Tcase=1;Tcase<=tcase;Tcase++){
            int need=0;
        ans=0;tot=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) from[i].clear();
        for(int i=1;i<=n;i++){
            scanf("%d",&b);go[i]=b;from[b].push_back(i);
        }
        printf("Case #%d: ",Tcase);
        /*if(Tcase==12){
            printf("n:%d\n",n);
            for(int i=1;i<=n;i++){
                printf("%d ",go[i]);
            }puts("");
        }*/

        memset(vis,0,sizeof(vis));memset(in,0,sizeof(in));
        for(int i=1;i<=n;i++){
            int x=i;
            if(!vis[x]){
                //printf("x:%d\n",x);
                S[top=0]=x;vis[x]=1;
                while(!vis[go[x]]){
                    S[++top]=go[x];x=go[x];vis[x]=1;
                }
                //printf("x:%d\n",x);
                cnt=0;
                while(S[top]!=go[x]){
                    huan[cnt++]=S[top--];in[S[top+1]]=1;
                }
                huan[cnt++]=go[x];top--;in[go[x]]=1;
                //printf("huan:");
                //for(int i=0;i<cnt;i++) printf("%d ",huan[i]);puts("");
                int big=0;
                for(int i=0;i<cnt;i++) dfs(huan[i]);
                if(cnt>2) ans=max(ans,cnt);
                else{
                    //for(int i=0;i<cnt;i++) big=max(big,dp[huan[i]]+cnt-1);
                    //need=min(dp[huan[0]],dp[huan[1]])-1;
                    big=dp[huan[0]]+dp[huan[1]];
                }
                tot+=big;
            }
        }
        tot+=need;
        ans=max(ans,tot);
        printf("%d\n",ans);
    }
    return 0;
}
