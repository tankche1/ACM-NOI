# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
const int INF=1000;
int g[510][510];
int n,k;
int st;
bool vis[510];
int print[510],top=0;
int first[510],next[510*510],v[510*510],edge=0;

void add_edge(int a,int b){
    next[edge]=first[a];
    v[edge]=b;
    first[a]=edge++;
}

bool dfs(int x){
    print[++top]=x;vis[x]=1;
    if(top==n){
        for(int e=first[x];e!=-1;e=next[e]){
            if(v[e]==st) return true;
        }
        top--;vis[x]=0;return false;
    }
    for(int e=first[x];e!=-1;e=next[e]){
        if(!vis[v[e]]){
            if(dfs(v[e])) return true;
        }
    }
    top--;vis[x]=0;
    return false;
}

int main(){
    srand(time(NULL));
    scanf("%d%d",&n,&k);
    char t;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            while((t=getchar())&&t!='0'&&t!='1');
            g[i][j]=t-'0';
            if(g[i][j]==0) g[i][j]=INF;
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
            }
        }
    }

    memset(first,-1,sizeof(first));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(g[i][j]<=k&&i!=j) add_edge(i,j);
    memset(vis,0,sizeof(vis));

    st=rand()%n+1;
    dfs(st);
    printf("%d",print[1]);
    for(int i=2;i<=n;i++)
        printf(" %d",print[i]);puts("");
    return 0;
}
