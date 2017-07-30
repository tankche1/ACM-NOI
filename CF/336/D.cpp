# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=200010;
typedef long long LL;
const int mod=1000000007;

struct Op{
    int type,p,v,nod;
    Op() {}
}op[maxn];
int v1,m,n;
vector<int> G[maxn];
int dfn[maxn],dfs_clock=0;
int L[maxn],R[maxn];
int fa[maxn];

void dfs(int x){
    dfn[x]=++dfs_clock;L[x]=dfn[x];//printf("x:%d\n",x);
    for(int e=0;e<(int)G[x].size();e++){
        fa[G[x][e]]=x;
        dfs(G[x][e]);
    }R[x]=dfs_clock;
}

LL fast_pow(LL a,LL b){
    if(b==0) return 1;
    LL half=fast_pow(a,b>>1);
    half=half*half%mod;
    if(b&1) half=half*a%mod;
    return half;
}

LL inv(LL x){
    return fast_pow(x,mod-2);
}

struct SegmenTree{
    LL sumv[maxn<<2],dmul[maxn<<2],vd[maxn<<2];
    LL lazydmul[maxn<<2];

    void build(int o,int L,int R){
        dmul[o]=1;sumv[o]=0;vd[o]=0;lazydmul[o]=1;
        if(L==R) return;
        int M=(L+R)>>1;
        build(o<<1,L,M);build(o<<1|1,M+1,R);
    }

    void pushdown(int o){
        if(lazydmul[o]!=1){
            LL d=lazydmul[o];
            lazydmul[o<<1]=lazydmul[o<<1]*d%mod;lazydmul[o<<1|1]=lazydmul[o<<1|1]*d%mod;
            dmul[o<<1]=dmul[o<<1]*d%mod;dmul[o<<1|1]=dmul[o<<1|1]*d%mod;
            vd[o<<1]=vd[o<<1]*d%mod;vd[o<<1|1]=vd[o<<1|1]*d%mod;
            lazydmul[o]=1;
        }
    }

    void updatev(int o,int L,int R,int pos,LL val){
        if(L==R){
            sumv[o]+=val;if(sumv[o]>=mod) sumv[o]-=mod;
            vd[o]=dmul[o]*sumv[o]%mod;
            return;
        }
        int M=(L+R)>>1;
        pushdown(o);
        if(pos<=M) updatev(o<<1,L,M,pos,val);
        else updatev(o<<1|1,M+1,R,pos,val);
        sumv[o]=sumv[o<<1]+sumv[o<<1|1];if(sumv[o]>=mod) sumv[o]-=mod;
        vd[o]=vd[o<<1]+vd[o<<1|1];if(vd[o]>=mod) vd[o]-=mod;
    }

    void updated(int o,int L,int R,int qL,int qR,LL val){
        if(qL<=L&&qR>=R){
            dmul[o]=dmul[o]*val%mod;
            vd[o]=(vd[o]*val)%mod;
            lazydmul[o]=lazydmul[o]*val%mod;
            return;
        }
        pushdown(o);
        int M=(L+R)>>1;
        if(qL<=M) updated(o<<1,L,M,qL,qR,val);
        if(qR>M) updated(o<<1|1,M+1,R,qL,qR,val);
        vd[o]=vd[o<<1]+vd[o<<1|1];if(vd[o]>=mod) vd[o]-=mod;
    }

    LL queryd(int o,int L,int R,int pos){
        if(L==R) return dmul[o];
        int M=(L+R)>>1;
        pushdown(o);
        if(pos<=M) return queryd(o<<1,L,M,pos);
        else return queryd(o<<1|1,M+1,R,pos);
    }

    LL queryvd(int o,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R) {
            return vd[o];
        }
        pushdown(o);
        int M=(L+R)>>1;
        LL ans=0;
        if(qL<=M) ans+=queryvd(o<<1,L,M,qL,qR);
        if(qR>M) ans+=queryvd(o<<1|1,M+1,R,qL,qR);
        if(ans>=mod) ans-=mod;
        return ans;
    }

}seg;

void changev(int pos,LL val){
    seg.updatev(1,1,n,dfn[pos],val);
}

LL d[maxn];

void changed(int pos){//*newd/d ==
    //printf("mul: %I64d d:%lld pos:%d \n",(d+1)*inv(d)%mod,d,pos);
    seg.updated(1,1,n,L[pos],R[pos],(d[pos]+1)*inv(d[pos])%mod);
    d[pos]++;
}

int main(){
    scanf("%d%d",&v1,&m);n=1;
    for(int i=1;i<=m;i++){
        scanf("%d",&op[i].type);
        if(op[i].type==1) scanf("%d%d",&op[i].p,&op[i].v),G[op[i].p].push_back(op[i].nod=++n);
        else scanf("%d",&op[i].p);
    }
    dfs(1);
    seg.build(1,1,n);
    changev(1,v1);
    //printf("%I64d\n",seg.queryvd(1,1,n,L[1],R[1]));
    for(int i=1;i<=n;i++) d[i]=1;

    for(int i=1;i<=m;i++){
        if(op[i].type==1){
            changev(op[i].nod,op[i].v);// printf("i:%d %I64d\n",i,seg.queryvd(1,1,n,L[1],R[1]));
            changed(op[i].p); //printf("i:%d %I64d\n",i,seg.queryvd(1,1,n,L[1],R[1]));
        }
        else{
            LL ans;
            if(op[i].p==1) ans=seg.queryvd(1,1,n,L[op[i].p],R[op[i].p]);
            else ans=seg.queryvd(1,1,n,L[op[i].p],R[op[i].p])*inv(seg.queryd(1,1,n,dfn[fa[op[i].p]]))%mod;
            printf("%I64d\n",ans);
        }

    }
    return 0;
}
