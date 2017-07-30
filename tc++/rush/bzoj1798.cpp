# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int mod,n,m;
int a[maxn],op;
typedef long long LL;
struct Lazy{
	LL plus,mul;
	Lazy() {}
	Lazy(LL plus,LL mul):plus(plus),mul(mul) {}
	bool operator == (Lazy rhs)const{
		return rhs.plus==plus&&rhs.mul==mul;
	}
};
Lazy none,mark[maxn<<2];
LL sum[maxn<<2];
void Plus(LL &a,LL b) {a+=b;a%=mod;}
void Mul(LL &a,LL b) {a*=b;a%=mod;}

void build(int o,int L,int R){
	mark[o]=none;
	if(L==R) {sum[o]=a[L];return;}
	int M=(L+R)>>1;
	build(o<<1,L,M);build(o<<1|1,M+1,R);
	sum[o]=(sum[o<<1]+sum[o<<1|1])%mod;
}

void MarkIt(int o,int len,Lazy laz){
	Mul(sum[o],laz.mul);Plus(sum[o],laz.plus*len);
	Mul(mark[o].plus,laz.mul);Plus(mark[o].plus,laz.plus);Mul(mark[o].mul,laz.mul);
}

void pushdown(int o,int L,int R){
	if(mark[o]==none) return;
	int M=(L+R)>>1;
	MarkIt(o<<1,M-L+1,mark[o]);MarkIt(o<<1|1,R-M,mark[o]);
	mark[o]=none;
}

void update(int o,int L,int R,int qL,int qR,Lazy laz){
//	printf("%d %d\n",L,R);
	if(qL<=L&&qR>=R){
		//printf("%d %d\n",L,R);
		MarkIt(o,R-L+1,laz);
		return;
	}
	pushdown(o,L,R);
	int M=(L+R)>>1;
	if(qL<=M) update(o<<1,L,M,qL,qR,laz);
	if(qR>M) update(o<<1|1,M+1,R,qL,qR,laz);
	sum[o]=sum[o<<1]+sum[o<<1|1];sum[o]%=mod;
}

int query(int o,int L,int R,int qL,int qR){
	//printf("L:%d R:%d sum:%d\n",L,R,sum[o]);
	if(qL<=L&&qR>=R) return sum[o];
	pushdown(o,L,R);
	LL ans=0;int M=(L+R)>>1;
	if(qL<=M) ans+=query(o<<1,L,M,qL,qR);
	if(qR>M) ans+=query(o<<1|1,M+1,R,qL,qR);
	return ans%mod;
}

int main(){
	none.mul=1;none.plus=0;
	int l,r,c;
	scanf("%d%d",&n,&mod);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	scanf("%d",&m);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d",&l,&r,&c);
			Lazy laz(0,c);
			update(1,1,n,l,r,laz);
		}
		else if(op==2){
			scanf("%d%d%d",&l,&r,&c);
			Lazy laz(c,1);
			update(1,1,n,l,r,laz);
		}
		else{
			scanf("%d%d",&l,&r);
			printf("%d\n",query(1,1,n,l,r));
		}
	}
	return 0;
}
