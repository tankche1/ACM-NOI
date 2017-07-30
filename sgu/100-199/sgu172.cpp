# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=210,maxm=30010;
int n,m;
int first[maxn],nnext[maxm<<1],v[maxm<<1],edge;
int col[maxn];

void add_edge(int a,int b){
    nnext[edge]=first[a];v[edge]=b;first[a]=edge++;
}

bool dfs(int x){
    for(int e=first[x];e!=-1;e=nnext[e]){
        if(col[v[e]]==-1){
            col[v[e]]=col[x]^1;if(!dfs(v[e])) return false;
        }
        else if(col[v[e]]==col[x]) return false;
    }
    return true;
}

int main(){
    int a,b;
    scanf("%d%d",&n,&m);
    edge=0;memset(first,-1,sizeof(first));
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);
        add_edge(a,b);add_edge(b,a);
    }

    bool ok=true;
    memset(col,-1,sizeof(col));
    for(int i=1;i<=n;i++){
        if(col[i]==-1){
            col[i]=1;
            if(!dfs(i)) {ok=false;break;}
        }
    }

    if(!ok) {puts("no");return 0;}
    puts("yes");
    int ans=0;
    for(int i=1;i<=n;i++){
        if(col[i]==0){
            ans++;
        }
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++){
        if(col[i]==0){
            printf("%d",i);
            if(--ans>0) printf(" ");
        }
    }
    return 0;
}
