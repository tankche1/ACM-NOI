#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=500110;
LL a[maxn],b[maxn];
LL n,m,x,y;
inline LL pos(int x,int y) {return (x-1)*n+y;}
inline bool check(int x,int y) {return x>=1&&x<=m&&y>=1&&y<=n;}

inline LL gcd(LL x,LL y){
	if(x<y) swap(x,y);
	if(y==0) return x;
	return gcd(y,x%y);
}

struct Node{
	Node *ch[2];
	LL g;
	Node() {}
};
Node seq[maxn*20];int seq_cnt=0;
Node *null;

Node *New(){
	Node *o=&seq[seq_cnt++];o->ch[0]=o->ch[1]=null;o->g=0;//if(seq_cnt%500==0) printf("seq_cnt:%d\n",seq_cnt);
	return o;
}

struct SegmenTree1D{
	Node* build(int L,int R,LL *tmp){
		Node *o=New();
		if(L==R) {o->g=tmp[L];return o;}
		int M=(L+R)>>1;
		o->ch[0]=build(L,M,tmp);
		o->ch[1]=build(M+1,R,tmp);
		o->g=gcd(o->ch[0]->g,o->ch[1]->g);
		return o;
	}
	
	LL query(Node *o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R) return o->g;
		//	printf("L:%d  R:%d qL:%d qR:%d\n",L,R,qL,qR);//int dd;scanf("%d",&dd);
		int M=(L+R)>>1;
		LL ans=0;
		if(qL<=M) ans=gcd(ans,query(o->ch[0],L,M,qL,qR));
		if(qR>M) ans=gcd(ans,query(o->ch[1],M+1,R,qL,qR));
		return ans;
	}
	
	void add(Node *o,int L,int R,int t,LL val){
		//printf("%d %d t:%d\n",L,R,t);
		if(L==R) {o->g+=val;return;}
		int M=(L+R)>>1;
		if(t<=M) add(o->ch[0],L,M,t,val);
		else add(o->ch[1],M+1,R,t,val);
		o->g=gcd(o->ch[0]->g,o->ch[1]->g);
	}
	
	void modify(Node *o,int L,int R,int t,LL val){
		if(L==R) {o->g=val;return;}
		int M=(L+R)>>1;
		if(t<=M) modify(o->ch[0],L,M,t,val);
		else modify(o->ch[1],M+1,R,t,val);
		o->g=gcd(o->ch[0]->g,o->ch[1]->g);
	}
}seg1D;

LL tmp[maxn];

struct SegmenTree2D{
	Node *s[maxn<<2];
	
	LL query(int o,int xL,int xR,int qL,int qR,int yL,int yR){
		if(qL<=xL&&qR>=xR)
			return seg1D.query(s[o],1,n,yL,yR);
		int M=(xL+xR)>>1;
		LL ans=0;
		if(qL<=M) ans=gcd(ans,query(o<<1,xL,M,qL,qR,yL,yR));
		if(qR>M) ans=gcd(ans,query(o<<1|1,M+1,xR,qL,qR,yL,yR));
		return ans;
	}
	
	void modify(int o,int xL,int xR,int tx,int ty,LL val){
		if(!check(tx,ty)) return;
		//	printf("xL:%d xR:%d tx:%d ty:%d\n",xL,xR,tx,ty);
		if(xL==xR)
		{seg1D.add(s[o],1,n,ty,val);return;}
		int M=(xL+xR)>>1;
		if(tx<=M)
			modify(o<<1,xL,M,tx,ty,val);
		if(tx>M)
			modify(o<<1|1,M+1,xR,tx,ty,val);//printf("ty:%d\n",ty);
		seg1D.modify(s[o],1,n,ty,gcd(seg1D.query(s[o<<1],1,n,ty,ty),seg1D.query(s[o<<1|1],1,n,ty,ty)));
	}
	
	void build(int o,int xL,int xR,LL *A){
		if(xL==xR){
			s[o]=seg1D.build(1,n,A+(xL-1)*n);
			return;
		}
		int M=(xL+xR)>>1;
		build(o<<1,xL,M,A);
		build(o<<1|1,M+1,xR,A);
		for(int i=1;i<=n;i++)
			tmp[i]=gcd(seg1D.query(s[o<<1],1,n,i,i),seg1D.query(s[o<<1|1],1,n,i,i));
		s[o]=seg1D.build(1,n,tmp);
	}
	
}seg2D;

