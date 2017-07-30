# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int mod=37;
unsigned long long hash1[maxn],hash2[maxn];
int n,m;
char w[maxn],s[maxn];
int first[maxn],nex[maxn<<1],edge=0,v[maxn<<1];
bool ok;

void add_edge(int a,int b){
    nex[edge]=first[a];v[edge]=b;first[a]=edge++;
}

int size[maxn],fa[maxn],dep[maxn];
bool face[maxn],back[maxn];
bool used[maxn];
void dfs_size(int x){
    size[x]=1;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]) continue;
        fa[v[e]]=x;dfs_size(v[e]);size[x]+=size[v[e]];
    }
}

int son[maxn],mx[maxn];
void choose(int &x){
    mx[x]=0;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]||used[v[e]]) continue;
        if(size[v[e]]>mx[x]){
            mx[x]=size[v[e]],son[x]=v[e];
        }
    }
    if(mx[x]>size[x]/2){
        size[x]-=size[son[x]];size[son[x]]+=size[x];fa[x]=son[x];fa[son[x]]=0;x=son[x];
        choose(x);
    }
}

void dfs(int x,unsigned long long has1,unsigned long long has2,unsigned long long tmp){
    //printf("dfsx:%d\n",x);
    has2=has2*mod+w[x]-'a';
    has1=has1+tmp*(w[x]-'a');tmp*=mod;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]||used[v[e]]) continue;
        dep[v[e]]=dep[x]+1;
        dfs(v[e],has1,has2,tmp);
    }
    face[x]=hash1[dep[x]+1]==has1;
    back[x]=hash2[dep[x]+1]==has2;
    //printf("face[%d]:%d back[%d]:%d\n",x,face[x],x,back[x]);
}
int have_face[maxn],have_back[maxn];
void check(int x){
    //printf("checkx:%d\n",x);
    if(face[x]&&have_back[m-(dep[x]+1)+1]) ok=true;
    if(back[x]&&have_face[m-(dep[x]+1)+1]) ok=true;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]||used[v[e]]) continue;
        check(v[e]);
    }
}

void join(int x,int sign){
    //printf("joinx:%d\n",x);
    if(face[x]) {have_face[dep[x]+1]+=sign;//printf("face:%d \n",dep[x]+1);
    }
    if(back[x]) {have_back[dep[x]+1]+=sign;//printf("back:%d \n",dep[x]+1);
    }
     for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]||used[v[e]]) continue;
        join(v[e],sign);
    }
}

void calc(int x){
    if(face[x]) have_face[1]=1;
    if(back[x]) have_back[1]=1;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(used[v[e]]) continue;
        check(v[e]);
        join(v[e],1);
    }
    if(face[x]) have_face[1]--;
    if(back[x]) have_back[1]--;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(used[v[e]]) continue;
        join(v[e],-1);
    }
}

void solve(int x){
    //printf("x:%d\n",x);
    choose(x);//printf("root:%d\n",x);
    dep[x]=0;dfs(x,0,0,1);
    calc(x);
    used[x]=1;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(used[v[e]]) continue;
        solve(v[e]);
    }
}

int main(){
    int tcase,a,b,tnum=0;
    scanf("%d",&tcase);
    while(tcase--){
        memset(first,-1,sizeof(first));edge=0;
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            add_edge(a,b);add_edge(b,a);
        }
        scanf("%s",w+1);
        scanf("%s",s+1);m=strlen(s+1);//printf("m:%d\n",m);
        hash1[0]=0;hash2[0]=0;
        for(int i=1;i<=m;i++){
            hash1[i]=hash1[i-1]*mod+s[i]-'a';
        }
        unsigned long long tmp=1;
        for(int i=m;i>=1;i--){
            hash2[m-i+1]=hash2[m-i]+(s[i]-'a')*tmp;
            tmp*=mod;
        }
        fa[1]=0;dfs_size(1);//puts("fuck");
        ok=false;memset(used,false,sizeof(used));
        solve(1);
        printf("Case #%d: ",++tnum);
        if(ok) puts("Find");
        else puts("Impossible");
    }
    return 0;
}
