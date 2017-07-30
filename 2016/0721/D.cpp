# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
const int Step=20;
int mod=1000000007;
int n,m,A,B;

int a,b,C=~(1<<31),MM=(1<<16)-1;
int pa[maxn],pb[maxn];

int rnd(int last){
    a = (36969 + (last >> 3)) * (a & MM) + (a >> 16);
    b = (18000 + (last >> 3)) * (b & MM) + (b >> 16);
    return (C & ((a << 16) + b)) % 1000000000;
}

struct SegmenTree{
    int s[maxn<<2],w[Step][maxn],lnum[Step][maxn];
    bool mark[maxn<<2];
    int res;

    void build(int o,int dep,int L,int R){
        mark[o]=0;
        if(L==R){
            w[dep][L]=pb[L];lnum[dep][L]=0;
            s[o]=(pa[L]>=pb[L]);
            return;
        }

        int M=(L+R)>>1;
        build(o<<1,dep+1,L,M);
        build(o<<1|1,dep+1,M+1,R);
        s[o]=s[o<<1]+s[o<<1|1];

        int ql=L,qr=M+1,q=L;
        while(q<=R){
            lnum[dep][q]=q==L?0:lnum[dep][q-1];
            if(ql>M){
                w[dep][q++]=w[dep+1][qr++];
            }
            else if(qr>R){
                lnum[dep][q]++;w[dep][q++]=w[dep+1][ql++];
            }
            else if(w[dep+1][ql]<=w[dep+1][qr]){
                lnum[dep][q]++;w[dep][q++]=w[dep+1][ql++];
            }
            else{
                w[dep][q++]=w[dep+1][qr++];
            }
        }

    }

    void pushdown(int o,int L,int dep){
        if(mark[o]){
            mark[o]=0;
            s[o<<1]=s[o]==0?0:lnum[dep][L+s[o]-1];mark[o<<1]=1;
            s[o<<1|1]=s[o]==0?0:(s[o]-lnum[dep][L+s[o]-1]);mark[o<<1|1]=1;
        }
    }

    void change(int o,int dep,int L,int R,int qL,int qR,int x){
        if(qL<=L&&qR>=R){
            mark[o]=1;s[o]=x;return;
        }

        pushdown(o,L,dep);
        int M=(L+R)>>1;
        if(qL<=M) change(o<<1,dep+1,L,M,qL,qR,x==0?0:lnum[dep][L+x-1]);
        if(qR>M) change(o<<1|1,dep+1,M+1,R,qL,qR,x==0?0:(x-lnum[dep][L+x-1]));
        s[o]=s[o<<1]+s[o<<1|1];
    }

    void Change(int l,int r,int x){
        int L=1,R=n,M;
        while(L<=R){
            M=(L+R)>>1;
            if(w[1][M]<=x) L=M+1;
            else R=M-1;
        }

        change(1,1,1,n,l,r,L-1);
    }

    void query(int o,int dep,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R){
            res+=s[o];return;
        }

        int M=(L+R)>>1;
        pushdown(o,L,dep);
        if(qL<=M) query(o<<1,dep+1,L,M,qL,qR);
        if(qR>M) query(o<<1|1,dep+1,M+1,R,qL,qR);
    }

    int Query(int l,int r){
        res=0;
        query(1,1,1,n,l,r);
        return res;
    }
}seg;

int main(){
    int T,last;
    int l,r,x;
    LL ans;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        last=0;ans=0;
        scanf("%d%d%d%d",&n,&m,&A,&B);a=A;b=B;
        for(int i=1;i<=n;i++) scanf("%d",&pa[i]);
        for(int i=1;i<=n;i++) scanf("%d",&pb[i]);

        seg.build(1,1,1,n);

        for(int i=1;i<=m;i++){
             l = rnd(last) % n + 1, r = rnd(last) % n + 1, x = rnd(last) + 1;

             //printf("l:%d r:%d x:%d op:%c\n",l,r,x,((l+r+x)&1)?'+':'?');
             if(l>r) swap(l,r);
             if((l+r+x)%2==0){// ?
                last=seg.Query(l,r);
               //printf("last:%d\n",last);
                ans+=(LL)i*last;
                if(ans>=mod) ans%=mod;
             }
             else{
                seg.Change(l,r,x);
             }
        }

        printf("%I64d\n",ans);
    }
    return 0;
}
