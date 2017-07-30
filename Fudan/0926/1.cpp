# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n;
int num[100010];
int pre[maxn][70];
int first[maxn],nex[maxn<<1],edge=0,v[maxn<<1];
int p[maxn][70],w[maxn],np[maxn];
int sign[maxn][70];
int prime[10010],prime_cnt=0;
int size[maxn],ans[maxn];
bool vis[maxn];

void prepare(){
    for(int i=2;i<=10000;i++){
        if(!vis[i]){
            prime[++prime_cnt]=i;
            for(int j=i;j<=10000;j+=i)
                vis[j]=1;
        }
    }
    //printf("prime_cnt:%d\n",prime_cnt);
}

void add_edge(int a,int b){
    nex[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void get_prime(int x){
    int t=w[x],tmp;
    np[x]=0;
    for(int i=1;prime[i]*prime[i]<=t;i++){
        if(t%prime[i]==0){
            p[x][++np[x]]=prime[i];sign[x][np[x]]=-1;
            while(t%prime[i]==0) t/=prime[i];
            //if(t==1) break;
        }
    }
    if(t>1) p[x][++np[x]]=t;sign[x][np[x]]=-1;
    p[x][0]=np[x];
    for(int i=1;i<(1<<np[x]);i++){

        t=1;tmp=0;
        for(int j=1;j<=np[x];j++){
            if((i>>(j-1))&1){
                t*=p[x][j];tmp++;
            }
        }
        if(tmp>1){++p[x][0]; p[x][p[x][0]]=t;sign[x][p[x][0]]=((tmp&1)==1)?-1:1;}

    }
}

void dfs(int x,int fa){
    get_prime(x);size[x]=1;
    for(int i=1;i<=p[x][0];i++)
        pre[x][i]=num[p[x][i]];
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa) continue;
        dfs(v[e],x);size[x]+=size[v[e]];
    }
    ans[x]=size[x]-1;if(w[x]==1) ans[x]++;
    //printf("x:%d \n",x);
    for(int i=1;i<=p[x][0];i++){
           // printf("%d num:%d pre:%d sign:%d\n",p[x][i],num[p[x][i]],pre[x][i],sign[x][i]);
        ans[x]+=sign[x][i]*(num[p[x][i]]-pre[x][i]);
    }//puts("");
    for(int i=1;i<=p[x][0];i++)
        num[p[x][i]]++;
}

int main(){
    int a,b,tnum=0;
    prepare();
    while(scanf("%d",&n)!=EOF){
        memset(first,-1,sizeof(first));edge=0;
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            add_edge(a,b);add_edge(b,a);
        }
        for(int i=1;i<=n;i++) scanf("%d",&w[i]);
        dfs(1,0);
        printf("Case #%d:",++tnum);
        for(int i=1;i<=n;i++)
            printf(" %d",ans[i]);
        puts("");
    }
    return 0;
}
