# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010,maxc=1000000;

struct IntervalTree{
	int sum[maxc<<2],addv[maxc<<2],qL,qR,n,v;
	
	void init(int n){
		this->n=n;
		memset(sum,0,sizeof(sum));
		memset(addv,0,sizeof(addv));
	}
	
	void pushdown(int o,int left,int right){
		int mid=(left+right)>>1;
		if(addv[o]){
			addv[o<<1]+=addv[o];
			addv[o<<1|1]+=addv[o];
			sum[o<<1]+=(mid-left+1)*addv[o];
			sum[o<<1|1]+=(right-mid)*addv[o];
			addv[o]=0;
		}
	}
	
	void maintain(int o){
		sum[o]=sum[o<<1]+sum[o<<1|1];
	}
	
	void update(int o,int L,int R){
		if(qL<=L&&qR>=R){
			sum[o]+=(R-L+1)*v;
			addv[o]+=v;
		}
		else{
			pushdown(o,L,R);
			int M=(L+R)>>1;
			if(qL<=M) update(o<<1,L,M);
			if(qR>M) update(o<<1|1,M+1,R);
			maintain(o);
		}
	}
	
	int query(int o,int L,int R){
		if(qL<=L&&qR>=R)
			return sum[o];
		pushdown(o,L,R);
		int M=(L+R)>>1;
		int ans=0;
		if(qL<=M) ans+=query(o<<1,L,M);
		if(qR>M) ans+=query(o<<1|1,M+1,R);
		return ans;
	}
	
	void add(int val,int L,int R){
		qL=L;qR=R;v=val;
		update(1,1,n);
}

int query(int L,int R){
	qL=L;qR=R;
	return query(1,1,n);
}

};
IntervalTree tree1,tree2;

struct City{
	int size,ymin,ymax;
	City *fa;
	
	City* find(){
		City *p=fa;
		while(p->fa!=p){
			p=p->fa;
		}
		return fa=p;
	}
};
City p[maxn];

void connect(int a,int b){
	City *px=p[a].find(),*py=p[b].find();
	if(px==py) return;
	if(px->ymin!=px->ymax){
		tree1.add(-1,px->ymin+1,px->ymax);
		tree2.add(-px->size,px->ymin+1,px->ymax);
	}
	if(py->ymin!=py->ymax){
		tree1.add(-1,py->ymin+1,py->ymax);
		tree2.add(-py->size,py->ymin+1,py->ymax);
	}
	tree1.add(1,min(px->ymin,py->ymin)+1,max(px->ymax,py->ymax));
	tree2.add(px->size+py->size,min(px->ymin,py->ymin)+1,max(px->ymax,py->ymax));
	px->fa=py;
	py->size=px->size+py->size;
	py->ymin=min(px->ymin,py->ymin);
	py->ymax=max(px->ymax,py->ymax);
}

int T,n,m;
int y[maxn];
int main(){
	//freopen("input","r",stdin);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		int x;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&x,&y[i]);
		}
		tree1.init(maxc);tree2.init(maxc);
		for(int i=1;i<=n;i++){
			p[i].fa=&p[i];
			p[i].ymin=p[i].ymax=y[i];
			p[i].size=1;
		}
		scanf("%d",&m);
		char op[20];
		int a,b;double c;
		while(m--){
			scanf("%s",op);
			if(op[0]=='r'){
				scanf("%d%d",&a,&b);a++;b++;
				connect(a,b);
			}
			else{
				scanf("%lf",&c);
				a=(int)c;
				printf("%d %d\n",tree1.query(a+1,a+1),tree2.query(a+1,a+1));
			}
		}
	}
	return 0;
}
