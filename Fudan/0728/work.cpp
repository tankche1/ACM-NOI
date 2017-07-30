# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=110;
bool son[maxn];
int n,k;
int first[maxn],nnext[maxn<<1],v[maxn<<1],edge=0;
int dp[maxn];
void add_edge(int a,int b){
    nnext[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void dfs(int x){
    dp[x]=1;
    for(int e=first[x];e!=-1;e=nnext[e]){
        dfs(v[e]);dp[x]+=dp[v[e]];
    }
}
int main(){
    int a,b;
    while(scanf("%d%d",&n,&k)!=EOF){

    memset(first,-1,sizeof(first));edge=0;
    memset(son,false,sizeof(son));
    for(int i=1;i<n;i++)
        scanf("%d%d",&a,&b),add_edge(a,b),son[b]=1;
    int root;
    for(root=1;root<=n;root++)
        if(!son[root]) break;
    dfs(root);
    int num=0;
    for(int i=1;i<=n;i++)
        if(dp[i]==k+1) num++;
        printf("%d\n",num);
    }
    return 0;
}
