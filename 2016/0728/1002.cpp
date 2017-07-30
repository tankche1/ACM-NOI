# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n;
int w[maxn];
vector<int> G[maxn];
int du[maxn],root;
int a[maxn];
int p[maxn];
bool ok;

int find(int x){
    if(x==p[x]) return x;
    return p[x]=find(p[x]);
}

void dfs(int x,int fa){
    int big=0;
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa) continue;
        dfs(G[x][e],x);
        big=max(big,w[G[x][e]]);
    }
    if(big>w[x]) ok=false;
    if(w[x]>big) {
        a[x]=w[x];
        if(find(w[x])!=w[x]) ok=false;
        p[w[x]]=w[x]-1;
    }
    else a[x]=-(w[x]-1);
}

int main(){
    int T,x,y;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            G[i].clear();
            scanf("%d",&w[i]),du[i]=0;if(w[i]==n) root=i;
        }
        for(int i=1;i<n;i++){
            scanf("%d%d",&x,&y);
            if(w[x]==n&&w[y]==n) du[x]++,du[y]++;
            G[x].push_back(y);G[y].push_back(x);
        }

        for(int i=1;i<=n;i++) {if(du[i]==1) {root=i;break;}}

        for(int i=0;i<=n;i++) p[i]=i;

        ok=true;
        dfs(root,-1);


        for(int i=n;i>=1;i--){
            if(a[i]<0){
                a[i]=-a[i];
                a[i]=find(a[i]);
                if(a[i]==0) {ok=false;break;}
                p[a[i]]=a[i]-1;
            }
        }

        printf("Case #%d:",Tcase);
        if(!ok) puts(" Impossible");
        else{
            for(int i=1;i<=n;i++) printf(" %d",a[i]);
            puts("");
        }
    }
    return 0;
}
