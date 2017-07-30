#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=20010;
const int INF=3*100000010;
int n,k;
int weight[maxn];

struct SegmenTree{
	int _min[maxn<<2],add[maxn<<2];
	void build(int o,int L,int R){
		add[o]=0;
		if(L==R) {_min[o]=weight[L];return;}
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
		_min[o]=min(_min[o<<1],_min[o<<1|1]);
	}
	
	void pushdown(int o){
		if(add[o]!=0){
			add[o<<1]+=add[o];add[o<<1|1]+=add[o];
			_min[o<<1]+=add[o];_min[o<<1|1]+=add[o];
			add[o]=0;
		}
	}
	
	void update(int o,int L,int R,int qL,int qR,int val){
		if(qL>qR) return;
		if(qL<=L&&qR>=R){
			_min[o]+=val;add[o]+=val;
			return;
		}
		pushdown(o);
		int M=(L+R)>>1;
		if(qL<=M) update(o<<1,L,M,qL,qR,val);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
		_min[o]=min(_min[o<<1],_min[o<<1|1]);
	}
	
	int query(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R) return _min[o];
		pushdown(o);
		int M=(L+R)>>1;
		int ans=INF;
		if(qL<=M) ans=min(ans,query(o<<1,L,M,qL,qR));
		if(qR>M) ans=min(ans,query(o<<1|1,M+1,R,qL,qR));
		return ans;
	}
	
}seg;

struct tank{
	int l,r,p;
	tank() {}
	tank(int l,int r,int p):l(l),r(r),p(p) {}
};
tank Duty[maxn];
int D[maxn],C[maxn],S[maxn],W[maxn];
int dp[maxn][2];

bool cmp(tank A,tank B){
	return A.r<B.r;
}
int ans=0;

int main(){
	//freopen("input.txt","r",stdin);
	scanf("%d%d",&n,&k);
	D[1]=0;
	for(int i=2;i<=n;i++)
		scanf("%d",&D[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&C[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&S[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&W[i]);
	D[++n]=D[n-1]+1000000005;
	C[n]=S[n]=W[n]=0;
	k++;
	for(int i=1;i<=n;i++){
		Duty[i].p=i;
		Duty[i].l=lower_bound(D+1,D+n+1,D[i]-S[i])-D-1;
		Duty[i].r=upper_bound(D+1,D+n+1,D[i]+S[i])-D;
	}
	sort(Duty+1,Duty+n+1,cmp);
	int sum=0,pos=1;
	for(int i=1;i<=n;i++){
		while(Duty[pos].r==i){
			sum+=W[Duty[pos].p];pos++;
		}
		dp[i][1]=sum+C[i];
	}
	ans=dp[n][1];
	for(int j=2;j<=k;j++){
		int now=j&1;int last=now^1;
		int pos=1;
		for(int i=1;i<j-1;i++) weight[i]=INF;
		for(int i=j-1;i<=n;i++) weight[i]=dp[i][last];
		seg.build(1,1,n);
		while(pos<=n&&Duty[pos].r<j) pos++;
		for(int i=j;i<=n;i++){
			while(pos<=n&&Duty[pos].r==i){
				seg.update(1,1,n,1,Duty[pos].l,W[Duty[pos].p]);
				pos++;
			}
			dp[i][now]=seg.query(1,1,n,1,i-1)+C[i];
		}
		ans=min(ans,dp[n][now]);
	}
	printf("%d\n",ans);
	return 0;
}
