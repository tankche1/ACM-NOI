# include<stdio.h>
# include<string.h>
# include<algorithm>
# define pos(x) (x+100000)
# define rehis(x) s[x].his=max(s[x].his,s[x].max);
using namespace std;
const int maxn=100010;
typedef long long LL;
const LL INF=1LL<<60;
int n,m;
int A[maxn];
struct Node{
	LL max,his,lazy,hislazy;
	Node() {max=0;his=0;lazy=0;hislazy=0;}
	Node(LL max,LL his,LL lazy=0,LL hislazy=0) :max(max),his(his),lazy(lazy),hislazy(hislazy) {}
};

Node s[maxn<<2];

void pushup(int o){
	s[o].max=max(s[o<<1].max,s[o<<1|1].max);
	s[o].his=max(s[o<<1].his,s[o<<1|1].his);
}

void pushdown(int o){
	if(s[o].hislazy||s[o].lazy){
		//printf("%d\n",o);
		s[o<<1].his=max(s[o<<1].max+s[o].hislazy,s[o<<1].his);
		s[o<<1].max+=s[o].lazy;
		s[o<<1].hislazy=max(s[o<<1].hislazy,s[o<<1].lazy+s[o].hislazy);
		s[o<<1].lazy+=s[o].lazy;
		s[o<<1|1].his=max(s[o<<1|1].max+s[o].hislazy,s[o<<1|1].his);
		s[o<<1|1].max+=s[o].lazy;
		s[o<<1|1].hislazy=max(s[o<<1|1].hislazy,s[o<<1|1].lazy+s[o].hislazy);
		s[o<<1|1].lazy+=s[o].lazy;
		s[o].hislazy=s[o].lazy=0;
	}
}

void update(int o,int L,int R,int qL,int qR,int val){
	//printf("o:%d L:%d R:%d qL:%d qR:%d val:%d %lld %lld\n",o,L,R,qL,qR,val,s[o].max,s[o].his);
	if(qL<=L&&qR>=R){
		s[o].max+=val;s[o].lazy+=val;s[o].hislazy=max(s[o].hislazy,s[o].lazy);
		s[o].his=max(s[o].his,s[o].max);//printf("co:%d L:%d R:%d qL:%d qR:%d val:%d %lld %lld\n",o,L,R,qL,qR,val,s[o].max,s[o].his);
		return;
	}
	int M=(L+R)>>1;
	pushdown(o);
	if(qL<=M) update(o<<1,L,M,qL,qR,val);
	if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
	pushup(o);
	//printf("co:%d L:%d R:%d qL:%d qR:%d %lld %lld\n",o,L,R,qL,qR,s[o].max,s[o].his);
	//printf("co:%d L:%d R:%d qL:%d qR:%d val:%d %lld %lld\n",o,L,R,qL,qR,val,s[o].max,s[o].his);
}

LL query(int o,int L,int R,int qL,int qR){
	//printf("oo:%d L:%d R:%d qL:%d qR:%d %lld %lld\n",o,L,R,qL,qR,s[o].max,s[o].his);
	if(qL<=L&&qR>=R)
		return s[o].his;
	LL ans=-INF;
	int M=(L+R)>>1;
	pushdown(o);
	if(qL<=M) ans=max(ans,query(o<<1,L,M,qL,qR));
	if(qR>M)    ans=max(ans,query(o<<1|1,M+1,R,qL,qR));
	return ans;
}

struct Query{
	int left,right,bh;
	Query() {}
	Query(int left,int right,int bh) :left(left),right(right),bh(bh) {}
	bool operator < (const Query &rhs)const{
		return right<rhs.right;
	}
};
Query q[maxn];

int last[maxn<<1];
LL ans[maxn];

int main(){
	//freopen("input.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	scanf("%d",&m);int l,r;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&l,&r);q[i]=Query(l,r,i);
	}
	sort(q+1,q+m+1);
	int nowq=1;
	memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++){
		update(1,1,n,last[pos(A[i])]+1,i,A[i]);
		while(q[nowq].right==i){
			ans[q[nowq].bh]=query(1,1,n,q[nowq].left,q[nowq].right);
			//printf("ans[%d}:%lld\n",q[nowq].bh,ans[q[nowq].bh]);
			nowq++;
		}
		if(nowq>m) break;
		last[pos(A[i])]=i;
	}
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
