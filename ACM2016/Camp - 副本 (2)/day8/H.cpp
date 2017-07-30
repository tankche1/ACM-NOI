# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n;
typedef long long LL;
int vis[1100][1100];
int tot=0;
LL ans=0;

void dfs(int cur,int x,int y){
    if(!vis[x+500][y+500]) tot++;
    vis[x+500][y+500]++;
    if(cur>n){
        ans+=tot;
        if(--vis[x+500][y+500]==0) tot--;
        return;
    }
    dfs(cur+1,x+1,y);
    dfs(cur+1,x-1,y);
    dfs(cur+1,x,y+1);
    dfs(cur+1,x,y-1);
    if(--vis[x+500][y+500]==0) tot--;
    return;
}
int main(){
    for(n=1;n<=20;n++){
            ans=0;
    dfs(1,0,0);
    printf("i:%d %I64d ",n,ans);
    double tt=(double)ans/((1<<(2*n))*1.0);
    printf("%.20lf\n",tt);
    }
    return 0;
}
