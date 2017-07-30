# include<stdio.h>
# include<string.h>
# include<vector>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=50010;
typedef long long LL;
const LL INF=(LL)10000000000;
int n,I,R;
int down[maxn],up[maxn];
LL downdist[maxn],updist[maxn];
int nnext[maxn<<1],first[maxn],v[maxn<<1],edge=0;

void add_edge(int a,int b){
    nnext[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void dfs1(int x,int fa){
    down[x]=1;downdist[x]=0;
    for(int e=first[x];e!=-1;e=nnext[e]){
        if(v[e]==fa) continue;
        dfs1(v[e],x);
        down[x]+=down[v[e]];downdist[x]+=downdist[v[e]]+down[v[e]];
    }
    return;
}

void dfs2(int x,int fa){
    for(int e=first[x];e!=-1;e=nnext[e]){
        if(v[e]==fa) continue;
        up[v[e]]=n-down[v[e]];updist[v[e]]=updist[x]+up[v[e]]+downdist[x]-downdist[v[e]]-down[v[e]];
        dfs2(v[e],x);
    }
}

vector<int> print;
int main(){
    int tcase;
    scanf("%d",&tcase);
    int a,b;
    while(tcase--){
        scanf("%d%d%d",&n,&I,&R);
        memset(first,-1,sizeof(first));edge=0;
        for(int i=1;i<n;i++)
            scanf("%d%d",&a,&b),add_edge(a,b),add_edge(b,a);

        down[1]=0;
        dfs1(1,0);
        up[1]=0;updist[1]=0;
        dfs2(1,0);

        long long ans=INF;
        print.clear();
        for(int i=1;i<=n;i++){
               // printf("i:%d up:%d down:%d updi:%I64d downdi:%I64d\n",i,up[i],down[i],updist[i],downdist[i]);
            if(updist[i]+downdist[i]<ans){
                ans=updist[i]+downdist[i];print.clear();print.push_back(i);
            }
            else if(updist[i]+downdist[i]==ans){
                print.push_back(i);
            }
        }
        printf("%I64d\n",ans*I*I*R);
        printf("%d",print[0]);
        for(int i=1;i<print.size();i++)
            printf(" %d",print[i]);puts("");puts("");
    }
    return 0;
}
