# include<stdio.h>
# include<string.h>
# include<algorithm>
# define hei puts("fuck");
using namespace std;
typedef long long LL;
const int maxn=10010;
LL n,mod,q;
LL a[maxn];
LL p[12];

LL quick_pow(LL a,LL x){
    LL now=a,ans=1;
    while(x>0){
        if(x&1){
            ans=ans*now%mod;
        }
        x>>=1;now=now*now%mod;
    }
    return ans;
}

void prepare(){
    p[0]=0;
    LL x=mod;
    for(LL j=2;j*j<=x;j++){
        //printf("j:%lld x:%lld\n",j,x);
        if(x%j==0){
            p[++p[0]]=j;
            while(x%j==0) x/=j;
        }
    }
    if(x>1) p[++p[0]]=x;
}

struct Tank{
    LL a[12],rest;
    void get(LL x){
        for(int i=1;i<=p[0];i++) a[i]=0;
        if(x==0) {rest=0;return;}
        for(int i=1;i<=p[0];i++){
            while(x%p[i]==0) x/=p[i],a[i]++;
        }
        rest=x;
    }

    void add(Tank A,Tank B){
        for(int i=1;i<=p[0];i++) a[i]=A.a[i]+B.a[i];
        rest=A.rest*B.rest;
        if(rest>=mod) rest%=mod;
    }

    void init() {memset(a,0,sizeof(a));rest=1;}
}num,ans;


void exgcd(LL a,LL b,LL &d,LL &x,LL &y){
	if(b==0){
		d=a;x=1;y=0;return;
	}
	exgcd(b,a%b,d,y,x);
	y-=a/b*x;
}

LL inverse(LL tmp){
    LL x,y,d;
    exgcd(tmp,mod,d,x,y);
    x%=mod;if(x<0) x+=mod;
    return x;
}

struct SegmenTree{
    Tank sum[maxn<<2],lazy[maxn<<2];

    void build(int o,int L,int R){
        lazy[o].init();
        if(L==R){
            sum[o].get(a[L]);return;
        }
        int M=(L+R)>>1;
        build(o<<1,L,M);build(o<<1|1,M+1,R);
        sum[o].add(sum[o<<1],sum[o<<1|1]);
    }

    void pushdown(int o,int L,int R){
        int M=(L+R)>>1;
        for(int j=1;j<=p[0];j++){
            sum[o<<1].a[j]+=lazy[o].a[j]*(M-L+1);sum[o<<1|1].a[j]+=lazy[o].a[j]*(R-M);
        }
        sum[o<<1].rest=sum[o<<1].rest*quick_pow(lazy[o].rest,(M-L+1))%mod;
        sum[o<<1|1].rest=sum[o<<1|1].rest*quick_pow(lazy[o].rest,(R-M))%mod;
        lazy[o<<1].add(lazy[o<<1],lazy[o]);lazy[o<<1|1].add(lazy[o<<1|1],lazy[o]);
        lazy[o].init();
    }

    void update(int o,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R){
            for(int i=1;i<=p[0];i++) sum[o].a[i]+=num.a[i]*(R-L+1);
            sum[o].rest=sum[o].rest*quick_pow(num.rest,R-L+1)%mod;
            lazy[o].add(lazy[o],num);
            return;
        }
        pushdown(o,L,R);
        int M=(L+R)>>1;
        if(qL<=M) update(o<<1,L,M,qL,qR);
        if(qR>M) update(o<<1|1,M+1,R,qL,qR);
        sum[o].add(sum[o<<1],sum[o<<1|1]);
    }

    void query(int o,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R){
            ans.add(ans,sum[o]);return;
        }
        int M=(L+R)>>1;
        pushdown(o,L,R);
        if(qL<=M) query(o<<1,L,M,qL,qR);
        if(qR>M) query(o<<1|1,M+1,R,qL,qR);
    }

}seg;



int main(){
    int tcase,tnum=0;
    char tt;
    int L,R;LL x;
    LL print;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%lld%lld",&n,&mod);
        prepare();
        for(int i=1;i<=n;i++)
            scanf("%lld",&a[i]);
        seg.build(1,1,n);
        scanf("%lld",&q);
        printf("Case #%d:\n",++tnum);
        for(int i=1;i<=q;i++){
            while((tt=getchar())&&tt!='Q'&&tt!='D'&&tt!='M');
            if(tt=='M'){
                scanf("%d%d%lld",&L,&R,&x);
                num.get(x);
                seg.update(1,1,n,L,R);
            }
            else if(tt=='D'){
                scanf("%d%d%lld",&L,&R,&x);
                num.get(x);
                for(int i=1;i<=p[0];i++) num.a[i]=-num.a[i];
                num.rest=inverse(num.rest);
                seg.update(1,1,n,L,R);
            }
            else{
                scanf("%d%d",&L,&R);
                ans.init();
                seg.query(1,1,n,L,R);
                if(ans.rest==0) puts("0");
                else{
                    print=ans.rest;//printf("rest:%lld\n",print);
                    for(int i=1;i<=p[0];i++)
                        if(ans.a[i]) {//printf("%lld %lld\n",p[i],ans.a[i]);
                        print=print*quick_pow(p[i],ans.a[i])%mod;}
                    printf("%lld\n",print);
                }
            }
        }
    }
    return 0;
}
