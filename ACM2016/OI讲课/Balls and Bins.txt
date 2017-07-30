# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=200010;
vector<int> Face[maxn],Back[maxn];
int n,m,q;
int w[maxn];
int visited[maxn],timestamp=0;
int match_x[maxn],match_y[maxn];

bool cmp_byweight(int a,int b){
    return w[a]>w[b];
}

bool find(int u){
    visited[u]=timestamp;
    int v;
    for(int e=0;e<(int)Face[u].size();e++){
        v=Face[u][e];
        if(match_y[v]==-1){
            match_y[v]=u;match_x[u]=v;return true;
        }
    }
    for(int e=0;e<(int)Face[u].size();e++){
        v=Face[u][e];
        if(visited[match_y[v]]!=timestamp&&find(match_y[v])){
            match_y[v]=u;match_x[u]=v;return true;
        }
    }
    return false;
}

int parent[maxn],vie[maxn];

void dfs(int u){
    visited[u]=timestamp;
    int v;
    for(int e=0;e<(int)Face[u].size();e++){
        v=Face[u][e];
        if(match_y[v]!=-1&&visited[match_y[v]]!=timestamp){
            parent[match_y[v]]=u;vie[match_y[v]]=v;
            dfs(match_y[v]);
        }
    }
}

void rdfs(int u){
    visited[u]=timestamp;
    int v;
    if(match_x[u]==-1) return;
    for(int e=0;e<(int)Back[match_x[u]].size();e++){
        v=Back[match_x[u]][e];
        if(visited[v]!=timestamp){
            parent[v]=u;vie[v]=match_x[u];
            rdfs(v);
        }
    }
}

int main(){
    int a,b,u,nw;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);
        Face[a].push_back(b);Back[b].push_back(a);
    }

    int bh[maxn];
    for(int i=1;i<=n;i++) bh[i]=i;
    sort(bh+1,bh+n+1,cmp_byweight);

    int sum=0;memset(match_x,-1,sizeof(match_x));memset(match_y,-1,sizeof(match_y));
    for(int i=1;i<=n;i++){
        if(w[bh[i]]<=0) break;
        timestamp++;
        if(find(bh[i])) sum+=w[bh[i]];
    }

    int best;
    for(int tt=1;tt<=q;tt++){
        scanf("%d%d",&u,&nw);
        timestamp++;
        if(match_x[u]==-1){
            w[u]=nw;
            if(w[u]<=0) goto Loop;
            if(find(u)) {sum+=w[u];goto Loop;}
            timestamp++;
            dfs(u);
            best=u;
            for(int i=1;i<=n;i++){
                if(visited[i]==timestamp&&w[i]<w[best]){
                    best=i;
                }
            }
            if(best==u) {goto Loop;}
            sum+=w[u]-w[best];
            match_x[best]=-1;
            while(best!=u){
                match_y[vie[best]]=parent[best];match_x[parent[best]]=vie[best];
                best=parent[best];
            }
        }else{
            sum-=w[u];
            w[u]=nw;
            rdfs(u);
            best=u;
            for(int i=1;i<=n;i++){
                if(visited[i]==timestamp&&match_x[i]==-1&&w[i]>w[best]){
                    best=i;
                }
            }
            if(w[best]<=0) {match_y[match_x[u]]=-1;match_x[u]=-1;goto Loop;}
            if(best==u) {sum+=w[u];goto Loop;}

            sum+=w[best];
            while(best!=u){
                match_x[best]=vie[best];match_y[vie[best]]=best;best=parent[best];
            }
            match_x[u]=-1;
        }
        Loop:
        printf("%d\n",sum);
    }
    return 0;
}
