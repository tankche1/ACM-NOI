# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n;
int first[maxn],next[maxn<<1],v[maxn<<1],edge=0;

void add_edge(int a,int b){
    next[edge]=first[a];v[edge]=b;first[a]=edge++;
}

int fa[maxn],size[maxn];
int dp[maxn][18];
int Step=17;
int f[maxn][18];

void dfs(int x){
    size[x]=1;
    for(int e=first[x];e!=-1;e=next[e]){
        if(v[e]==fa[x]) continue;
        fa[v[e]]=x;
        dfs(v[e]);size[x]+=size[v[e]];
    }
    return;
}

void prepare(){
    for(int i=1;i<=n;i++) dp[i][0]=fa[i];
    for(int j=1;j<=Step;j++){
        for(int i=1;i<=n;i++){
            if(dp[i][j-1]==-1) {dp[i][j]=-1;continue;}
            dp[i][j]=dp[dp[i][j-1]][j-1];
            //if(j<=3) printf("dp[%d][%d]:%d\n",i,j,dp[i][j]);
        }
    }
}

int val[maxn];
long long ans=0;
int anc[20];

void dfs2(int x){
    for(int e=first[x];e!=-1;e=next[e]){
        if(v[e]==fa[x]) continue;
        dfs2(v[e]);
    }

    for(int j=0;j<=Step;j++){
        for(int k=0;k<j;k++){
            if(dp[x][k]==-1) break;
            f[dp[x][k]][k]+=f[x][j];
        }
        if(dp[x][j]!=-1) f[dp[x][j]][j]++;
        //if(f[x][j]>0) printf("f[%d][%d]:%d\n",x,j,f[x][j]);
    }

    anc[0]=x;
    for(int k=1;k<=Step;k++) anc[k]=1;
    for(int k=1;k<=Step;k++) {anc[k]=dp[anc[k-1]][k-1];if(anc[k]==-1) {anc[k]=1;break;}}

    int sum;
    for(int k=0;k<Step;k++){
        if(dp[x][k]==-1) break;
        sum=1;
        for(int j=k+1;j<=Step;j++)
            sum+=f[x][j];

        int ans1=ans;
        if(k==0) ans+=(long long)(size[fa[x]]-size[anc[k]])*sum;
        else ans+=(long long)(size[anc[k+1]]-size[anc[k]])*sum;
       //printf("x:%d k:%d : %d sum:%d %d\n",x,k,ans-ans1,sum,size[dp[x][k]]-size[anc[k]]);
    }
}

int main(){
    int a,b;
    scanf("%d",&n);
    memset(first,-1,sizeof(first));edge=0;
    for(int i=1;i<n;i++) {
        scanf("%d %d",&a,&b);
        add_edge(a,b);add_edge(b,a);
    }

    fa[1]=-1;
    dfs(1);
    prepare();
    dfs2(1);
    printf("%I64d\n",ans);
    return 0;
}
