# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=100010;
int dp[maxn];
int n;

struct tank{
	int a,b,num,key;
	tank() {}
	tank(int a,int b,int num):a(a),b(b),num(num) {}
};
set<tank> s;

bool operator< (const tank &A,const tank &B){
	if(A.a!=B.a) return A.a<B.a;
	return A.b<B.b;
}

tank T[maxn];

set<tank> ::iterator it;
int ans=0;
int now;
int track[maxn];

void dfs(int x){
	if(!x) return;
	printf("%d ",T[x].key);
	dfs(track[x]);
}
int main()
{
	//freopen("people.in","r",stdin);
	//freopen("people.out","w",stdout);
	int j;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&T[i].a,&T[i].b),T[i].key=i;
	sort(T+1,T+n+1);
	/*puts("");
	for(int i=1;i<=n;i++)
		printf("%d %d\n",T[i].a,T[i].b);*/
	for(int i=1;i<=n;i++) T[i].num=i;
	s.insert(tank(0,0,0));
	memset(track,0,sizeof(track));
	for(int i=1;i<=n;i++){
		for(j=i;j<n&&T[j+1].a==T[j].a;j++);
		for(int k=i;k<=j;k++){
			it=s.lower_bound(tank(T[k].b,0,0));
			it--;
			track[k]=it->num;
			dp[k]=it->b+1;
			if(dp[k]>ans) ans=dp[k],now=k;
		}
		for(int k=i;k<=j;k++){
			it=s.lower_bound(tank(T[k].b,dp[k],0));
			if(it->a==T[k].b&&it->b>=dp[k]) continue;
			it--;
			if(it->b>=dp[k]) continue;
			s.insert(tank(T[k].b,dp[k],T[k].num));
			it=s.find(tank(T[k].b,dp[k],T[k].num));
			it--;
			while(it!=s.begin()&&!(it->a<T[k].b&&it->b>dp[k])) s.erase(it),it--;
			it=s.find(tank(T[k].b,dp[k],T[k].num));
			it++;
			while(it!=s.end()&&!(it->a>T[k].b&&it->b>dp[k])) s.erase(it),it++;
		}
		i=j;
	}
	printf("%d\n",ans);
	dfs(now);puts("");
	return 0;
}
