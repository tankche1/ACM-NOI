# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=300010;
int first[maxn],nnext[maxm<<1],edge=0,u[maxm<<1],v[maxm<<1],pre[maxm<<1],bh[maxm<<1];
bool flag[maxm<<1];
int n,m;
int ans[maxm];

void add_edge(int a,int b,int num,bool op){
    if(first[a]!=-1) pre[first[a]]=edge;
    bh[edge]=num;
    nnext[edge]=first[a];u[edge]=a;v[edge]=b;first[a]=edge;flag[edge]=op;pre[edge]=-1;edge++;
}
int now=0;

void del(int e){
    if(pre[e]==-1){
        first[u[e]]=nnext[e];pre[nnext[e]]=-1;
    }
    else{
        nnext[pre[e]]=nnext[e];pre[nnext[e]]=pre[e];
    }
}

bool dfs(int x){
    bool ok,vis=false;
    now^=1;
    while(1){
            //printf("x:%d\n",x);
        ok=false;
        for(int e=first[x];e!=-1;e=nnext[e]){
            ok=true;vis=1;
            ans[bh[e]]=flag[e]^now;
            x=v[e];
            del(e);del(e^1);break;
        }
      if(!ok) break;
    }
    return vis;
}

int main(){
    int tcase,a,b;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&n,&m);
        memset(first,-1,sizeof(first));edge=0;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&a,&b);
            if(a==b) ans[i]=true;
            add_edge(a,b,i,1);
            add_edge(b,a,i,0);
        }
        for(int i=1;i<=n;i++){
            while(dfs(i));
        }
        for(int i=1;i<=m;i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}
