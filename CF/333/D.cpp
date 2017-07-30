# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=300010;
int n;
int c[maxn];
int ch[maxn<<1][26],cnt=0;
vector<int> G[maxn];
char s[maxn];

int fa[maxn],size[maxn<<1];

int Merge(int u,int v){
    if(!u) return v;
    if(!v) return u;
    int t=++cnt;
    size[t]=1;
    for(int i=0;i<26;i++){
        ch[t][i]=Merge(ch[u][i],ch[v][i]);
        if(ch[t][i]!=0) size[t]+=size[ch[t][i]];
    }
    return t;
}

void dfs(int x){
    int v,lab;
    for(int i=0;i<26;i++) ch[x][i]=0;
    size[x]=1;
    for(int e=0;e<(int)G[x].size();e++){
        v=G[x][e];
        if(v==fa[x]) continue;
        fa[v]=x;
        dfs(v);
        lab=s[v]-'a';
        ch[x][lab]=Merge(ch[x][lab],v);
    }
    for(int i=0;i<26;i++) if(ch[x][i]!=0) size[x]+=size[ch[x][i]];
}

int main(){
    int a,b;
    scanf("%d",&n);cnt=n;
    for(int i=1;i<=n;i++)
        scanf("%d",&c[i]);
    scanf("%s",s+1);
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        G[a].push_back(b);G[b].push_back(a);
    }

    fa[1]=1;
    dfs(1);

    int ans=0,num=0;
    for(int i=1;i<=n;i++){
        if(size[i]+c[i]>ans) ans=size[i]+c[i],num=1;
        else if(size[i]+c[i]==ans) num++;
    }
    printf("%d\n%d\n",ans,num);
    return 0;
}
