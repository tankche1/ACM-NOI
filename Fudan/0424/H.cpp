# include<stdio.h>
# include<iostream>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=500010;
vector<int> G[maxn];
int n,m;
int fa[maxn],dep[maxn],bh[maxn],A[maxn];
int t[maxn];
bool vis[maxn];

void dfs1(int x){
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa[x]) continue;
        dep[G[x][e]]=dep[x]+1;fa[G[x][e]]=x;
        dfs1(G[x][e]);
    }
}

bool cmp(int a,int b){return dep[a]>dep[b];}

int S[maxn],top;

void dfs2(int x){
    S[++top]=x;
    if(vis[x]){
        vis[x]=1;
        dfs2(fa[x]);
    }
    else{
        for(int e=0;e<(int)G[x].size();e++){
            if(G[x][e]!=fa[x]&&!vis[G[x][e]]){
                vis[G[x][e]]=1;dfs2(G[x][e]);
            }
        }
    }
}

int Q[maxn];

void dfs3(int x){
    if(x<=m) return;
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa[x]) continue;
        dfs3(G[x][e]);
    }

    int cnt=0;
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa[x]) continue;
        Q[++cnt]=A[G[x][e]];
    }
    sort(Q+1,Q+cnt+1);
    int mid;
    if(cnt&1) mid=cnt/2+1;
    else{
        if(x==n) mid=cnt/2;
        else{
            if(t[x]==1){
                mid=cnt/2;
            }
            else mid=cnt/2+1;
        }
    }
    A[x]=Q[mid];
}

int main(){
    int a,b;
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        G[a].push_back(b);G[b].push_back(a);
    }

    for(int i=1;i<=m;i++) scanf("%d",&A[i]);
    fa[n]=n;dep[n]=1;
    dfs1(n);

    memset(vis,false,sizeof(vis));vis[n]=1;
    for(int i=1;i<=m;i++) bh[i]=i;
    sort(bh+1,bh+m+1,cmp);
    for(int i=1;i<=m;i++){
        if(!vis[i]){
            top=-1;
            dfs2(i);
            int val=A[S[0]]>=A[S[top]],now=0;
            while(now<top&&fa[S[now]]==S[now+1]) t[now]=val;
            val=-val;
            now=top;
            while(now>0&&fa[S[now]]==S[now-1]) t[now]=val;
        }
    }

    dfs3(n);
    long long ans=0;
    for(int i=1;i<n;i++){
        ans+=abs(A[fa[i]]-A[i]);
    }

    cout << ans <<endl;
    return 0;
}
