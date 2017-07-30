# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=10010;
const int maxm=100010;
LL c[maxn];
int first[maxn],nnext[maxm<<1],v[maxm<<1],w[maxm<<1],edge=0;
int n,m;

struct HeapNode{
    LL c;int x;
    HeapNode(LL c=0,int x=0):c(c),x(x) {}
    bool operator < (const HeapNode &rhs)const{
        return c>rhs.c;
    }
};
priority_queue<HeapNode> Q;
bool used[maxn];

void add_edge(int a,int b,int cost){
    nnext[edge]=first[a];v[edge]=b;w[edge]=cost;first[a]=edge++;
}
int main(){
    freopen("dwarf.in","r",stdin);
    freopen("dwarf.out","w",stdout);
    int x,y,z;
    memset(first,-1,sizeof(first));edge=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%I64d",&c[i]);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        add_edge(y,x,z);add_edge(z,x,y);
    }
    for(int i=1;i<=n;i++){
        Q.push(HeapNode(c[i],i));
    }
    while(!Q.empty()){
        int x=Q.top().x;Q.pop();
        if(used[x]) continue;
        if(x==1) break;
        used[x]=1;
        for(int e=first[x];e!=-1;e=nnext[e]){
            if(c[v[e]]>c[x]+c[w[e]]){
                c[v[e]]=c[x]+c[w[e]];
                Q.push(HeapNode(c[v[e]],v[e]));
            }
        }
    }
    printf("%I64d\n",c[1]);
    return 0;
}
