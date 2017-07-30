# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=maxn*20;
int n,m;
int first[maxn],nnext[maxm],v[maxm],edge=0;
int deg[maxn],belong[maxn],cnt;
int dev[maxn<<1];
bool vis[maxn<<1];
int to[maxm];
vector<int> G[maxn<<1];
bool used[maxm];

void add_edge(int a,int b){
    nnext[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void get(int x){
    vis[x]=1;belong[x]=cnt;
    for(int e=first[x];e!=-1;e=nnext[e]){
        if(deg[v[e]]!=2){
            vis[v[e]]=1;belong[v[e]]=cnt;
        }
    }
    return;
}
int S[maxn],top;

void Euler(int x){
   // printf("x:%d\n",x);
    for(int i=0;i<(int)G[x].size();i++){
        if(used[G[x][i]]) continue;
        used[G[x][i]]=used[G[x][i]^1]=1;
        Euler(to[G[x][i]]);
        S[top--]=x;
    }
    return;
}

vector<int> ans;

int main(){
    int a,b;
    scanf("%d%d",&n,&m);
    memset(first,-1,sizeof(first));
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);deg[a]++;deg[b]++;
    }
    memset(vis,0,sizeof(vis));cnt=n;
    for(int i=1;i<=n;i++) belong[i]=i;
    for(int i=1;i<=n;i++){
        if(deg[i]!=2&&!vis[i]) {cnt++;get(i);}
    }
    memset(dev,0,sizeof(dev));
    edge=0;top=0;
    for(int i=1;i<=n;i++){
        for(int e=first[i];e!=-1;e=nnext[e]){
            if(belong[i]<belong[v[e]])
                top++,
               // printf("connect %d %d\n",belong[i],belong[v[e]]),
                to[edge]=belong[v[e]],G[belong[i]].push_back(edge++),
                to[edge]=belong[i],G[belong[v[e]]].push_back(edge++),
                dev[belong[i]]++,dev[belong[v[e]]]++;
        }
    }top--;
   // for(int i=1;i<=n;i++) printf("belong[%d]:%d\n",i,belong[i]);
    for(int i=1;i<=cnt;i++)
        if(dev[i]&1){
            puts("-1");return 0;
        }
    int st;
    for(int i=1;i<=n;i++)
        if(deg[i]==2) {st=i;break;}
    memset(used,false,sizeof(used));
    int nn;
    nn=top;
    Euler(st);
    top=nn;S[++top]=S[0];
    //for(int i=0;i<=top;i++) printf("S[%d]:%d\n",i,S[i]);

    ans.push_back(S[0]);
    for(int i=1;i<=top;i++){
          //  printf("S[%d]:%d\n",i,S[i]);
        if(S[i]<=n) ans.push_back(S[i]);
        else{
            for(int e=first[S[i-1]];e!=-1;e=nnext[e])
                if(belong[v[e]]==S[i])
                    ans.push_back(v[e]);
            if(i<top)
                for(int e=first[S[i+1]];e!=-1;e=nnext[e])
                    if(belong[v[e]]==S[i]) ans.push_back(v[e]);
        }
    }
    printf("%d",st);
    for(int i=1;i<(int)ans.size()-1;i++)
        printf(" %d",ans[i]);
    puts("");
    return 0;
}
