# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n,q;
int a[maxn];

inline int gcd(int a,int b){
    if(a==0) return b;
    return gcd(b%a,a);
}

struct Seg{
    int pos,_gcd;
    Seg(){}
    Seg(int pos,int _gcd):pos(pos),_gcd(_gcd) {}
};

struct Query{
    int l,r,id;
    Query() {}
    Query(int l,int r,int id):l(l),r(r),id(id) {}
}query[maxn];

bool cmp(Query A,Query B){
    return A.l>B.l;
}
int ans[maxn];

vector<Seg> G[maxn];

void prepare(){
    G[n].clear();
    G[n].push_back(Seg(n,a[n]));
    for(int i=n-1;i>=1;i--){
        G[i].clear();
        G[i].push_back(Seg(i,a[i]));
        int now=a[i];
        for(int j=0;j<(int)G[i+1].size();j++){
            if(gcd(a[i],G[i+1][j]._gcd)!=now){
                now=gcd(a[i],G[i+1][j]._gcd);
                G[i].push_back(Seg(G[i+1][j].pos,now));
            }
        }
        //printf("i:%d ",i);
        //for(int j=0;j<G[i].size();j++) printf("(%d,%d) ",G[i][j].pos,G[i][j]._gcd);puts("");
    }
}

int val[1000010];

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    int C[maxn],n;
    void init(int nn) {n=nn;memset(C,0,sizeof(C));}

    void insert(int x,int v){
        while(x<=n){
            C[x]+=v;
            x+=lowbit(x);
        }
    }

    int sum(int x){
        int res=0;
        while(x>0){
            res+=C[x];x-=lowbit(x);
        }
        return res;
    }
}fwt;

int main(){
    while(scanf("%d%d",&n,&q)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        prepare();
        for(int i=1;i<=q;i++) {query[i].id=i;scanf("%d%d",&query[i].l,&query[i].r);}
        sort(query+1,query+q+1,cmp);

        fwt.init(n);for(int i=1;i<=1000000;i++)val[i]=-1;
        int now=1;
        for(int i=n;i>=1;i--){
                //printf("i:%d\n",i);
            for(int e=0;e<(int)G[i].size();e++){
                if(val[G[i][e]._gcd]==-1) fwt.insert(G[i][e].pos,1),val[G[i][e]._gcd]=G[i][e].pos;
                else if(G[i][e].pos<val[G[i][e]._gcd]) fwt.insert(val[G[i][e]._gcd],-1),fwt.insert(G[i][e].pos,1),val[G[i][e]._gcd]=G[i][e].pos;
            }
            while(query[now].l==i&&now<=q){
                ans[query[now].id]=fwt.sum(query[now].r);//-fwt.sum(query[now].l-1);
                now++;
            }
        }

        for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    }
    return 0;
}
