# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int INF=~0U>>3;
int length,width,n,height;

struct SegmenTree{
	int delta[maxn<<2],minimal[maxn<<2];
	
	void init(){
		memset(delta,0,sizeof(delta));memset(minimal,0,sizeof(minimal));
	}
	
	void update(int o,int L,int R,int qL,int qR,int val){
		if(qL<=L&&qR>=R){
			delta[o]+=val;return;
		}
		int M=(L+R)>>1;
		if(qL<=M) update(o<<1,L,M,qL,qR,val);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
		minimal[o]=min(delta[o<<1]+minimal[o<<1],delta[o<<1|1]+minimal[o<<1|1]);
		return;
	}
	
	int query(){
		return delta[1]+minimal[1];
	}
};

struct Tree{
	SegmenTree node[maxn];
	
	void init(){
		for(int i=1;i<=width+1;i++)
			node[i].init();
	}
	
	void update(int x1,int y1,int x2,int y2,int val){
		x1++;y1++;x2++;y2++;
		for(int i=x1;i<=x2;i++)
			node[i].update(1,0+1,width+1,y1,y2,val);
	}
	
	bool query(){
		int res=INF;
		for(int i=1;i<=length+1;i++)
			res=min(res,node[i].query());
		return res==0;
	}
	
}tree;

struct Box{
	int x1,y1,z1,x2,y2,z2;
	void read(){
		scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);
	}
	Box(){}
	Box(int x1,int y1,int z1,int x2,int y2,int z2):x1(x1),y1(y1),z1(z1),x2(x2),y2(y2),z2(z2) {}
};
Box box1[maxn],box[maxn];

struct Event{
	int x1,y1,x2,y2,z,val;
	Event() {}
	Event(int x1,int y1,int x2,int y2,int z,int val):x1(x1),y1(y1),x2(x2),y2(y2),z(z),val(val) {}
	bool operator <(const Event &rhs)const{
		if(z==rhs.z) return val>rhs.val;
		return z<rhs.z;
	}
}event[maxn<<1];

bool havespace(int len){
	tree.init();
	int m=n;
	box1[m++]=Box(0,0,height,length+1,width+1,height);
	box1[m++]=Box(length,0,0,length+1,width+1,height);
	box1[m++]=Box(0,width,0,length+1,width+1,height);
	for(int i=0;i<m;i++){
		box[i].x1=max(0,box1[i].x1-len+1);
		box[i].y1=max(0,box1[i].y1-len+1);
		box[i].z1=max(0,box1[i].z1-len+1);
		box[i].x2=max(0,box1[i].x2-1);
		box[i].y2=max(0,box1[i].y2-1);
		box[i].z2=box1[i].z2;
	}
	for(int i=0;i<m;i++){
	if(box[i].x1<=box[i].x2&&box[i].y1<=box[i].y2&&box[i].z1<=box[i].z2){
		event[2*i]=Event(box[i].x1,box[i].y1,box[i].x2,box[i].y2,box[i].z1,1);
		event[2*i+1]=Event(box[i].x1,box[i].y1,box[i].x2,box[i].y2,box[i].z2,-1);
		}
	}
	sort(event,event+2*m);
	
	tree.init();
	bool ok=false;
	int pos=0;
	for(int nowz=0;nowz<height;nowz++){
		while(pos<2*m&&event[pos].z==nowz){
			tree.update(event[pos].x1,event[pos].y1,event[pos].x2,event[pos].y2,event[pos].val);pos++;
		}
		if(tree.query())
		{ok=true;break;}
	}
	return ok;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("cubic.out","w",stdout);
	int tcase;
	scanf("%d",&tcase);
	for(int tt=1;tt<=tcase;tt++){
		scanf("%d%d%d%d",&n,&length,&width,&height);
		for(int i=0;i<n;i++)
			box1[i].read();
		int L=1,R=min(length,min(width,height));
		while(L<=R){
			int M=(L+R)>>1;
			//printf("%d\n",M);
			if(havespace(M))
				L=M+1;
			else R=M-1;
		}
		printf("Case %d: %d\n",tt,L-1);
	}
	return 0;
}
/*
2
2 10 15 8
0 0 0 4 11 3
0 11 0 4 15 8

1 500 500 500
0 0 0 500 500 500

*/
