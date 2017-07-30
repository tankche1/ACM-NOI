# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
int n,p[maxn];

struct SegmenTree{
	int sum[maxn<<2],add[maxn<<2];
	void pushdown(int o){
		if(add[o]){
			add[o<<1]+=add[o];add[o<<1|1]+=add[o];sum[o<<1]+=add[o];sum[o<<1|1]+=add[o];
			add[o]=0;
		}
	}
	void init() {memset(sum,0,sizeof(sum)),memset(add,0,sizeof(add));}
	
	void Add(int o,int L,int R,int qL,int qR,int val){
		if(qL<=L&&qR>=R) {sum[o]+=val,add[o]+=val;return;}
		pushdown(o);
		int M=(L+R)>>1;
		if(qL<=M) Add(o<<1,L,M,qL,qR,val);
		if(qR>M) Add(o<<1|1,M+1,R,qL,qR,val);
	}
	
	int query(int o,int L,int R,int pos){
		if(L==R) {return sum[o];}
		pushdown(o);
		int M=(L+R)>>1;
		if(pos<=M) return query(o<<1,L,M,pos);
		else return query(o<<1|1,M+1,R,pos);
	}
}seg;

int main(){
	int ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]),ans^=p[i];
	seg.init();
	for(int i=2;i<=n;i++){
		int x=n%i;
		//printf("x:%d i:%d \n",x,i);
		seg.Add(1,1,n,1,i-1,n/i);
		if(x>=1) seg.Add(1,1,n,1,x,1);
	}
	for(int i=1;i<=n;i++)
		ans^=((seg.query(1,1,n,i)&1)==1)?i:0;//printf("i:%d %d\n",i,seg.query(1,1,n,i));
	printf("%d\n",ans);
	return 0;
}
