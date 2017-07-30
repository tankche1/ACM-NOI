# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
# define lowbit(x) x&(-x)
const int maxn=200010;

struct FenwickTree{
	int n;
	long long C[maxn];
	
	void init(int n){
		this->n=n;
		memset(C,0,sizeof(C));
	}
	
	void add(int x,int d){
		while(x<=n){
			C[x]+=d;
			x+=lowbit(x);
		}
	}
	
	long long sum(int x){
		long long ans=0;
		while(x>0){
			ans+=C[x];
			x-=lowbit(x);
		}
		return ans;
	}
	
};
FenwickTree g;
int a[maxn];
int main(){
	int n;
	int kase=1;
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		if(kase!=1) printf("\n");
		printf("Case %d:\n",kase++);
		g.init(n);
		int x;
		for(int i=1;i<=n;i++){
			scanf("%d",&x);a[i]=x;
			g.add(i,x);
		}
		char c[20];
		int y;
		while(1){
			scanf("%s",c);
			if(c[0]=='E') break;
			if(c[0]=='S'){
				scanf("%d%d",&x,&y);
				g.add(x,y-a[x]);a[x]=y;
			}
			else{
				scanf("%d%d",&x,&y);
				long long ans=g.sum(y)-g.sum(x-1);
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
