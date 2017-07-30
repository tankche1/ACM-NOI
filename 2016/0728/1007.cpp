# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=1000000000;
vector<int> G[maxn];
int n,m;
int L[maxn],R[maxn],fa[maxn],dep[maxn];
int dfs_clock;

struct SegmenTree{
    int s[maxn<<2],lazy[maxn<<2];

    void build(int o,int L,int R){
        lazy[o]=0;s[o]=0;
        if(L==R){
            return;
        }

        int M=(L+R)>>1;
        build(o<<1,L,M);
        build(o<<1|1,M+1,R);
    }

    void pushdown(int o){
        if(lazy[o]!=0){
            s[o<<1]+=lazy[o];s[o<<1|1]+=lazy[o];
            lazy[o<<1]+=lazy[o];lazy[o<<1|1]+=lazy[o];
            lazy[o]=0;
        }
    }

    void update(int o,int L,int R,int qL,int qR,int val){
        if(qL<=L&&qR>=R){
            s[o]+=val;lazy[o]+=val;return;
        }

        pushdown(o);
        int M=(L+R)>>1;
        if(qL<=M) update(o<<1,L,M,qL,qR,val);
        if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
        s[o]=max(s[o<<1],s[o<<1|1]);
    }


}seg;

void dfs(int x){
    L[x]=++dfs_clock;
   // printf("dep[%d]:%d\n",x,dep[x]);
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa[x]) continue;
        fa[G[x][e]]=x;dep[G[x][e]]=dep[x]+1;dfs(G[x][e]);
    }

    R[x]=dfs_clock;
}

int Step=17;
int dp[maxn][18];
void prepare(){
    for(int i=1;i<=n;i++) dp[i][0]=fa[i];
    for(int j=1;j<=Step;j++){
        for(int i=1;i<=n;i++)
            dp[i][j]=dp[dp[i][j-1]][j-1];
    }
}

int Lca(int u,int v){
    if(dep[u]>dep[v]) swap(u,v);
    int k=dep[v]-dep[u];
    for(int j=Step;j>=0;j--) if((k>>j)&1) v=dp[v][j];
    int j=Step;
    while(u!=v){
        while(j>0&&dp[u][j]==dp[v][j]) j--;
        u=dp[u][j];v=dp[v][j];
    }
    return u;
}

int get_lca(int u,int v){

    if(dep[u]>dep[v]) swap(u,v);
    //printf("u:%d v:%d dep[u]:%d dep[v]:%d\n",u,v,dep[u],dep[v]);

    for(int j=Step;j>=0;j--){
        if(dep[dp[v][j]]>dep[u]) v=dp[v][j];
    }
    //printf("get:%d\n",v);
    return v;
}

int x1[maxn<<2],x2[maxn<<2],y1[maxn<<2],y2[maxn<<2],w[maxn<<2],cnt;

void add(int _x1,int _x2,int _y1,int _y2,int c){
    //printf("%d %d %d %d %d\n",_x1,_x2,_y1,_y2,c);
    if(_y2<_y1||_x2<_x1) return;
    //printf("go %d %d %d %d %d\n",_x1,_x2,_y1,_y2,c);
    x1[cnt]=_x1;x2[cnt]=_x2;y1[cnt]=_y1;y2[cnt]=_y2;w[cnt]=c;cnt++;
}

struct Line{
    int l,r,y,w,op;
    Line() {}
    Line(int _l,int _r,int _y,int _w,int _op):l(_l),r(_r),y(_y),w(_w),op(_op) {}
}line[maxn<<3];

bool cmp(Line A,Line B){
    if(A.y!=B.y) return A.y<B.y;
    return A.op<B.op;
}

int ans;

void solve(){
    int nn=0;
    ans=-INF;

    for(int i=0;i<cnt;i++){
        line[nn++]=Line(x1[i],x2[i],y1[i],w[i],1);
        line[nn++]=Line(x1[i],x2[i],y2[i]+1,-w[i],-1);
        //printf("%d %d --- %d %d\n",y1[i],w[i],y2[i]+1,-w[i]);
    }

    sort(line,line+nn,cmp);

    seg.build(1,1,n);

    for(int i=0;i<nn;i++){
        int k=i;
        if(line[i].y>n) break;
        while(k+1<nn&&line[k+1].y==line[k].y) k++;
        for(int j=i;j<=k;j++){
            seg.update(1,1,n,line[j].l,line[j].r,line[j].w);
        }

        ans=max(ans,seg.s[1]);
       // printf("%d \n",seg.s[1]);
        i=k;
    }

    //printf("%d\n",ans);
    //if(ans==0) printf("n:%d m:%d\n",n,m);
}

int main(){
   // freopen("1007.in","r",stdin);
    //freopen("output.txt","w",stdout);
    int T,a,b,c,anc;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) G[i].clear();

        for(int i=1;i<n;i++){

            scanf("%d%d",&a,&b);
            //if(n==3&&m==3) printf("%d %d\n",a,b);
            G[a].push_back(b);
            G[b].push_back(a);
        }

        dfs_clock=0;
        fa[1]=1;dep[1]=1;dfs(1);
        prepare();

        cnt=0;
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&a,&b,&c);
            //if(n==3&&m==3) printf("%d %d %d\n",a,b,c);
            anc=Lca(a,b);
            if(a!=anc&&b!=anc){
                add(L[a],R[a],L[b],R[b],c);
                //x1[cnt]=L[a];x2[cnt]=R[a];y1[cnt]=L[b];y2[cnt]=R[b];
            }
            else if(a!=b&&b==anc){
                b=get_lca(a,b);
                add(L[a],R[a],1,L[b]-1,c);
                add(L[a],R[a],R[b]+1,n,c);
            }
            else if(a!=b&&a==anc){
                a=get_lca(a,b);
                add(1,L[a]-1,L[b],R[b],c);
                add(R[a]+1,n,L[b],R[b],c);
            }
            else if(a==b){
                add(1,n,1,n,c);
                for(int e=0;e<(int)G[a].size();e++){
                    if(G[a][e]!=fa[a]) add(L[G[a][e]],R[G[a][e]],L[G[a][e]],R[G[a][e]],-c);
                }
                if(a!=1){
                    add(1,L[a]-1,1,L[a]-1,-c);
                    add(1,L[a]-1,R[a]+1,n,-c);
                    add(R[a]+1,n,1,L[a]-1,-c);
                    add(R[a]+1,n,R[a]+1,n,-c);
                }
            }
        }

        solve();
        printf("Case #%d: ",Tcase);
        printf("%d\n",ans);
    }
    return 0;
}
