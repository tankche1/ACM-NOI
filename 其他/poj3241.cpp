# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int INF=100000000;
int n,k;

struct point{
    int x,y,bh;
    int jian,jia;
    point() {}
}init[maxn],p[maxn];

struct Node{
    int minval,bh;
    bool operator < (const Node &rhs){
        return minval<rhs.minval;
    }
};

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    int n;
    Node C[maxn];
    void init(int nn){
        n=nn;
        for(int i=1;i<=nn;i++) C[i].minval=INF,C[i].bh=-1;
    }

    void insert(int x,Node v){
        while(x<=n){
            if(v<C[x]) C[x]=v;
            x+=lowbit(x);
        }
    }

    Node query(int x){
        Node res;res.minval=INF;res.bh=-1;
        while(x>0){
            if(C[x]<res) res=C[x];
            x-=lowbit(x);
        }
        return res;
    }
}fwt;

bool cmp(point A,point B){
    if(A.x==B.x)
        return A.jian>B.jian;
    return A.x<B.x;
}

int _jian[maxn],cnt;

int u[maxn<<2],v[maxn<<2],w[maxn<<2],edge=0;

void add_edge(int a,int b){
    edge++;
    u[edge]=a;v[edge]=b;w[edge]=abs(init[a].x-init[b].x)+abs(init[a].y-init[b].y);
    //printf("a:%d b:%d w:%d\n",a,b,w[edge]);
}

int bh[maxn<<2],fa[maxn];

int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}

bool cmp2(int a,int b){
    return w[a]<w[b];
}
void Kruskal(){
    int px,py,x,y;
    for(int i=1;i<=edge;i++) bh[i]=i;
    sort(bh+1,bh+edge+1,cmp2);
    for(int i=1;i<=n;i++) fa[i]=i;

    int cnt=0;
    for(int i=1;i<=edge;i++){
        x=u[bh[i]],y=v[bh[i]];
        px=find(x);py=find(y);
        if(px!=py){
            cnt++;
            if(cnt==n-1-k+1){
                printf("%d\n",w[bh[i]]);return;
            }
            fa[px]=py;
        }
    }
}

void Add(){
    Node x;
    for(int i=1;i<=n;i++)
        p[i].jia=p[i].x+p[i].y,p[i].jian=p[i].x-p[i].y,_jian[i]=p[i].jian;
    sort(p+1,p+n+1,cmp);

    sort(_jian+1,_jian+n+1);
    cnt=unique(_jian+1,_jian+n+1)-_jian-1;

    for(int i=1;i<=n;i++) p[i].jian=lower_bound(_jian+1,_jian+cnt+1,p[i].jian)-_jian;
    fwt.init(cnt);
    /*for(int i=1;i<=n;i++){
        printf("x:%d y:%d jia:%d jian:%d\n",p[i].x,p[i].y,p[i].jia,p[i].jian);
    }*/
    for(int i=n;i>=1;i--){
        x=fwt.query(p[i].jian);
        if(x.bh!=-1){
            add_edge(p[i].bh,p[x.bh].bh);
        }
        x.minval=p[i].jia,x.bh=i;
        fwt.insert(p[i].jian,x);
    }
}

int main(){

    while(scanf("%d%d",&n,&k)!=EOF){
    for(int i=1;i<=n;i++)
        scanf("%d%d",&init[i].x,&init[i].y),init[i].bh=i;

    for(int i=1;i<=n;i++) p[i]=init[i];
    Add();
    for(int i=1;i<=n;i++) p[i]=init[i],swap(p[i].x,p[i].y);
    Add();
    for(int i=1;i<=n;i++) p[i]=init[i],p[i].x=-p[i].x;
    Add();
    for(int i=1;i<=n;i++) p[i]=init[i],p[i].x=-p[i].x,swap(p[i].x,p[i].y);
    Add();

    Kruskal();
}
    return 0;
}
