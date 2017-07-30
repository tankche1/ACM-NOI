# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=1000010;
vector<int> G[maxn],weight[maxn];
int n,m;
int p[maxn],u[maxm],v[maxm],w[maxm],bh[maxm];

bool cmp(int a,int b){
    return w[a]<w[b];
}

int find(int x){
    if(x==p[x]) return x;
    return p[x]=find(p[x]);
}

long long want;

void Kruskal(){
    sort(bh+1,bh+m+1,cmp);want=0;
    for(int i=1;i<=n;i++) p[i]=i;

    for(int i=1;i<=m;i++){
        int e=bh[i];
        int px=find(u[e]),py=find(v[e]);
        if(px!=py){
            p[px]=py;want+=w[e];
            G[u[e]].push_back(v[e]);weight[u[e]].push_back(w[e]);
            G[v[e]].push_back(u[e]);weight[v[e]].push_back(w[e]);
        }
    }

}
int size[maxn];
long long ans;

void dfs(int x,int fa){
    size[x]=1;
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa) continue;

        dfs(G[x][e],x);size[x]+=size[G[x][e]];
        ans+=(long long)size[G[x][e]]*(n-size[G[x][e]])*weight[x][e];
       // printf("x:%d v:%d w:%d\n",x,G[x][e],weight[x][e]);
       // printf("ans:%I64d\n",ans);
    }
}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u[i],&v[i],&w[i]);bh[i]=i;
        }

        for(int i=1;i<=n;i++) G[i].clear(),weight[i].clear();
        Kruskal();

        ans=0;
        dfs(1,1);

        double _ans=ans*2/(n*1.0)/((n-1)*1.0);
        printf("%I64d %.2lf\n",want,_ans);
    }
    return 0;
}
