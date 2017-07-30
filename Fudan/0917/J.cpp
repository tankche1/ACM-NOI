# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=(~0U>>1)-1000000;
struct Mart{
    int dis,bh;
    Mart(){}
    bool operator <(const Mart &rhs) const{
        return (dis==rhs.dis)?(bh<rhs.bh):(dis<rhs.dis);
    }
};
Mart mart[maxn];
Mart tmp;
bool ismart[maxn];
int dis[maxn],size[maxn],fa[maxn];
int n;
int first[maxn],nex[maxn<<1],v[maxn<<1],w[maxn<<1],edge;

void add_edge(int a,int b,int c){
    nex[edge]=first[a];v[edge]=b;w[edge]=c;first[a]=edge++;
}

int que[maxn];
bool vis[maxn];
void add(int &x){x++;if(x==maxn) x=0;}
void spfa(){
    memset(vis,false,sizeof(vis));
    int front=0,rear=0,x;
    for(int i=1;i<=n;i++){
        if(ismart[i]) mart[i].dis=0,mart[i].bh=i,que[rear++]=i;
        else mart[i].dis=INF,mart[i].bh=n+1;
    }
    while(front!=rear){
        x=que[front];add(front);
        vis[x]=0;
        for(int e=first[x];e!=-1;e=nex[e]){
            tmp.dis=mart[x].dis+w[e],tmp.bh=mart[x].bh;
            if(tmp<mart[v[e]]){
                mart[v[e]]=tmp;if(!vis[v[e]]) vis[v[e]]=1,que[rear]=v[e],add(rear);
            }
        }
    }
}

void getsize(int x){
    size[x]=1;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(fa[x]==v[e]) continue;
        fa[v[e]]=x;getsize(v[e]);size[x]+=size[v[e]];
    }
}

int tot_size;
bool used[maxn];
void choose(int &x){
    int mx=0,son;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(!used[v[e]]&&size[v[e]]>mx){
            son=v[e];mx=size[v[e]];
        }
    }
    if(mx>tot_size/2){
        fa[x]=son;fa[son]=0;size[x]-=size[son];size[son]+=size[x];
        x=son;choose(x);
    }
}

Mart q[maxn];
int len,point[maxn];
void get_dis(int x){
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]||used[v[e]]) continue;
        dis[v[e]]=dis[x]+w[e];
        get_dis(v[e]);
    }
}

void push(int x){
    for(int e=first[x];e!=-1;e=nex[e]){
        if(v[e]==fa[x]||used[v[e]]) continue;
        push(v[e]);
    }
    q[len].dis=mart[x].dis-dis[x];point[len]=x;q[len].bh=mart[x].bh;len++;
}
int ans[maxn];

int get(Mart tmp){
    int t=lower_bound(q,q+len,tmp)-q;
    return len-t;
}

void get_ans(int x,int sign){
    int u;
    len=0;push(x);
    sort(q,q+len);
    for(int i=0;i<len;i++){
        u=point[i];
        tmp.dis=dis[u],tmp.bh=u;
        ans[u]+=sign*get(tmp);
    }
}

void solve(int x){
    tot_size=size[x];
    choose(x);
    dis[x]=0;get_dis(x);
    get_ans(x,1);
    for(int e=first[x];e!=-1;e=nex[e]){
        if(!used[v[e]]){
            get_ans(v[e],-1);
        }
    }
    used[x]=1;
    for(int e=first[x];e!=-1;e=nex[e]){
        if(!used[v[e]]) solve(v[e]);
    }
}

int main(){
    int a,b,c;
    int print,tt;
    while(scanf("%d",&n)!=EOF){
        memset(first,-1,sizeof(first));edge=0;
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&a,&b,&c);
            add_edge(a,b,c);add_edge(b,a,c);
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&ismart[i]);
        spfa();
        fa[1]=0;getsize(1);

        memset(ans,0,sizeof(ans));memset(used,false,sizeof(used));
        solve(1);
        print=0;
        for(int i=1;i<=n;i++){
            if((!ismart[i])&&ans[i]>print) print=ans[i],tt=i;
        }
        printf("%d\n",print);
    }
    return 0;
}
