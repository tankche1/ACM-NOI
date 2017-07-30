# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=200010;
int n,k;
int a[maxn],x[maxn];
vector<int> G[maxn];
int dp[maxn],up[maxn],fa[maxn];//size 表示全覆盖 else表示不能全覆盖
# define _size size
int size[maxn];
int limit;

void get_size(int x){
    size[x]=1;
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa[x]) continue;
        fa[G[x][e]]=x;
        get_size(G[x][e]);
        size[x]+=size[G[x][e]];
    }
}

void dfs1(int x){
    int big1=0,num=0;
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa[x]) continue;
        dfs1(G[x][e]);
        if(dp[G[x][e]]==size[G[x][e]]) num+=size[G[x][e]];
        else{
            if(dp[G[x][e]]>big1) big1=dp[G[x][e]];
            //else if(dp[G[x][e]]>big2) big2=dp[G[x][e]];
        }
    }
    if(a[x]<limit) dp[x]=0;
    else{
        dp[x]=num+big1+1;
    }
}

void dfs2(int x){
    int big1=0,big2=0,num=0;
    if(a[x]>=limit){
        num++;
        if(up[x]==n-size[x]) num+=up[x];
        else{
            if(up[x]>big1) big1=up[x];
            else if(up[x]>big2) big2=up[x];
        }
        for(int e=0;e<(int)G[x].size();e++){
            if(G[x][e]==fa[x]) continue;
            if(dp[G[x][e]]==size[G[x][e]]) num+=size[G[x][e]];
            else{
                if(dp[G[x][e]]>big1) big1=dp[G[x][e]];
                else if(dp[G[x][e]]>big2) big2=dp[G[x][e]];
            }
        }
    }

    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa[x]) continue;
        if(a[x]<limit) up[G[x][e]]=0;
        else{
            if(dp[G[x][e]]==size[G[x][e]]) up[G[x][e]]=num-size[G[x][e]]+big1;
            else{
                if(dp[G[x][e]]==big1) up[G[x][e]]=num+big2;
                else up[G[x][e]]=num+big1;
            }
        }
    }

    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa[x]) continue;
        dfs2(G[x][e]);
    }
}

bool solve(int lim){
    limit=lim;
    dfs1(1);
    up[1]=0;
    dfs2(1);
    int num,big;
    for(int i=1;i<=n;i++){
        if(a[i]<limit) continue;
        num=1;big=0;
        if(up[i]==n-size[i]) num+=up[i];
        else big=max(big,up[i]);
        for(int e=0;e<(int)G[i].size();e++){
            if(G[i][e]!=fa[i]){
                if(dp[G[i][e]]==size[G[i][e]]) num+=dp[G[i][e]];
                else big=max(big,dp[G[i][e]]);
            }
        }
        if(num+big>=k) return true;
    }
    return false;
}

int main(){
    int u,v;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),x[i]=a[i];
    sort(x+1,x+n+1);
    int cnt=unique(x+1,x+n+1)-x;
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(x+1,x+cnt,a[i])-x;

    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
    }

    fa[1]=1;get_size(1);

    int L=1,R=cnt-1,M;
    while(L<=R){
        M=(L+R)>>1;
        if(solve(M)) L=M+1;
        else R=M-1;
    }

    printf("%d\n",x[L-1]);
    return 0;
}
