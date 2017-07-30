# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=110;
const int maxm=210;
int n,m,Bag,uni,r,Ti;

int p[5][maxn];
int dp[5][maxn][5][220];

struct Edge{
    int to,t,cost;
    Edge(){}
    Edge(int to,int t,int cost):to(to),t(t),cost(cost) {}
};
int first[maxn],_next[maxm<<1],edges=0;
Edge edge[maxm<<1];

void add_edge(int a,int b,int c,int d){
    _next[edges]=first[a];first[a]=edges;
    edge[edges++]=Edge(b,c,d);
}

//vector<Node> G[maxn];


struct HeapNode{
    int k,x,b,t,money;
    HeapNode() {}
    HeapNode(int k,int x,int b,int t,int money):k(k),x(x),b(b),t(t),money(money) {}

    bool operator < (const HeapNode &rhs)const{
        return t>rhs.t;
    }
};
priority_queue<HeapNode> Q;
HeapNode now,nex;

void join(){
    if(nex.money<0) return;
    //printf("join x:%d k:%d b:%d t:%d money:%d\n",nex.x,nex.k,nex.b,nex.t,nex.money);
    if(dp[nex.k][nex.x][nex.b][nex.t]<nex.money){
            dp[nex.k][nex.x][nex.b][nex.t]=nex.money;
            Q.push(HeapNode(nex.k,nex.x,nex.b,nex.t,nex.money));
    }
    if(nex.b<Bag&&nex.money>=p[nex.k][nex.x]&&nex.x!=1&&nex.x!=n){
        nex.b++;nex.money-=p[nex.k][nex.x];
        if(dp[nex.k][nex.x][nex.b][nex.t]<nex.money){
            dp[nex.k][nex.x][nex.b][nex.t]=nex.money;
            Q.push(HeapNode(nex.k,nex.x,nex.b,nex.t,nex.money));
        }
        nex.b--;nex.money+=p[nex.k][nex.x];
    }
    if(nex.b>0&&nex.x!=1&&nex.x!=n){
        nex.b--;nex.money+=p[nex.k][nex.x];
        if(dp[nex.k][nex.x][nex.b][nex.t]<nex.money){
            //printf("sold %d\n",nex.money);
            dp[nex.k][nex.x][nex.b][nex.t]=nex.money;
            Q.push(HeapNode(nex.k,nex.x,nex.b,nex.t,nex.money));
        }
        nex.b++;nex.money-=p[nex.k][nex.x];
    }
}

void dijkstra(){
    while(!Q.empty()) Q.pop();
    Q.push(HeapNode(0,1,0,0,r));
    dp[0][1][0][0]=r;

    while(!Q.empty()){
        now=Q.top();Q.pop();
        if(now.t>=Ti) break;
        if(dp[now.k][now.x][now.b][now.t]>now.money) continue;
        if(now.x==n) continue;
        if(now.k!=0&&now.x==1) continue;
        //printf("x:%d k:%d b:%d t:%d money:%d\n",now.x,now.k,now.b,now.t,now.money);

        //change universe
        nex.k=(now.k+1)%uni;nex.x=now.x;nex.b=now.b;nex.t=now.t+1;nex.money=now.money;
        join();
        //road
        for(int e=first[now.x];e!=-1;e=_next[e]){
            nex.k=now.k;nex.x=edge[e].to;nex.b=now.b;nex.t=now.t+edge[e].t;nex.money=now.money-edge[e].cost;
            join();
        }

    }

}


int main(){
    int Case;
    int a,b,c,d;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d%d%d%d%d%d",&n,&m,&Bag,&uni,&r,&Ti);
        for(int k=0;k<uni;k++){
            for(int i=1;i<=n;i++){
                scanf("%d",&p[k][i]);
            }
        }

        edges=0;memset(first,-1,sizeof(first));
        for(int i=1;i<=m;i++){
            scanf("%d%d%d%d",&a,&b,&c,&d);
            add_edge(a,b,c,d);
        }

        for(int k=0;k<uni;k++){
            for(int i=1;i<=n;i++){
                for(int b=0;b<=Bag;b++){
                    for(int t=0;t<=Ti+16;t++) dp[k][i][b][t]=-1;
                }
            }
        }

        dijkstra();
        printf("Case #%d: ",Tcase);
        int ans=-1;
        for(int t=0;t<=Ti;t++){
            ans=max(ans,dp[0][n][0][t]);
        }
        if(ans==-1) puts("Forever Alone");
        else printf("%d\n",ans);
    }
    return 0;
}
