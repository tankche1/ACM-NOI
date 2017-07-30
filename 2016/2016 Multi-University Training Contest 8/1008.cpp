# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int n,m;
int A[maxn];
LL ans=0;

struct SegmenTree{
    LL _min[maxn<<2],_max[maxn<<2],sum[maxn<<2],lazy[maxn<<2],_set[maxn<<2];

    void maintain(int o){
        _max[o]=max(_max[o<<1],_max[o<<1|1]);
        _min[o]=min(_min[o<<1],_min[o<<1|1]);
        sum[o]=sum[o<<1]+sum[o<<1|1];
    }

    void build(int o,int L,int R){
        lazy[o]=0;_set[o]=0;
        if(L==R){
            _min[o]=_max[o]=sum[o]=A[L];
            return;
        }

        int M=(L+R)>>1;
        build(o<<1,L,M);
        build(o<<1|1,M+1,R);
        maintain(o);
    }

    void pushdown(int o,int L,int R){
        int M=(L+R)>>1;
        if(_set[o]!=0){
            _set[o<<1]=_set[o<<1|1]=_set[o];
            lazy[o<<1]=lazy[o<<1|1]=0;
            sum[o<<1]=_set[o]*(M-L+1);sum[o<<1|1]=_set[o]*(R-M);
            _min[o<<1]=_max[o<<1]=_set[o];
            _min[o<<1|1]=_max[o<<1|1]=_set[o];
            _set[o]=0;
        }
        if(lazy[o]!=0){
            lazy[o<<1]+=lazy[o];lazy[o<<1|1]+=lazy[o];
            _min[o<<1]+=lazy[o];_max[o<<1]+=lazy[o];
            _min[o<<1|1]+=lazy[o];_max[o<<1|1]+=lazy[o];
            sum[o<<1]+=lazy[o]*(M-L+1);sum[o<<1|1]+=lazy[o]*(R-M);
            lazy[o]=0;
        }
        return;
    }

    void update(int o,int L,int R,int qL,int qR,int val){
        if(qL<=L&&qR>=R){
            _min[o]+=val;_max[o]+=val;lazy[o]+=val;sum[o]+=(LL)(R-L+1)*val;
            return;
        }
        pushdown(o,L,R);
        int M=(L+R)>>1;
        if(qL<=M) update(o<<1,L,M,qL,qR,val);
        if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
        maintain(o);
    }

    void update2(int o,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R&&_min[o]==_max[o]){
            int t=(int)sqrt(_min[o]);
            _min[o]=_max[o]=t;sum[o]=(LL)(R-L+1)*t;
            lazy[o]=0;_set[o]=t;
            return;
        }
        pushdown(o,L,R);
        int M=(L+R)>>1;
        if(qL<=M) update2(o<<1,L,M,qL,qR);
        if(qR>M) update2(o<<1|1,M+1,R,qL,qR);
        maintain(o);
    }

    void query(int o,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R){
            ans+=sum[o];return;
        }
        int M=(L+R)>>1;
        pushdown(o,L,R);
        if(qL<=M) query(o<<1,L,M,qL,qR);
        if(qR>M) query(o<<1|1,M+1,R,qL,qR);
    }

}seg;

int main(){
    int T;
    int op,l,r,x;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        seg.build(1,1,n);

        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&op,&l,&r);
            if(op==1){
                scanf("%d",&x);
                seg.update(1,1,n,l,r,x);
            }
            else if(op==2){
                seg.update2(1,1,n,l,r);
            }
            else{
                ans=0;
                seg.query(1,1,n,l,r);
                printf("%I64d\n",ans);
            }
        }
    }
    return 0;
}
