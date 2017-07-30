# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
bool a[10][10];
int num[10],n,m;
bool vis[10];
bool T[10];
int left[10];
int ans;
int g[10][10];

bool match(int x){
    for(int i=1;i<=n;i++){
        if(g[x][i]){
            if(!T[i]){
                T[i]=1;
                if(left[i]==-1||match(left[i])){
                    left[i]=x;return true;
                }
            }
        }
    }
    return false;
}

void solve(){
    memset(g,0,sizeof(g));
    for(int i=1;i<=n;i++){
        if((!a[i][num[1]])&&(!a[i][num[n]])) g[1][i]=1;
    }

    for(int pos=2;pos<=n;pos++){
        for(int i=1;i<=n;i++){
            if((!a[i][num[pos-1]])&&(!a[i][num[pos]])) g[pos][i]=1;
        }
    }

    memset(left,-1,sizeof(left));
    int cnt=0;
    for(int i=1;i<=n;i++){
        memset(T,0,sizeof(T));
        if(match(i)) cnt++;
    }
    ans=min(ans,n-cnt);
}

void dfs(int cur){
    if(cur>n){
        solve();return;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            num[cur]=i;vis[i]=1;dfs(cur+1);vis[i]=0;
        }
    }
}

int main(){
    int x,y;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(a,0,sizeof(a));
        for(int i=1;i<=m;i++){
            scanf("%d%d",&x,&y);a[x][y]=1;
        }
        memset(vis,0,sizeof(vis));
        num[1]=1;vis[1]=1;ans=n;
        dfs(2);

        printf("%d\n",ans);
    }
    return 0;
}
