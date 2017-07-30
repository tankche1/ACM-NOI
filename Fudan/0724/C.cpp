# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=20010;
typedef long long LL;
const LL INF=(LL)100000000000000;
int n,m;
int cost[maxn],q;
int qx[maxm],qy[maxm];
LL ans[maxm];
int first[maxn],nnext[maxm<<1],to[maxm<<1],edge=0,dis[maxm<<1];

void add_edge(int a,int b,int c){
    nnext[edge]=first[a];to[edge]=b;dis[edge]=c;first[a]=edge++;
}
struct HeapNode{
    int x;LL val;
    HeapNode(int x=0,LL val=0):x(x),val(val) {}
    bool operator < (const HeapNode &rhs)const{
    return val>rhs.val;
    }
};
priority_queue<HeapNode> que;
bool used[maxn];
LL d[maxn];

void solve(int st){
   for(int i=1;i<=n;i++) used[i]=false,d[i]=INF;
   que.push(HeapNode(st,0));d[st]=0;
   while(!que.empty()){
     int x=que.top().x;que.pop();
     if(used[x]) continue;
     used[x]=1;
     for(int e=first[x];e!=-1;e=nnext[e]){
        if(cost[to[e]]>cost[st]) continue;
        if(d[to[e]]>d[x]+dis[e]){
            d[to[e]]=d[x]+dis[e];que.push(HeapNode(to[e],d[to[e]]));
        }
     }
   }
   for(int i=1;i<=q;i++)
    ans[i]=min(ans[i],d[qx[i]]+d[qy[i]]+cost[st]);
}

int main(){
    int a,b,c;
    while(scanf("%d%d",&n,&m)!=EOF){
        edge=0;memset(first,-1,sizeof(first));
        if(n==0&&m==0) break;
        for(int i=1;i<=n;i++) scanf("%d",&cost[i]);
        for(int i=0;i<m;i++) scanf("%d%d%d",&a,&b,&c),add_edge(a,b,c),add_edge(b,a,c);
        scanf("%d",&q);
        for(int i=1;i<=q;i++)
            scanf("%d%d",&qx[i],&qy[i]),ans[i]=INF;

        for(int i=1;i<=n;i++){
            solve(i);
        }
        for(int i=1;i<=q;i++){
            if(ans[i]==INF) puts("-1");
            else printf("%I64d\n",ans[i]);
        }
        puts("");
    }
    return 0;
}
