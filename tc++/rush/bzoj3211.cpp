#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
const int maxm=200010;
int n,m;
int A[maxn];

struct SegmenTree{
	LL sum[maxn<<2];
	bool one[maxn<<2];//都是1
	
	void build(int o,int L,int R){
		if(L==R) {sum[o]=A[L];one[o]=sum[o]<=1;return;}
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
		sum[o]=sum[o<<1]+sum[o<<1|1];
		one[o]=one[o<<1]&one[o<<1|1];
	}
	
	LL query(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R){
			return sum[o];
		}
		LL ans=0;
		int M=(L+R)>>1;
		if(qL<=M) ans+=query(o<<1,L,M,qL,qR);
		if(qR>M) ans+=query(o<<1|1,M+1,R,qL,qR);
		return ans;
	}
	
	void update(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R&&one[o]) return;
		if(L==R){
			sum[o]=(LL)sqrt(sum[o]);one[o]=sum[o]<=1;return;
		}
		int M=(L+R)>>1;
		if(qL<=M) update(o<<1,L,M,qL,qR);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR);
		sum[o]=sum[o<<1]+sum[o<<1|1];
		one[o]=one[o<<1]&one[o<<1|1];
	}
}seg;

int main(){
	int op,L,R;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	seg.build(1,1,n);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&op,&L,&R);
		if(op==1){
			printf("%lld\n",seg.query(1,1,n,L,R));
		}
		else
			seg.update(1,1,n,L,R);
	}
	return 0;
}
