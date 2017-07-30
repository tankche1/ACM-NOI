#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=200010;
typedef long long LL;
int n,ans;
const int mod=1000000007;

struct Point{
	int x,y;
	Point() {}
	bool operator < (const Point &rhs)const{
		return y==rhs.y?x<rhs.x:y<rhs.y;
	}
};Point p[maxn];
int x[maxn],y[maxn],xcnt,ycnt;

inline int lowbit(int x) {return x&(-x);}
struct FenwickTree{
	int C[maxn],n;
	
	void init(int nn) {memset(C,0,sizeof(C));n=nn;}
	void add(int x,int val) {while(x<=n) C[x]+=val,x+=lowbit(x);}
	int sum(int x) {int res=0;while(x) res+=C[x],x-=lowbit(x);return res;}
}fwt;

struct SegmenTree{
	int size[maxn<<2],sum[maxn<<2],lazy[maxn<<2];
	void build() {memset(size,0,sizeof(size));memset(sum,0,sizeof(sum));memset(lazy,0,sizeof(lazy));}
	void pushdown(int o){
		if(lazy[o]){
			lazy[o<<1]+=lazy[o],lazy[o<<1|1]+=lazy[o];
			sum[o<<1]+=lazy[o]*size[o<<1];sum[o<<1|1]+=lazy[o]*size[o<<1|1];
			lazy[o]=0;
		}
	}
	
	void update(int o){
		size[o]=size[o<<1]+size[o<<1|1];
		sum[o]=sum[o<<1]+sum[o<<1|1];
	}
	
	void add(int o,int L,int R,int qL,int qR,int val){
		if(qL<=L&&qR>=R){
			lazy[o]+=val;sum[o]+=size[o]*val;return;
		}
		pushdown(o);
		int M=(L+R)>>1;
		if(qL<=M) add(o<<1,L,M,qL,qR,val);
		if(qR>M) add(o<<1|1,M+1,R,qL,qR,val);
		update(o);
	}
	
	void insert(int o,int L,int R,int pos,int val){
		if(L==R){
			sum[o]+=val,size[o]++;return;
		}
		pushdown(o);
		int M=(L+R)>>1;
		if(pos<=M) insert(o<<1,L,M,pos,val);
		else insert(o<<1|1,M+1,R,pos,val);
		update(o);
	}
	
	int query(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R) return sum[o];
		pushdown(o);
		int M=(L+R)>>1,ans=0;
		if(qL<=M) ans+=query(o<<1,L,M,qL,qR);
		if(qR>M) ans+=query(o<<1|1,M+1,R,qL,qR);
		return ans;
	}
}seg;
int left[maxn],right[maxn];

void solve(){
	seg.build();fwt.init(xcnt);
	sort(p,p+n);
	for(int i=0;i<n;i++) fwt.add(p[i].x,1);//,printf("%d %d\n",p[i].x,p[i].y);
	for(int l=0;l<n;l++){
		int r=l;while(r<n&&p[r+1].y==p[r].y) r++;
		for(int i=l;i<=r;i++) fwt.add(p[i].x,-1);
		for(int i=l;i<=r;i++) if(p[i].x<xcnt) seg.add(1,1,xcnt,p[i].x+1,xcnt,-1);
		for(int i=l;i<=r;i++) left[i]=p[i].x==1?0:seg.query(1,1,xcnt,1,p[i].x-1);
		for(int i=l;i<=r;i++) seg.insert(1,1,xcnt,p[i].x,fwt.sum(p[i].x-1));
		l=r;
	}
	
	seg.build();fwt.init(xcnt);
	for(int i=0;i<n;i++) fwt.add(p[i].x,1);
	for(int l=0;l<n;l++){
		int r=l;while(r<n&&p[r+1].y==p[r].y) r++;
		for(int i=l;i<=r;i++) fwt.add(p[i].x,-1);
		for(int i=l;i<=r;i++) if(p[i].x>1) seg.add(1,1,xcnt,1,p[i].x-1,-1);
		for(int i=l;i<=r;i++) right[i]=p[i].x==xcnt?0:seg.query(1,1,xcnt,p[i].x+1,xcnt);
		for(int i=l;i<=r;i++) seg.insert(1,1,xcnt,p[i].x,fwt.sum(xcnt)-fwt.sum(p[i].x));
		l=r;
	}
	
	ans=0;
	for(int i=0;i<n;i++)
		ans=((LL)left[i]*right[i]+ans)%mod;
	printf("%d\n",ans);
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&x[i],&y[i]);
		p[i].x=x[i];p[i].y=y[i];
	}
	sort(x,x+n);sort(y,y+n);
	xcnt=unique(x,x+n)-x;ycnt=unique(y,y+n)-y;
	for(int i=0;i<n;i++)
		p[i].x=lower_bound(x,x+xcnt,p[i].x)-x+1,p[i].y=lower_bound(y,y+ycnt,p[i].y)-y+1;
	solve();
	return 0;
}
