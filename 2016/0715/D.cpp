# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=510;
const int maxm=510*510;
int n,m;
int ans;
int cnt[maxn],fg[maxn];
vector<int> G[maxn];

void prepare(){
    int v;
    for(int i=1;i<=n;i++){
        cnt[i]=fg[i]=0;
        for(int j=0;j<(int)G[i].size();j++){
            v=G[i][j];
            if(v<=30){
                fg[i]|=(1<<(v-1));
            }
            else cnt[i]++;
        }
        //printf("fg[%d]:%d\n",i,fg[i]);
    }
}

int calc(int st){
    int res=0;
    for(int i=31;i<=n;i++){
        if((st&fg[i])!=fg[i]) res++;
    }
    return res;
}

void dfs(int x,int st,int res){
   // printf("x:%d st:%d res:%d\n",x,st,res);
    if(x>30) {ans=min(ans,res+calc(st));return;}

    //×îÓÅ»¯¼ô
    int st2=st;
    for(int i=x;i<=30;i++) st2=st2|(1<<(i-1));
    if(res+calc(st2)>=ans) return;

    if(((fg[x]&st)==fg[x])&&(!cnt[x])){
        dfs(x+1,st,res);return;
    }

    if(((fg[x]&((1<<x)-1))&st)==(fg[x]&((1<<x)-1))) dfs(x+1,st,res);
    dfs(x+1,st|(1<<(x-1)),res+1);
}

int main(){
    //freopen("input.txt","r",stdin);
    int a,b;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++) G[i].clear();
        ans=min(n,30);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&a,&b);
            G[a].push_back(b);G[b].push_back(a);
        }

        prepare();
        dfs(1,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
