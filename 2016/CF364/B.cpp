# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=200010;
vector<int> G[maxn];
int n,k;
bool vis[maxn];
int size[maxn],dep[maxn];
typedef long long LL;
LL ans=0;

void dfs1(int x,int fa){
    size[x]=vis[x];
    if(vis[x]) ans+=dep[x];
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa) continue;
        dep[G[x][e]]=dep[x]+1;
        dfs1(G[x][e],x);
        size[x]+=size[G[x][e]];
    }
    return;
}

void dfs2(int x,int fa,int num){
    //printf("x:%d fa:%d num:%d ans:%I64d\n",x,fa,num,ans);
    int big=0,son=-1;
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa) continue;
        if(size[G[x][e]]>big) big=size[G[x][e]],son=G[x][e];
    }

    if(big-(size[x]-num)<=size[x]-size[son]) {//printf("minus: %I64d\n",(LL)num*dep[x]);
    ans-=(LL)num*dep[x];return;}
    ans-=(LL)(size[x]-size[son])*2*dep[x];
    dfs2(son,x,big-(size[x]-num)-(size[x]-size[son]));
}

int main(){
    int x,a,b;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=2*k;i++){
        scanf("%d",&x);
        vis[x]=1;
    }

    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dep[1]=1;dfs1(1,1);

    dfs2(1,1,size[1]);

    printf("%I64d\n",ans);
    return 0;
}
