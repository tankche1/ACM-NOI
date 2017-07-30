# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=10000;
int n=6666;
int a[7000];
int num[2300];
int G[2300];
int dp[2020][2020];

bool dfs(int cur,int S,int use,int tt){
    if(use==0){
        if(S==0){
            return true;
        }
        return false;
    }
    if(cur>2016) return false;
    if(num[cur]==0) return dfs(cur+1,S,use,tt);
    if(dp[use][S]<tt) return false;
    dp[use][S]=tt;
    int SS;
    for(int i=0;i<=num[cur]&&i<=use;i++){
        SS=S+i*cur;while(SS>=2016) SS-=2016;
        G[cur]=i;
        if(dfs(cur+1,SS,use-i,i>0?cur:tt)) return true;
    }return false;
}
int main(){
    freopen("input.txt","r",stdin);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        num[a[i]]++;
    }
    for(int i=0;i<=2016;i++) for(int j=0;j<=2016;j++) dp[i][j]=INF;
    dfs(1,0,2016,INF);
    for(int i=1;i<=n;i++){
        if(G[a[i]]>0) {G[a[i]]--;printf("%d\n",i);}
    }
    return 0;
}
