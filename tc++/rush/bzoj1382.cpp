# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
typedef long long LL;

struct Event{
	int x,d,u,val;
	Event() {}
	Event(int x,int d,int u,int val):x(x),d(d),u(u),val(val) {}
};
Event E[maxn<<1];

bool cmp(Event a,Event b){
	return a.x<b.x;
}

int n;
int y_cnt,y[maxn<<1],E_cnt;

struct SegmentTree{
	int cover[maxn<<3],sum[maxn<<3];
	
	void build(){
		memset(cover,0,sizeof(cover));
		memset(sum,0,sizeof(sum));
	}
	
	void change(int o,int l,int r,int ql,int qr,int val){
		if(ql<=l&&qr>=r){
			cover[o]+=val;
			if(cover[o]>0) sum[o]=y[r]-y[l];
			else sum[o]=l+1==r?0:sum[o<<1]+sum[o<<1|1];
			return;
		}
		int M=(l+r)>>1;
		if(ql<M) change(o<<1,l,M,ql,qr,val);
		if(qr>M) change(o<<1|1,M,r,ql,qr,val);
		if(cover[o]>0) sum[o]=y[r]-y[l];
		else sum[o]=l+1==r?0:sum[o<<1]+sum[o<<1|1];
	}
};
SegmentTree seg;

int main(){
	int x1,y1,x2,y2;
	scanf("%d",&n);
	y_cnt=0;E_cnt=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		E[E_cnt++]=Event(x1,y1,y2,1);
		E[E_cnt++]=Event(x2,y1,y2,-1);
		//x[x_cnt++]=x1;x[x_cnt++]=x2;
		y[y_cnt++]=y1;y[y_cnt++]=y2;
	}
	sort(y,y+y_cnt);
	y_cnt=unique(y,y+y_cnt)-y;
	for(int i=0;i<E_cnt;i++){
		E[i].u=lower_bound(y,y+y_cnt,E[i].u)-y;
		E[i].d=lower_bound(y,y+y_cnt,E[i].d)-y;
	}
	sort(E,E+E_cnt,cmp);
	int last=E[0].x;
	LL ans=0;
	seg.build();
	for(int i=0;i<E_cnt;i++){
		//printf("x:%d u:%d d:%d val:%d\n",E[i].x,E[i].u,E[i].d,E[i].val);
		Event now=E[i];
		if(now.x!=last){
			ans+=(LL)((now.x-last)*seg.sum[1]);
			last=now.x;
			//printf("ans:%d\n",ans);
		}
		seg.change(1,0,y_cnt-1,now.d,now.u,now.val);
	}
	printf("%lld\n",ans);
	return 0;
}
