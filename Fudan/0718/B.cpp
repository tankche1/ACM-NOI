# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
# define mp(a,b) make_pair(a,b)
using namespace std;
typedef long long LL;
const int maxn=50010;
int w,h,n,m;
int input[maxn][4];
struct segment{
	int x,L,R,op;
	segment(int x=0,int L=0,int R=0,int op=0):x(x),L(L),R(R),op(op) {}
	bool operator < (const segment &rhs)const{
		if(x==rhs.x) return op<rhs.op;
		return x<rhs.x;
	}
}seg[maxn<<1];
int seg_cnt=0;
LL ans=0;
set<pair<int,int> > s;
set<pair<int,int> >::iterator it;

inline int count(int l,int r){return r-l+1-m+1>0?r-l+1-m+1:0;}

void solve(){
	//puts("fuck");
	seg_cnt=0;
	for(int i=1;i<=n;i++){
		seg[++seg_cnt]=segment(input[i][0],input[i][1],input[i][3],1);
		seg[++seg_cnt]=segment(input[i][2]+1,input[i][1],input[i][3],-1);
	}
	if(seg_cnt)
		sort(seg+1,seg+seg_cnt+1);
	s.clear();s.insert(mp(0,0));s.insert(mp(h+1,h+1));
	int nownum=h-m+1,nowx,lastx=1,tr,l,r;
	for(int tl=1;tl<=seg_cnt;tl++){
		nowx=seg[tl].x;
		//printf("tl:%d nowx:%d lastx:%d\n",tl,nowx,lastx);
		for(tr=tl;tr<seg_cnt&&seg[tr+1].x==nowx;tr++);
		ans+=(LL)nownum*(LL)(nowx-lastx);
		for(int i=tl;i<=tr;i++){
			if(seg[i].op==1){
				it=s.upper_bound(mp(seg[i].L,seg[i].R));
				r=it->first-1;it--;l=it->second+1;
				//printf("l:%d r:%d L:%d R:%d \n",l,r,seg[i].L,seg[i].R);
				nownum=nownum-count(l,r)+count(l,seg[i].L-1)+count(seg[i].R+1,r);
				s.insert(mp(seg[i].L,seg[i].R));
			}
			else{
				it=s.find(mp(seg[i].L,seg[i].R));
				it++;r=it->first-1;it--;it--;l=it->second+1;
				nownum=nownum-count(l,seg[i].L-1)-count(seg[i].R+1,r)+count(l,r);
				s.erase(mp(seg[i].L,seg[i].R));
			}
		}
		lastx=seg[tl].x;tl=tr;
		//printf("nownum:%d lastx:%d\n",nownum,lastx);
	}
	//printf("lastx:%d\n",lastx);
	ans+=(LL)(w+1-lastx)*(LL)nownum;
	//puts("hei");
}

int main(){
	while(scanf("%d%d%d%d",&w,&h,&n,&m)!=EOF){
		ans=0;
		for(int i=1;i<=n;i++)
			for(int j=0;j<4;j++)
				scanf("%d",&input[i][j]);
		solve();
		if(m!=1){
			swap(w,h);
			for(int i=1;i<=n;i++) swap(input[i][0],input[i][1]),swap(input[i][2],input[i][3]);
			solve();
		}
		printf("%lld\n",ans);
	}
	return 0;
}
