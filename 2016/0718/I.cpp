# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=1000100;
const int INF=10000010;

int n,m;
int a[maxn],b[maxn];
int fa[maxn],dfs_clock;
vector<int> G[maxn];
int L[maxn],R[maxn];

void dfs(int x){
    L[x]=++dfs_clock;
    for(int e=0;e<(int)G[x].size();e++){
        dfs(G[x][e]);
    }
    R[x]=dfs_clock;
}

struct SegmenTree{
    int _min[maxn<<2],_max[maxn<<2],lazy[maxn<<2];
    int mina,maxa;

    void build(int o,int L,int R){
        lazy[o]=0;
        if(L==R){
            _min[o]=_max[o]=b[L];return;
        }
        int M=(L+R)>>1;
        build(o<<1,L,M);
        build(o<<1|1,M+1,R);
        _min[o]=min(_min[o<<1],_min[o<<1|1]);
        _max[o]=max(_max[o<<1],_max[o<<1|1]);
    }

    void pushdown(int o){
        if(lazy[o]!=0){
            _min[o<<1]+=lazy[o];_max[o<<1]+=lazy[o];
            _min[o<<1|1]+=lazy[o];_max[o<<1|1]+=lazy[o];
            lazy[o<<1]+=lazy[o];lazy[o<<1|1]+=lazy[o];
            lazy[o]=0;
        }
    }

    void update(int o,int L,int R,int qL,int qR,int val){
        if(qL<=L&&qR>=R){
            lazy[o]+=val;_min[o]+=val;_max[o]+=val;return;
        }
        pushdown(o);

        int M=(L+R)>>1;
        if(qL<=M) update(o<<1,L,M,qL,qR,val);
        if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
        _min[o]=min(_min[o<<1],_min[o<<1|1]);
        _max[o]=max(_max[o<<1],_max[o<<1|1]);
    }

    void query(int o,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R){
            mina=min(mina,_min[o]);
            maxa=max(maxa,_max[o]);
            return;
        }
        pushdown(o);

        int M=(L+R)>>1;
        if(qL<=M) query(o<<1,L,M,qL,qR);
        if(qR>M) query(o<<1|1,M+1,R,qL,qR);
    }

}seg;

int main(){
    //freopen("input.txt","r",stdin)
    int T;
    char op;
    int x,val;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=2;i<=n;i++){
            scanf("%d",&fa[i]);G[fa[i]].push_back(i);
        }

        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }

        dfs_clock=0;
        dfs(1);

        for(int i=1;i<=n;i++) b[L[i]]=a[i];

        seg.build(1,1,n);

        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            while((op=getchar())&&op!='R'&&op!='Q');
            if(op=='R'){
                scanf("%d%d",&x,&val);seg.update(1,1,n,L[x],R[x],val);
            }
            else{
                scanf("%d",&x);seg.mina=INF,seg.maxa=-INF;seg.query(1,1,n,L[x],R[x]);
                printf("%d\n",seg.maxa-seg.mina);
            }
        }

    }
    return 0;
}
