# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=30010;
const int INF=~0U>>1;
int n,m,s,t;
int first[maxn],next[maxm<<1],u[maxm<<1],v[maxm<<1],w[maxm<<1],edge;
bool vis[maxn];
int last[maxn];
bool del[maxm<<1];

void add_edge(int a,int b,int c){
    next[edge]=first[a];u[edge]=a;v[edge]=b;w[edge]=c;first[a]=edge++;
}

queue<int> Q;
void bfs(){
    last[s]=-1;
    Q.push(s);vis[s]=1;
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        if(x==t) break;
        for(int e=first[x];e!=-1;e=next[e]){
            if(!vis[v[e]]){
                vis[v[e]]=1;Q.push(v[e]);last[v[e]]=e;
            }
        }
    }
}

int ans=INF;
vector<int> print;

int low[maxn],pre[maxn],dfs_clock;
bool isbridge[maxm<<1];

void find_bridge(int x,int from){
    pre[x]=++dfs_clock;low[x]=pre[x];
    for(int e=first[x];e!=-1;e=next[e]){
        if(e==from||del[e]) continue;
        if(!pre[v[e]]){
            find_bridge(v[e],e^1);
            low[x]=min(low[x],low[v[e]]);
            if(low[v[e]]>pre[x]){
                isbridge[e]=isbridge[e^1]=1;
            }
        }
        else{
            low[x]=min(low[x],pre[v[e]]);
        }
    }
}

int aa=-1;
bool dfs(int x,int t){
    if(x==t) return true;

    vis[x]=1;
    bool ok=false;
    for(int e=first[x];e!=-1;e=next[e]){
        if(del[e]) continue;
        if(vis[v[e]]) continue;
        if(isbridge[e]){
            if(dfs(v[e],t)){
                ok=true;
                if(aa==-1||w[e]<w[aa]) aa=e;
                break;
            }
        }
        else{
            if(dfs(v[e],t)) {ok=true;break;}
        }
    }
    //printf("x:%d t:%d ok:%d\n",x,t,ok);
    return ok;
}

int main(){
    int a,b,c;
    scanf("%d%d",&n,&m);
    scanf("%d%d",&s,&t);
    memset(first,-1,sizeof(first));edge=0;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a,&b,&c);add_edge(a,b,c);add_edge(b,a,c);
    }

    bfs();
    if(!vis[t]) {printf("0\n0\n\n");return 0;}

    int now=t;
    while(now!=s){
        del[last[now]]=1;del[last[now]^1]=1;
        //printf("now:%d last:%d\n",now,last[now]/2+1);

        for(int i=1;i<=n;i++) pre[i]=0;dfs_clock=0;
        for(int i=0;i<2*m;i++) isbridge[i]=0;
        for(int i=1;i<=n;i++) if(!pre[i]) find_bridge(i,-1);

        for(int i=1;i<=n;i++) vis[i]=0;aa=-1;
        if(!dfs(s,t)){
            if(w[last[now]]<ans) ans=w[last[now]],print.clear(),print.push_back(last[now]/2+1);
        }
        else if(aa!=-1&&w[last[now]]+w[aa]<ans){
            ans=w[last[now]]+w[aa],print.clear(),print.push_back(last[now]/2+1),print.push_back(aa/2+1);
        }

        del[last[now]]=0;del[last[now]^1]=0;
        now=u[last[now]];
    }

    if(ans==INF) {puts("-1");return 0;}

    printf("%d\n",ans);
    printf("%d\n",(int)print.size());
    if(print.size()==1) printf("%d\n",print[0]);
    else printf("%d %d\n",print[0],print[1]);
    return 0;
}
