#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=50010;
const int maxnode=maxn*100;
int n,m;

struct Node{
	Node *ch[2];
	int size,add;
	Node() {}
};
Node *null,seq[maxnode];int seq_cnt=0;

Node *New(){Node *o=&seq[seq_cnt++];o->ch[0]=o->ch[1]=null;o->size=o->add=0;return o;}

void add(Node* &o,int L,int R,int qL,int qR){
	//printf("1DL:%d R:%d qL:%d qR:%d\n",L,R,qL,qR);//printf("o->size:%d add:%d\n",o->size,o->add);
	if(o==null) o=New();
	//	printf("o->size:%d add:%d\n",o->size,o->add);
	if(qL<=L&&qR>=R) {o->add++;o->size+=R-L+1;return;}
	int M=(L+R)>>1;
	if(qL<=M) add(o->ch[0],L,M,qL,qR);
	if(qR>M) add(o->ch[1],M+1,R,qL,qR);
	o->size=o->ch[0]->size+o->ch[1]->size+(R-L+1)*o->add;
}

int Query(Node* &o,int L,int R,int qL,int qR){
	//printf("1DL:%d R:%d qL:%d qR:%d size:%d add:%d\n",L,R,qL,qR,o->size,o->add);
	if(qL<=L&&qR>=R) return o->size;
	int M=(L+R)>>1;
	int ans=(min(R,qR)-max(L,qL)+1)*o->add;
	if(qL<=M) ans+=Query(o->ch[0],L,M,qL,qR);
	if(qR>M) ans+=Query(o->ch[1],M+1,R,qL,qR);
	return ans;
}

struct Seg2D{
	Node *root[maxn<<3];
	Seg2D() {}
	
	void insert(int o,int L,int R,int t,int qL,int qR){
		if(root[o]==null) root[o]=New();
			
		add(root[o],1,n,qL,qR);//printf("2DL:%d R:%d size:%d add:%d \n",L,R,root[o]->size,root[o]->add);
		if(L==R) {return;}
		int M=(L+R)>>1;
		if(t<=M) insert(o<<1,L,M,t,qL,qR);
		else insert(o<<1|1,M+1,R,t,qL,qR);
	}
	
	int query(int o,int L,int R,int qL,int qR,int k){
		if(L==R) return L;
			//printf("2DL:%d R:%d qL:%d qR:%d k:%d\n",L,R,qL,qR,k);
		int M=(L+R)>>1;
		int num=Query(root[o<<1|1],1,n,qL,qR);
		if(num>=k) return query(o<<1|1,M+1,R,qL,qR,k);
		else {k-=num;return query(o<<1,L,M,qL,qR,k);}
	}
}seg;



int main(){
	int op,a,b,c;
	null=new Node();null->ch[0]=null->ch[1]=null;null->size=0;null->add=0;
	scanf("%d%d",&n,&m);
	for(int i=0;i<8*maxn;i++) seg.root[i]=null;
	while(m--){
		scanf("%d%d%d%d",&op,&a,&b,&c);
		if(op==1)
			c+=n+1,seg.insert(1,1,2*n+1,c,a,b);
		else printf("%d\n",seg.query(1,1,2*n+1,a,b,c)-n-1);
	}
	return 0;
}
