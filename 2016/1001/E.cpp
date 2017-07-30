# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<queue>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
const LL INF=(LL)1<<60;
int x[maxn],y[maxn],c[maxn],w[maxn];
int first[maxn],_next[maxn],cost[maxn],v[maxn],edge;
LL d[maxn];

int n,m;

void add_edge(int a,int b,int c){
    _next[edge]=first[a];v[edge]=b;cost[edge]=c;first[a]=edge++;
}

bool used[maxn];

struct HeapNode{
    int x;LL dis;
    HeapNode() {}
    HeapNode(int x,LL dis):x(x),dis(dis) {}
    bool operator < (const HeapNode &rhs)const{
        return dis>rhs.dis;
    }
};
priority_queue<HeapNode> Q;
LL ans;

bool Dijkstar(){
    ans=0;
    HeapNode now;
    for(int i=1;i<=n;i++) d[i]=INF,used[i]=0;
    for(int i=1;i<=n;i++){
        if(w[i]==0) d[i]=0;
        Q.push(HeapNode(i,d[i]));
    }

    while(!Q.empty()){
        now=Q.top();Q.pop();
        if(used[now.x]) continue;
        used[now.x]=1;

        for(int e=first[now.x];e!=-1;e=_next[e]){
            if(d[v[e]]>d[now.x]+cost[e]){
                d[v[e]]=d[now.x]+cost[e];
                Q.push(HeapNode(v[e],d[v[e]]));
            }
        }
    }

    for(int i=1;i<=n;i++) if(w[i]==2) {ans+=d[i];if(d[i]==INF) return false;}
    return true;
}
int main(){


    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d%d",&m,&n);
        for(int i=1;i<=n;i++) first[i]=-1;edge=0;
        for(int i=1;i<=m;i++) scanf("%d",&x[i]);
        for(int i=1;i<=m;i++) scanf("%d",&y[i]);
        for(int i=1;i<=m;i++) scanf("%d",&c[i]);
        for(int i=1;i<=n;i++) scanf("%d",&w[i]);

        for(int i=1;i<=m;i++) add_edge(y[i],x[i],c[i]);
        printf("Case #%d: ",Tcase);
        if(!Dijkstar()) puts("-1");
        else printf("%I64d\n",ans);


    }
    return 0;
}
