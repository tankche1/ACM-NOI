# include<stdio.h>
# include<string.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int n,m;
int black[maxn];
LL vis[maxn][2];
int belong[maxn][2];
vector<int> G[maxn],cost[maxn];

struct Node{
    int u;LL dis;int ori;
    Node(int u=0,LL dis=0,int ori=0):u(u),dis(dis),ori(ori) {}
    bool operator < (const Node &rhs)const{
        return dis>rhs.dis;
    }
};

priority_queue<Node> Q;

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&black[i]);
        if(black[i]) Q.push(Node(i,0,i));
    }

    int a,b,c;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a,&b,&c);
        G[a].push_back(b);cost[a].push_back(c);
        G[b].push_back(a);cost[b].push_back(c);
    }

    memset(vis,-1,sizeof(vis));memset(belong,-1,sizeof(belong));
    Node now;
    while(!Q.empty()){
        now=Q.top();Q.pop();
        //printf("now.u:%d now.dis:%d\n",now.u,now.dis);
        if(vis[now.u][0]==-1) vis[now.u][0]=now.dis,belong[now.u][0]=now.ori;
        else{
            if(vis[now.u][1]==-1&&belong[now.u][0]!=now.ori) vis[now.u][1]=now.dis,belong[now.u][1]=now.ori;
            continue;
        }
        for(int e=0;e<(int)G[now.u].size();e++){
            Q.push(Node(G[now.u][e],now.dis+cost[now.u][e],now.ori));
        }
    }

    LL ans=(LL)10000000000000000;int pos=-1;
    for(int i=1;i<=n;i++){
        if(vis[i][0]!=-1&&vis[i][1]!=-1){
            if(vis[i][0]+vis[i][1]<ans){
                ans=vis[i][0]+vis[i][1];
                pos=i;
            }
        }
    }
    if(pos==-1) puts("No luck at all");
    else printf("%I64d\n%d %d\n",ans,belong[pos][0],belong[pos][1]);
    return 0;
}
