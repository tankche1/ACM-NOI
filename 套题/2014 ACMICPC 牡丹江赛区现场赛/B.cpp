# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
int T,n;

int first[maxn],next[maxn<<1],v[maxn<<1],edge=0;

void add_edge(int a,int b){
    next[edge]=first[a];v[edge]=b;first[a]=edge++;
}

int dep[maxn],fa[maxn];
bool vis[maxn];

int maxd,pos;
int ans1,ans2;
int q[maxn],front,rear;
int d[maxn];

void dfs(int root){
    int x;
    front=rear=0;q[0]=root;
    for(int i=1;i<=n;i++) dep[i]=-1;
    dep[root]=1;fa[root]=root;
    while(front<=rear){
        x=q[front++];
        for(int e=first[x];e!=-1;e=next[e]){
            if(dep[v[e]]==-1){
                dep[v[e]]=dep[x]+1;fa[v[e]]=x;
                q[++rear]=v[e];
            }
        }
    }
}

void bfs(int root,int dis){
    int x;
    front=rear=0;q[0]=root;vis[root]=1;
    for(int i=1;i<=n;i++) d[i]=-1;
    d[root]=0;
    while(front<=rear){
        x=q[front++];
        if(d[x]==dis) break;
        for(int e=first[x];e!=-1;e=next[e]){
            if(d[v[e]]==-1){
                vis[v[e]]=1;
                d[v[e]]=d[x]+1;
                q[++rear]=v[e];
            }
        }
    }
}

bool check(int dis){
    //printf("dis:%d\n",dis);
    int p1=pos,p2,tmp;
    for(int i=1;i<=dis;i++)
        p1=fa[p1];
    for(int i=1;i<=n;i++) vis[i]=0;
    bfs(p1,dis);

    tmp=0;p2=p1==1?2:1;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            if(dep[i]>tmp) tmp=dep[i],p2=i;
        }
    }
    if(tmp==0) {ans1=p1;ans2=p2;return true;}
    for(int i=1;i<=dis;i++)
        p2=fa[p2];
    //printf("p1:%d p2:%d\n",p1,p2);
    bfs(p2,dis);
    for(int i=1;i<=n;i++){
        if(!vis[i]) {return false;}
    }
    //printf("p1:%d p2:%d\n",p1,p2);
    ans1=p1;ans2=p2;return true;
}

int main(){
    int a,b;
    int L,R,M;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) first[i]=-1;edge=0;
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);
        }
        dfs(1);//puts("fuck");
        maxd=0;pos=-1;
        for(int i=1;i<=n;i++) if(dep[i]>maxd) maxd=dep[i],pos=i;
        L=0,R=n;
        while(L<=R){
            M=(L+R)>>1;
            if(check(M)) R=M-1;
            else L=M+1;
        }
        printf("%d %d %d\n",R+1,ans1,ans2);
    }
    return 0;
}
