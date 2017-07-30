# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
LL INF=(LL)1000000010*maxn;
int a[maxn],n,m;
struct node{
    LL oddodd,oddeven,evenodd,eveneven;
    node(){}
    node(LL oddodd,LL oddeven,LL evenodd,LL eveneven):oddodd(oddodd),oddeven(oddeven),evenodd(evenodd),eveneven(eveneven) {}
};
node res;

struct SegmenTree{
    node t[maxn<<2];

    node maintain(node a,node b){
        node ret;
        ret.oddodd=max(a.oddodd,b.oddodd);
        ret.oddodd=max(ret.oddodd,a.oddodd+b.evenodd);
        ret.oddodd=max(ret.oddodd,a.oddeven+b.oddodd);

        ret.oddeven=max(a.oddeven,b.oddeven);
        ret.oddeven=max(ret.oddeven,a.oddodd+b.eveneven);
        ret.oddeven=max(ret.oddeven,a.oddeven+b.oddeven);

        ret.evenodd=max(a.evenodd,b.evenodd);
        ret.evenodd=max(ret.evenodd,a.evenodd+b.evenodd);
        ret.evenodd=max(ret.evenodd,a.eveneven+b.oddodd);

        ret.eveneven=max(a.eveneven,b.eveneven);
        ret.eveneven=max(ret.eveneven,a.evenodd+b.eveneven);
        ret.eveneven=max(ret.eveneven,a.eveneven+b.oddeven);
       // printf("ret:%I64d %I64d %I64d %I64d \n",ret.oddodd,ret.oddeven,ret.evenodd,ret.eveneven);
        return ret;
    }

    void build(int o,int L,int R){
        if(L==R){
            if(L&1) t[o]=node(a[L],-INF,-INF,-INF);
            else t[o]=node(-INF,-INF,-INF,a[L]);
            return;
        }
        int M=(L+R)>>1;
        build(o<<1,L,M);build(o<<1|1,M+1,R);
        t[o]=maintain(t[o<<1],t[o<<1|1]);
    }

    void update(int o,int L,int R,int pos){
        if(L==R){
            if(L&1) t[o]=node(a[L],-INF,-INF,-INF);
            else t[o]=node(-INF,-INF,-INF,a[L]);
            return;
        }
        int M=(L+R)>>1;
        if(pos<=M) update(o<<1,L,M,pos);
        else update(o<<1|1,M+1,R,pos);
        t[o]=maintain(t[o<<1],t[o<<1|1]);
    }

    void query(int o,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R){
            //printf("ttres:%I64d %I64d %I64d %I64d \n",res.oddodd,res.oddeven,res.evenodd,res.eveneven);
            res=maintain(res,t[o]);
           // printf("res:%I64d %I64d %I64d %I64d \n",res.oddodd,res.oddeven,res.evenodd,res.eveneven);
            return;
        }
        int M=(L+R)>>1;
        if(qL<=M) query(o<<1,L,M,qL,qR);
        if(qR>M) query(o<<1|1,M+1,R,qL,qR);
        return;
    }
}seg;

int main(){
    //printf("%I64d\n",-INF);
    LL ans;
    int tcase;
    int type,c,d;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        seg.build(1,1,n);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&type,&c,&d);
            if(type==0){
                res=node(-INF,-INF,-INF,-INF);
                //printf("%I64d %I64d %I64d %I64d \n",res.oddodd,res.oddeven,res.evenodd,res.eveneven);
                seg.query(1,1,n,c,d);//printf("c:%d d:%d\n",c,d);
                //printf("%I64d %I64d %I64d %I64d \n",res.oddodd,res.oddeven,res.evenodd,res.eveneven);
                ans=max(max(res.oddodd,res.oddeven),max(res.evenodd,res.eveneven));
                printf("%I64d\n",ans);
            }
            else{
                a[c]=d;
                seg.update(1,1,n,c);
            }
        }
    }
    return 0;
}
