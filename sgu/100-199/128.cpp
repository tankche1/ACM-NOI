# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
# define mp(a,b) make_pair(a,b)
using namespace std;
const int maxn=10010;
int n;
vector<int> gx[maxn],gy[maxn];

struct point{
	int x,y;
	int bh;
	point() {}
}p[maxn];

struct Segment{
	int L,R;
	int op;
	int x;
	Segment() {}
	bool operator < (const Segment &rhs)const{
		if(x!=rhs.x) return x<rhs.x;
		return op<rhs.op;
	}
}seg[maxn<<1];
int seg_cnt=0;

bool cmp1(point a,point b){
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}

bool cmp2(point a,point b){
	if(a.y!=b.y)
	return a.y<b.y;
	return a.x<b.x;
}

bool vis[maxn];
int ans=0;

void dfs(int x,int way){
	if(vis[x])  return;
	vis[x]=1;
	if(way!=1){
		dfs(gx[x][0],1);
	}
	else{
		dfs(gy[x][0],2);
	}
	return;
}

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
	int c[20030],n;
	void init(int nn){
		n=nn;
		memset(c,0,sizeof(c));
	}
	
	int sum(int x){
		x+=10005;
		int res=0;
		while(x>0) res+=c[x],x-=lowbit(x);
		return res;
	}
	 
	void update(int x,int val){
		x+=10005;
		while(x<=n){
			c[x]+=val;x+=lowbit(x);
		}
	}
	
}fwt;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y);
	sort(p+1,p+n+1,cmp1);
	for(int i=1;i<=n;i++) p[i].bh=i;
	seg_cnt=0;
	for(int i=1;i<n;i++){
		if(p[i].x==p[i+1].x) {
			ans+=p[i+1].y-p[i].y;
			gx[i].push_back(i+1),gx[i+1].push_back(i);
			seg[++seg_cnt].op=2;seg[seg_cnt].x=p[i].x;seg[seg_cnt].L=p[i].y+1;seg[seg_cnt].R=p[i+1].y-1;
			i++;
		}
	}
	sort(p+1,p+n+1,cmp2);
	for(int i=1;i<n;i++)
		if(p[i].y==p[i+1].y){
			ans+=p[i+1].x-p[i].x;
			gy[p[i].bh].push_back(p[i+1].bh),gy[p[i+1].bh].push_back(p[i].bh);
			seg[++seg_cnt].op=1;seg[seg_cnt].x=p[i].x;seg[seg_cnt].L=seg[seg_cnt].R=p[i].y;
			seg[++seg_cnt].op=-1;seg[seg_cnt].x=p[i+1].x+1;seg[seg_cnt].L=seg[seg_cnt].R=p[i+1].y;
			i++;
		}
	
	//sort(p+1,p+n+1,cmp1);
	for(int i=1;i<=n;i++)
		if(!(gx[i].size()==1&&gy[i].size()==1)) {puts("0");return 0;}
	memset(vis,false,sizeof(vis));
	dfs(1,-1);
	for(int i=1;i<=n;i++) if(!vis[i]) {puts("0");return 0;}
	
	//puts("hei");
	fwt.init(10003+10005);
	sort(seg+1,seg+seg_cnt+1);
	int t2,t1;
	for(int i=1;i<=seg_cnt;i++){
		//printf("i:%d op:%d x:%d L:%d R:%d\n",i,seg[i].op,seg[i].x,seg[i].L,seg[i].R);
		if(seg[i].op==2){
			if(seg[i].R<=seg[i].L) continue;
			t1=fwt.sum(seg[i].L-1);t2=fwt.sum(seg[i].R);
			if(t2-t1!=0) {puts("0");return 0;}
		}
		else{
			fwt.update(seg[i].L,seg[i].op);
		}
	}
	printf("%d\n",ans);
	return 0;
}
