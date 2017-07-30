# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
const int INF=(~0U>>1)-5;
int a[maxn],c[maxn];
int mmax;
struct SegmenTree{
    int maxv[maxn<<2],addv[maxn<<2];

    void maintain(int o){
        maxv[o]=max(maxv[o<<1],maxv[o<<1|1]);
    }

    void build(int o,int L,int R) {
        addv[o]=0;
        if(L==R) {maxv[o]=c[L];return;}
        int M=(L+R)>>1;
        build(o<<1,L,M);build(o<<1|1,M+1,R);
        maintain(o);
    }


    void pushdown(int o,int L,int R){
        int M=(L+R)>>1;
        if(addv[o]){
            addv[o<<1]+=addv[o];
            maxv[o<<1]+=addv[o];
            addv[o<<1|1]+=addv[o];
            maxv[o<<1|1]+=addv[o];
            addv[o]=0;
        }
    }

    void add(int o,int L,int R,int qL,int qR,int v){
        if(qL<=L&&qR>=R){
            addv[o]+=v;
            maxv[o]+=v;
            return;
        }
        int M=(L+R)>>1;
        pushdown(o,L,R);
        if(qL<=M) add(o<<1,L,M,qL,qR,v);
        if(qR>M) add(o<<1|1,M+1,R,qL,qR,v);
        maintain(o);
        return;
    }

    void query(int o,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R){
           mmax=max(mmax,maxv[o]);
            return;
        }
        int M=(L+R)>>1;
        pushdown(o,L,R);
        if(qL<=M) query(o<<1,L,M,qL,qR);
        if(qR>M) query(o<<1|1,M+1,R,qL,qR);
    }
}seg;

int sum[maxn];
int n,m,k;
int main(){
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d%d",&n,&m,&k);sum[0]=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
        for(int i=1;i<=n-k+1;i++){
            c[i]=sum[i+k-1]-sum[i-1];
        }
        n=n-k+1;
        seg.build(1,1,n);
        int op,x,y,L,R;
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&op,&x,&y);
            if(op==0){
                L=max(1,x-k+1);R=min(n,x);
                seg.add(1,1,n,L,R,y-a[x]);a[x]=y;
            }
            else if(op==1){
                L=max(1,x-k+1);R=min(n,x);
                seg.add(1,1,n,L,R,a[y]-a[x]);
                 L=max(1,y-k+1);R=min(n,y);
                seg.add(1,1,n,L,R,a[x]-a[y]);
                swap(a[x],a[y]);
            }
            else{
                L=x;R=y-k+1;
                mmax=-INF;seg.query(1,1,n,L,R);
                printf("%d\n",mmax);
            }
        }
    }
    return 0;
}
