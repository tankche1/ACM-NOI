#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=300000;
int n;
int big,where;
struct worker{
	int l,r,v;
	bool operator < (const worker &rhs)const{
		return r<rhs.r;
	}
};
worker work[maxn],cork[maxn],tork[maxn];

struct SegmenTree{
	int _max[maxm<<2],add[maxm<<2],pos[maxm<<2];
	void build(int o,int L,int R) {
		_max[o]=add[o]=0;pos[o]=L;
		if(L==R) return;
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
	}
	
	void pushdown(int o){
		if(add[o]){
			_max[o<<1]+=add[o];_max[o<<1|1]+=add[o];
			add[o<<1]+=add[o];add[o<<1|1]+=add[o];
			add[o]=0;
		}
	}
	
	void Add(int o,int L,int R,int qL,int qR,int val){
		//printf("o:%d L:%d R:%d qL:%d qR:%d val:%d\n",o,L,R,qL,qR,val);
		if(qL<=L&&qR>=R){
			add[o]+=val;_max[o]+=val;return;
		}
		int M=(L+R)>>1;
		pushdown(o);
		if(qL<=M) Add(o<<1,L,M,qL,qR,val);
		if(qR>M) Add(o<<1|1,M+1,R,qL,qR,val);
		if(_max[o<<1]>_max[o<<1|1])
			_max[o]=_max[o<<1],pos[o]=pos[o<<1];
		else
			_max[o]=_max[o<<1|1],pos[o]=pos[o<<1|1];
	}
	
	void query(int o,int L,int R,int qL,int qR){
		//printf("o:%d L:%d R:%d qL:%d qR:%d\n",o,L,R,qL,qR);
		if(qL<=L&&qR>=R){
			if(_max[o]>big) {big=_max[o];where=pos[o];}
			return;
		}
		pushdown(o);
		int M=(L+R)>>1;
		if(qL<=M) query(o<<1,L,M,qL,qR);
		if(qR>M) query(o<<1|1,M+1,R,qL,qR);
	}
};
SegmenTree seg;

bool cmp(worker A,worker B){
	return A.v<B.v;
}

int main(){
	int m=0;
	int ans=0,L,R;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&work[i].l,&work[i].v,&work[i].r),m=max(m,work[i].r),cork[i]=work[i],tork[i]=work[i];
	sort(work+1,work+n+1);
	sort(tork+1,tork+n+1,cmp);
	seg.build(1,1,m);
	int noww=n,nowt=n;
	for(int i=m;i>=1;i--){
		if(work[noww].r==i){
			while(noww>0&&work[noww].r==i){
				seg.Add(1,1,m,work[noww].l,work[noww].v,1);//printf("add %d %d\n",work[i-1].l,work[i-1].v);
				noww--;
			}
			big=0;seg.query(1,1,m,1,i);//printf("query 1 %d big:%d where:%d \n",work[i].r,big,where);
			if(big>ans){
				ans=big;L=where;R=i;
			}
		}
		while(tork[nowt].v==i){
			seg.Add(1,1,m,tork[nowt].l,tork[nowt].v,-1);nowt--;
		}
	}
	printf("%d\n",ans);//printf("L:%d R:%d\n",L,R);
	bool first=true;
	for(int i=1;i<=n;i++){
		if(cork[i].l<=L&&cork[i].r>=R&&cork[i].v>=L&&cork[i].v<=R){
			if(!first) printf(" ");
			printf("%d ",i);
		}
	}puts("");
	return 0;
}