void change(){
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",&a[pos(i,j)]);
	b[pos(x,y)]=a[pos(x,y)];
	for(int i=x-1;i>=1;i--)
		b[pos(i,y)]=a[pos(i,y)]-a[pos(i+1,y)];
	for(int i=x+1;i<=m;i++)
		b[pos(i,y)]=a[pos(i,y)]-a[pos(i-1,y)];
	for(int j=y-1;j>=1;j--)
		b[pos(x,j)]=a[pos(x,j)]-a[pos(x,j+1)];
	for(int j=y+1;j<=n;j++)
		b[pos(x,j)]=a[pos(x,j)]-a[pos(x,j-1)];
	for(int i=x-1;i>=1;i--)
		for(int j=y-1;j>=1;j--)
			b[pos(i,j)]=a[pos(i,j)]+a[pos(i+1,j+1)]-a[pos(i+1,j)]-a[pos(i,j+1)];
	for(int i=x-1;i>=1;i--)
		for(int j=y+1;j<=n;j++)
			b[pos(i,j)]=a[pos(i,j)]+a[pos(i+1,j-1)]-a[pos(i+1,j)]-a[pos(i,j-1)];
	for(int i=x+1;i<=m;i++)
		for(int j=y-1;j>=1;j--)
			b[pos(i,j)]=a[pos(i,j)]+a[pos(i-1,j+1)]-a[pos(i-1,j)]-a[pos(i,j+1)];
	for(int i=x+1;i<=m;i++)
		for(int j=y+1;j<=n;j++)
			b[pos(i,j)]=a[pos(i,j)]+a[pos(i-1,j-1)]-a[pos(i-1,j)]-a[pos(i,j-1)];
	seg2D.build(1,1,m,b);
}

int main(){
	//freopen("chess.in","r",stdin);
	//freopen("chess.out","w",stdout);
	//freopen("input.txt","r",stdin);
	null=new Node();null->ch[0]=null->ch[1]=null;null->g=0;
	int x1,y1,x2,y2,op;LL c;
	scanf("%lld%lld",&m,&n);
	scanf("%lld%lld",&x,&y);
	int T;
	scanf("%d",&T);
	change();
	for(int i=1;i<=T;i++){
		scanf("%d",&op);
		if(op==0){
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1=x-x1;y1=y-y1;x2=x+x2;y2=y+y2;
			printf("%lld\n",seg2D.query(1,1,m,x1,x2,y1,y2));
		}
		else{
			scanf("%d%d%d%d%lld",&x1,&y1,&x2,&y2,&c);
			if(x1<=x&&y1<=y) seg2D.modify(1,1,m,x1-1,y1-1,c);
			if(x1<=x&&y1>y) seg2D.modify(1,1,m,x1-1,y,-c);
			if(x1>x&&y1<=y) seg2D.modify(1,1,m,x1,y1-1,-c);
			if(x1>x&&y1>y) seg2D.modify(1,1,m,x1,y1,c);
				
			if(x2<x&&y1<=y) seg2D.modify(1,1,m,x2,y1-1,-c);
			if(x2<x&&y1>y) seg2D.modify(1,1,m,x2,y1,c);
			if(x2>=x&&y1<=y) seg2D.modify(1,1,m,x2+1,y1-1,c);
			if(x2>=x&&y1>y) seg2D.modify(1,1,m,x2+1,y1,-c);
				
			if(x1<=x&&y2<y) seg2D.modify(1,1,m,x1-1,y2,-c);
			if(x1<=x&&y2>=y) seg2D.modify(1,1,m,x1-1,y2+1,c);
			if(x1>x&&y2<y) seg2D.modify(1,1,m,x1,y2,c);
			if(x1>x&&y2>=y) seg2D.modify(1,1,m,x1,y2+1,-c);
				
			if(x2<x&&y2<y) seg2D.modify(1,1,m,x2,y2,c);
			if(x2<x&&y2>=y) seg2D.modify(1,1,m,x2,y2+1,-c);
			if(x2>=x&&y2<y) seg2D.modify(1,1,m,x2+1,y2,-c);
			if(x2>=x&&y2>=y) seg2D.modify(1,1,m,x2+1,y2+1,c);
				
			if(y1<=y&&y2>=y){
				if(x1<=x) seg2D.modify(1,1,m,x1-1,y,-c);else seg2D.modify(1,1,m,x1,y,c);
				if(x2<x) seg2D.modify(1,1,m,x2,y,c);else seg2D.modify(1,1,m,x2+1,y,-c);
			}
			
			if(x1<=x&&x2>=x){
				if(y1<=y) seg2D.modify(1,1,m,x,y1-1,-c);else seg2D.modify(1,1,m,x,y1,c);
				if(y2<y) seg2D.modify(1,1,m,x,y2,c);seg2D.modify(1,1,m,x,y2+1,-c);
			}
			
			if(x1<=x&&x2>=x&&y1<=y&&y2>=y)
				seg2D.modify(1,1,m,x,y,c);
		}
	}
	return 0;
}
