# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=50010;
int n,m;
int qL,qR;

struct Node{
	int maxl,ls,rs;
	int lazy;
};

struct SegmentTree{
	Node s[maxn<<2];
	
	void pushdown(int o,int L,int R){
		if(s[o].lazy!=-1){
			int M=(L+R)>>1;
			s[o<<1].maxl=s[o<<1].ls=s[o<<1].rs=(M-L+1)*s[o].lazy;
			s[o<<1].lazy=s[o<<1|1].lazy=s[o].lazy;
			s[o<<1|1].maxl=s[o<<1|1].ls=s[o<<1|1].rs=(R-M)*s[o].lazy;
			s[o].lazy=-1;
		}
	}
	
	void maintain(int o,int L,int R){
		int M=(L+R)>>1;
		s[o].maxl=max(max(s[o<<1].maxl,s[o<<1|1].maxl),s[o<<1].rs+s[o<<1|1].ls);
		s[o].ls=s[o<<1].ls==(M-L+1)?M-L+1+s[o<<1|1].ls:s[o<<1].ls;
		s[o].rs=s[o<<1|1].rs==(R-M)?R-M+s[o<<1].rs:s[o<<1|1].rs;
	}
	
	void build(int o,int left,int right){
		s[o].maxl=s[o].ls=s[o].rs=right-left+1;s[o].lazy=-1;
		if(left==right) return;
		int M=(left+right)>>1;
		build(o<<1,left,M);build(o<<1|1,M+1,right);
	}
	
	void query(int o,int L,int R,int len){
		int M=(L+R)>>1;
		if(L==R) {qL=qR=L;return;}
		pushdown(o,L,R);
		if(s[o<<1].maxl>=len) query(o<<1,L,M,len);
		else if(s[o<<1].rs+s[o<<1|1].ls>=len) {qL=M-s[o<<1].rs+1;qR=qL+len-1;return;}
		else query(o<<1|1,M+1,R,len);
	}
	
	void update(int o,int L,int R,int qL,int qR,int val){
		if(qL<=L&&qR>=R){
			s[o].maxl=s[o].ls=s[o].rs=(R-L+1)*val;s[o].lazy=val;return;
		}
		pushdown(o,L,R);
		int M=(L+R)>>1;
		if(qL<=M) update(o<<1,L,M,qL,qR,val);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
		maintain(o,L,R);
	}
	
};
SegmentTree seg;
int main(){
	scanf("%d%d",&n,&m);
	seg.build(1,1,n);
	for(int i=1;i<=m;i++){
		int op,x,d;
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&d);
			if(seg.s[1].maxl<d) puts("0");
				else{
					seg.query(1,1,n,d);
					seg.update(1,1,n,qL,qR,0);
					printf("%d\n",qL);
				}
		}
		else{
			scanf("%d%d",&x,&d);
			seg.update(1,1,n,x,x+d-1,1);
		}
	}
	return 0;
}
