# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=200010;
int first[maxn],nex[maxn<<1],v[maxn<<1],edge=0;
int du[maxn],w[maxn];int fa[maxn];
int n;

void add_edge(int a,int b){
    nex[edge]=first[a];v[edge]=b;first[a]=edge++;
}

int que[maxn];
bool vis[maxn];
void getq(){
    int rear=n,x;
        for(int i=1;i<=n;i++)
            if(du[i]==1) que[rear--]=i;

        memset(vis,false,sizeof(vis));
        for(int i=n;i>=1;i--){
            vis[que[i]]=1;x=que[i];
            for(int e=first[x];e!=-1;e=nex[e])
                if(!vis[v[e]]){
                    fa[x]=v[e];
                    if(--du[v[e]]==1) que[rear--]=v[e];
                }
        }fa[que[1]]=0;
}
int up[maxn][110],down[maxn][110];
int preup[maxn][110],predown[maxn][110];
int help[110];

void solve(){
    for(int i=n;i>=1;i--){
        int x=que[i];//printf("x:%d\n",x);
        for(int j=0;j<=100;j++){
            help[j]=0;up[x][j]=INF;

            for(int e=first[x];e!=-1;e=nex[e]){
                if(v[e]==fa[x]) continue;
                help[j]+=min(preup[v[e]][j+1],(j==0)?INF:(predown[v[e]][j-1]));
            }
            for(int e=first[x];e!=-1;e=nex[e]){
                if(v[e]==fa[x]) continue;
                up[x][j]=min(up[x][j],help[j]-min(preup[v[e]][j+1],(j==0)?INF:(predown[v[e]][j-1]))+up[v[e]][j+1]);
            }

            if(j==0){
                down[x][j]=0;
                for(int e=first[x];e!=-1;e=nex[e]){
                    if(v[e]==fa[x]) continue;
                    down[x][j]+=up[v[e]][0];
                }
            }
            else{
                help[j]=0;down[x][j]=INF;
                for(int e=first[x];e!=-1;e=nex[e]){
                    if(v[e]==fa[x]) continue;
                    help[j]+=min(predown[v[e]][j-1],preup[v[e]][j]);
                }
                for(int e=first[x];e!=-1;e=nex[e]){
                    if(v[e]==fa[x]) continue;
                    down[x][j]=min(down[x][j],help[j]-min(predown[v[e]][j-1],preup[v[e]][j])+down[v[e]][j-1]);
                }
            }
        }

        help[w[x]]=0;
        if(w[x]==0){
            for(int e=first[x];e!=-1;e=nex[e]){
                if(v[e]==fa[x]) continue;
                help[w[x]]+=preup[v[e]][w[x]+1];
            }
        }
        else{
              for(int e=first[x];e!=-1;e=nex[e]){
                      if(v[e]==fa[x]) continue;
                      help[w[x]]+=min(predown[v[e]][w[x]-1],preup[v[e]][w[x]+1]);
                  }
        }
        up[x][w[x]]=min(up[x][w[x]],help[w[x]]+1);
        preup[x][0]=up[x][0];predown[x][0]=down[x][0];
        for(int j=101;j<=103;j++) up[x][j]=down[x][j]=INF;
        for(int j=1;j<=103;j++)
            preup[x][j]=min(preup[x][j-1],up[x][j]),predown[x][j]=min(predown[x][j-1],down[x][j]);
    }
}


int main(){
    int a,b;
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
        }
        memset(first,-1,sizeof(first));edge=0;memset(du,0,sizeof(du));
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);du[a]++;du[b]++;
        }
        getq();
        solve();
        printf("%d\n",preup[que[1]][103]);
    }
    return 0;
}
