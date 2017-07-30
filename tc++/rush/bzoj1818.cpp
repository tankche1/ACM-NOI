# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;

struct SeqmentTree{
	int sum[maxn<<2];
	
	void init() {memset(sum,0,sizeof(sum));}
	
	void update(int o,int L,int R,int q,int val){
		if(L==R){
			sum[o]+=val;return;
		}
		int M=(L+R)>>1;
		if(q<=M) update(o<<1,L,M,q,val);
			else update(o<<1|1,M+1,R,q,val);
		sum[o]=sum[o<<1]+sum[o<<1|1];
	}
	
	int query(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R)
			return sum[o];
		int M=(L+R)>>1;
		int ans=0;
		if(qL<=M)
			ans+=query(o<<1,L,M,qL,qR);
		if(qR>M) ans+=query(o<<1|1,M+1,R,qL,qR);
		return ans;
	}
}seq;
int n;
int bx[maxn],by[maxn];
int x[maxn],y[maxn];
struct point{
	int x,y;
};
point b[maxn];

struct Line{
	int st,ed,pos;
	Line(){}
	Line(int st,int ed,int pos):st(st),ed(ed),pos(pos) {}
};
Line row[maxn],line[maxn],eline[maxn];
int lcnt,rcnt;

bool cmp1(point a,point b){
	if(a.x!=b.x)
	return a.x<b.x;return a.y<b.y;
}

bool cmp2(point a,point b){
	if(a.y!=b.y)
	return a.y<b.y;return a.x<b.x;
}

bool cmp3(Line a,Line b){
	return a.st<b.st;
}

bool cmp4(Line a,Line b){
	return a.pos<b.pos;
}

bool cmp5(Line a,Line b){
	return a.ed<b.ed;
}

int main(){
	scanf("%d",&n);
	int ans=n;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&bx[i],&by[i]),x[i]=bx[i],y[i]=by[i];
	sort(x+1,x+n+1);sort(y+1,y+n+1);
	int xcnt=unique(x+1,x+n+1)-(x+1);
	int ycnt=unique(y+1,y+n+1)-(y+1);//for(int i=1;i<=ycnt;i++) printf("%d\n",y[i]);
	for(int i=1;i<=n;i++)
		b[i].x=lower_bound(x+1,x+xcnt+1,bx[i])-x,b[i].y=lower_bound(y+1,y+ycnt+1,by[i])-y;//printf("%d %d\n",b[i].x,b[i].y);}
	sort(b+1,b+n+1,cmp1);//line
	lcnt=rcnt=0;
	for(int i=1;i<=n;i++){
		int j=i+1;
		if(b[i].x==b[j].x&&b[i].y+1<=b[j].y-1)
		line[++lcnt]=Line(b[i].y+1,b[j].y-1,b[i].x);
	}
	sort(b+1,b+n+1,cmp2);//row
	for(int i=1;i<=n;i++){
		int j=i+1;
		if(b[i].y==b[j].y&&b[i].x+1<=b[j].x-1)
		row[++rcnt]=Line(b[i].x+1,b[j].x-1,b[i].y);
	}
	sort(line+1,line+lcnt+1,cmp3);
	sort(row+1,row+rcnt+1,cmp4);
	for(int i=1;i<=lcnt;i++) eline[i]=line[i];
	sort(eline+1,eline+lcnt+1,cmp5);
	int ll=1,rr=1,ell=1;
	seq.init();
	for(int i=1;i<=ycnt;i++){
		while(line[ll].st==i){
			seq.update(1,1,xcnt,line[ll].pos,1);ll++;
		}
		while(eline[ell].ed+1==i){
			seq.update(1,1,xcnt,eline[ell].pos,-1);ell++;
		}
		while(row[rr].pos==i){
			ans+=seq.query(1,1,xcnt,row[rr].st,row[rr].ed);
			rr++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*
5
2 4
3 3
1 5
6 2
2 7
*/
