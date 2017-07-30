# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=~0U>>1;
vector<int> G[maxn];

struct Node{
    int _min,_max,lazy;
    unsigned int sum;
    int ls,rs;
    Node() {}
}seq[maxn*20];
int node[maxn];
int seq_cnt=0;
int n,Q;

int fa[maxn],dep[maxn],L[maxn],R[maxn],w[maxn];
int dfs_clock;

void dfs(int x){
    L[x]=++dfs_clock;
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa[x]) continue;
        fa[G[x][e]]=x;dep[G[x][e]]=dep[x]+1;
        dfs(G[x][e]);
    }
    R[x]=dfs_clock;
    //printf("x:%d L:%d R:%d\n",x,L[x],R[x]);
}

void maintain(int u,int sz){
    seq[u].sum=seq[seq[u].ls].sum+seq[seq[u].rs].sum+(unsigned int)sz*seq[u].lazy;
    seq[u]._max=max(seq[seq[u].ls]._max,seq[seq[u].rs]._max)+seq[u].lazy;
    seq[u]._min=min(seq[seq[u].ls]._min,seq[seq[u].rs]._min)+seq[u].lazy;
}

void build(int &u,int L,int R){
    u=seq_cnt++;seq[u].lazy=0;
    if(L==R){
        seq[u]._min=seq[u]._max=seq[u].sum=w[L];//seq[u].lazy=0;
        return;
    }

    int M=(L+R)>>1;
    build(seq[u].ls,L,M);
    build(seq[u].rs,M+1,R);

    maintain(u,R-L+1);
    //printf("L:%d R:%d sum:%u big:%d small:%d\n",L,R,seq[u].sum,seq[u]._max,seq[u]._min);
}

void modify(int &u,int L,int R,int qL,int qR,int val){
    int v=u;u=seq_cnt++;

    seq[u]._min=seq[v]._min;
    seq[u]._max=seq[v]._max;
    seq[u].sum=seq[v].sum;
    seq[u].lazy=seq[v].lazy;
    seq[u].ls=seq[v].ls;
    seq[u].rs=seq[v].rs;

    if(qL<=L&&qR>=R){
        seq[u].lazy+=val;
        seq[u]._min+=val;
        seq[u]._max+=val;
        seq[u].sum+=val*(R-L+1);
        //printf("L:%d R:%d sum:%u big:%d small:%d\n",L,R,seq[u].sum,seq[u]._max,seq[u]._min);

        return;
    }

    int M=(L+R)>>1;
    if(qL<=M) modify(seq[u].ls,L,M,qL,qR,val);
    if(qR>M) modify(seq[u].rs,M+1,R,qL,qR,val);

    maintain(u,R-L+1);
    //printf("L:%d R:%d sum:%u big:%d small:%d\n",L,R,seq[u].sum,seq[u]._max,seq[u]._min);
}

unsigned int Sum;
int Big,Small;

void Query(int u,int L,int R,int qL,int qR,int lazy){
    if(qL<=L&&qR>=R){
        Sum+=(R-L+1)*lazy+seq[u].sum;
        Big=max(Big,seq[u]._max+lazy);
        Small=min(Small,seq[u]._min+lazy);
        return;
    }

    int M=(L+R)>>1;
    if(qL<=M) Query(seq[u].ls,L,M,qL,qR,lazy+seq[u].lazy);
    if(qR>M) Query(seq[u].rs,M+1,R,qL,qR,lazy+seq[u].lazy);
}

void dfs2(int x){
    for(int e=0;e<(int)G[x].size();e++){
        if(fa[x]==G[x][e]) continue;
        node[L[G[x][e]]]=node[L[x]];
       // printf("node:%d\n",G[x][e]);
        modify(node[L[G[x][e]]],1,n,1,n,1);
        modify(node[L[G[x][e]]],1,n,L[G[x][e]],R[G[x][e]],-2);
        dfs2(G[x][e]);
    }
}

struct Tank{
    int l,r;
    Tank() {}
    Tank(int _l,int _r):l(_l),r(_r) {}
}tank[maxn],T[maxn];

bool cmp(Tank A,Tank B){
    return A.l<B.l;
}

int main(){
    //freopen("1005.in","r",stdin);
    //freopen("output.txt","w",stdout);
    int a,b;
    while(scanf("%d%d",&n,&Q)!=EOF){
        seq_cnt=0;
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            G[a].push_back(b);G[b].push_back(a);
        }

        fa[1]=1;dep[1]=0;dfs_clock=0;
        dfs(1);

        for(int i=1;i<=n;i++) w[L[i]]=dep[i];

        //printf("node:1\n");
        build(node[L[1]],1,n);


        dfs2(1);
        for(int i=1;i<=n;i++){
            Sum=0;Big=0;Small=INF;
            Query(node[L[1]],1,n,L[i],L[i],0);

            //printf("i:%d node:(%d,%d) %u %d %d\n",1,L[i],L[i],Sum,Big,Small);
        }

        for(int i=1;i<=n;i++){
            Sum=0;Big=0;Small=INF;
            Query(node[L[8]],1,n,L[i],L[i],0);

            //printf("i:%d node:(%d,%d) %u %d %d\n",8,L[i],L[i],Sum,Big,Small);
        }

        for(int i=1;i<=n;i++){
            Sum=0;Big=0;Small=INF;
            Query(node[L[2]],1,n,L[i],L[i],0);

            //printf("i:%d node:(%d,%d) %u %d %d\n",2,L[i],L[i],Sum,Big,Small);
        }

        unsigned int lastans=0;
        int K,P,TT,now;
        for(int t=1;t<=Q;t++){
            scanf("%d%d%d",&K,&P,&TT);
            P=(P+lastans)%n+1;

            if(K==0){
                T[now=1]=Tank(1,n);
                goto Loop;
            }

            for(int i=1;i<=K;i++){
                scanf("%d",&a);
                tank[i].l=L[a];tank[i].r=R[a];
            }
            sort(tank+1,tank+K+1,cmp);
            tank[now=1]=tank[1];

            for(int i=2;i<=K;i++){
                if(tank[i].l<=tank[now].r+1) tank[now].r=max(tank[now].r,tank[i].r);
                else tank[++now]=tank[i];
            }

            K=now;now=0;
            if(tank[1].l>1) T[++now]=Tank(1,tank[1].l-1);
            for(int i=1;i<K;i++) T[++now]=Tank(tank[i].r+1,tank[i+1].l-1);
            if(tank[K].r<n) T[++now]=Tank(tank[K].r+1,n);

            if(now==0) {lastans=0;puts("-1");continue;}

            Loop:

            /*puts("**********");
            for(int i=1;i<=now;i++) printf("%d %d\n",T[i].l,T[i].r);
            puts("%%%%%%%%%%%%%%");*/

            Sum=0;Big=0;Small=INF;
            for(int i=1;i<=now;i++) Query(node[L[P]],1,n,T[i].l,T[i].r,0);

            if(TT==1){
                lastans=Sum;
            }
            else if(TT==2){
                lastans=Small;
            }
            else lastans=Big;

            printf("%d\n",lastans);
        }
    }
    return 0;
}
