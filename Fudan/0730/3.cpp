# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n;
bool vis[maxn];
bool isloop[maxn];
int to[maxn];
int size[maxn];
int cnt;
vector<int> loop;
int first[maxn],nnext[maxn<<1],v[maxn<<1],edge;
bool dp[maxn];

void add_edge(int a,int b){
    nnext[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void dp_size(int x,int fa){
    size[x]=1;
    for(int e=first[x];e!=-1;e=nnext[e]){
        if(isloop[v[e]]||v[e]==fa) continue;
        dp_size(v[e],x);size[x]+=size[v[e]];
    }
   // printf("size[%d]:%d\n",x,size[x]);
}

void dfs(int x,int fa){
    int son=1;
    for(int e=first[x];e!=-1;e=nnext[e]){
        if(v[e]==fa||isloop[v[e]]) continue;
        dfs(v[e],x);if(!dp[v[e]]) {dp[x]=0;return;}
        son+=size[v[e]]-size[v[e]]/cnt*cnt;
    }
    if(son<=cnt) dp[x]=1;
    else dp[x]=0;
    //printf("x:%d dp:%d\n",x,dp[x]);
    return;
}

int a[maxn<<1],m,right[maxn],suma[maxn<<1];
int S[maxn],top=-1;
int solve(int kuai){
    //printf("kuai:%d\n",kuai);
    bool luck=false;int pos,now,tt,last;
    cnt=kuai;
    memset(dp,false,sizeof(dp));
    for(int i=0;i<(int)loop.size();i++){
        dfs(loop[i],0);if(!dp[loop[i]]) return 0;
    }
    int sum=0;suma[0]=0;
    for(int i=1;i<=m;i++){
        a[i]=size[loop[i-1]]-size[loop[i-1]]/cnt*cnt;sum+=a[i];suma[i]=sum;
        if(a[i]==0&&(!luck)) {luck=1;pos=i+1;}
       // printf("a[%d]:%d\n",i,a[i]);
    }
    for(int i=m+1;i<=m+m;i++) a[i]=a[i-m],suma[i]=suma[i-1]+a[i];
    if(sum==0||sum==cnt) return 1;
    if(luck){
        //    puts("fuck");
        now=0;tt=0;
        while(tt<=m){
        tt++;
        if(pos>m) pos=1;
        now+=a[pos];
        if(a[pos]==0){
            if(now!=0&&now!=cnt) return 0;
        }
        if(now==cnt) now=0;
        else if(now>cnt) return 0;
        pos++;
        }
        return 1;
    }

    last=1;memset(vis,false,sizeof(vis));a[0]=0;
    for(int i=1;i<=m;i++){
        for(;suma[last]-suma[i-1]<cnt;) last++;
        if(suma[last]-suma[i-1]>cnt) vis[i]=1;
        else right[i]=last>m?last-m:last;
        //printf("right[%d]:%d\n",i,right[i]);
    }

    int x;
    for(int i=1;i<=m;i++){
        x=i;bool ok=0;top=-1;
        while(1){
            if(vis[x]) break;
            S[++top]=x;

            if(x==i) {ok=1;break;}
            x=right[x]+1;if(x>m) x=1;
        }
        if(ok) return 1;
        else{
            while(top>=0)
                vis[S[top]]=1,top--;
        }
    }
    return 0;
}

int main(){
    //freopen("input.txt","r",stdin);
    while(scanf("%d",&n)!=EOF){
        memset(first,-1,sizeof(first));edge=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&to[i]);add_edge(i,to[i]);add_edge(to[i],i);
        }
        int x=1;memset(vis,0,sizeof(vis));
        while(!vis[x]){
            vis[x]=1;x=to[x];
        }
        memset(vis,0,sizeof(vis));
        memset(isloop,false,sizeof(isloop));
        loop.clear();
        while(!vis[x]){
            isloop[x]=1;loop.push_back(x);//printf("loop:%d\n",x);
            vis[x]=1;x=to[x];
        }
        m=loop.size();
        for(int i=0;i<(int)loop.size();i++){
            dp_size(loop[i],0);
        }

        int ans=2;
        for(int kuai=2;kuai*kuai<=n;kuai++){
            if(n%kuai==0){
                ans+=solve(kuai);ans+=solve(n/kuai);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
