# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
inline int lowbit(int x) {return x&(-x);}
int n;
int C[maxn];
int dp[maxn];

void init(){
	memset(C,0,sizeof(C));
}

void update(int x,int v){
	while(x<=n){
		C[x]=max(C[x],v);
		x+=lowbit(x);
	}
}

int find(int x){
	int v=0;
	while(x>0){
		v=max(v,C[x]);
		x-=lowbit(x);
	}
	return v;
}

struct tank{
	int a,b,key;
	tank() {}
	tank(int a,int b):a(a),b(b) {}
};

bool operator< (const tank &A,const tank &B){
	if(A.a!=B.a) return A.a<B.a;
	return A.b<B.b;
}
tank T[maxn];

void dfs(int x){
	printf("%d ",T[x].key);
	if(dp[x]==1) return;
	for(int i=x-1;i>=1;i--)
		if(dp[i]+1==dp[x]&&T[i].a<T[x].a&&T[i].b<T[x].b){
			dfs(i);break;
	}
	return;
}

int B[maxn],B_num;

int main()
{
	freopen("people.in","r",stdin);
	freopen("people.out","w",stdout);
	int j;
	int ans=0,now;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&T[i].a,&T[i].b),T[i].key=i,B[i-1]=T[i].b;
	sort(T+1,T+n+1);
	sort(B,B+n);
	B_num=unique(B,B+n)-B;
	for(int i=1;i<=n;i++)
		T[i].b=lower_bound(B,B+B_num,T[i].b)-B+1;//,printf("%d\n",T[i].b);
	init();
	for(int i=1;i<=n;i++){
		for(j=i;j<n&&T[j+1].a==T[j].a;j++);
		for(int k=i;k<=j;k++){
			dp[k]=find(T[k].b-1)+1;
			if(dp[k]>ans) ans=dp[k],now=k;
		}
		for(int k=i;k<=j;k++){
			update(T[k].b,dp[k]);
		}
		i=j;
	}
	printf("%d\n",ans);
	dfs(now);puts("");
	return 0;
}
