# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=500010;
const int INF=~0U>>1;
int n,k,L,R;
int A[maxn];
typedef long long LL;
int s[maxn];
/*struct State{
	
};*/

struct SeqmenTree{
	int num[maxn<<2];
	
	void build(int o,int L,int R){
		if(L==R){
			num[o]=L;return;
		}
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
		if(s[num[o<<1]]>s[num[o<<1|1]])
		num[o]=num[o<<1];
		else num[o]=num[o<<1|1];
	}
	
	int query(int o,int L,int R,int qL,int qR){
		//printf("o:%d L:%d R:%d qL:%d qR:%d num:%d\n",o,L,R,qL,qR,num[o]);
		if(qL<=L&&qR>=R) return num[o];
		int M=(L+R)>>1;
		int ans=-INF,k,d;
		if(qL<=M) //ans=max(ans,query(o<<1,L,M,qL,qR));
			if(s[(d=query(o<<1,L,M,qL,qR))]>ans) 
				ans=s[d],k=d;
		if(qR>M) 
			if(s[(d=query(o<<1|1,M+1,R,qL,qR))]>ans) 
				ans=s[d],k=d;
			//printf("k:%d\n",k);
		return k;
	}
	
};
SeqmenTree seq;
struct HeapNode{
	int j,a,b,val;
	HeapNode(int j=0,int a=0,int b=0,int val=0):j(j),a(a),b(b),val(val) {}
	bool operator < (const HeapNode &rhs)const{
		return s[val]-s[j]<s[rhs.val]-s[rhs.j];
	}
};
priority_queue<HeapNode> Q;

int main(){
	scanf("%d%d%d%d",&n,&k,&L,&R);
	s[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),s[i]=s[i-1]+A[i];
	seq.build(1,1,n);
	for(int i=0;i+L<=n;i++)
		Q.push(HeapNode(i,i+L,min(n,i+R),seq.query(1,1,n,i+L,min(n,i+R))));//,printf("%d %d %d %d\n",i,i+L,min(n,i+R),seq.query(1,1,n,i+L,min(n,i+R)));
	LL ans=0;
	for(int i=1;i<=k;i++){
		HeapNode now=Q.top();Q.pop();
		ans+=s[now.val]-s[now.j];//printf("%d %d a:%d b:%d\n",now.val,now.j,now.a,now.b);
		if(now.val>now.a) Q.push(HeapNode(now.j,now.a,now.val-1,seq.query(1,1,n,now.a,now.val-1)));
		if(now.val<now.b) Q.push(HeapNode(now.j,now.val+1,now.b,seq.query(1,1,n,now.val+1,now.b)));
	}
	printf("%lld\n",ans);
	return 0;
}
