# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
const int mod=1000000007;
int n,m;
int a,b;
int nn,mm;
bool vn[maxn],vm[maxn<<1];
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
void add_edge(int from,int to){
	next[edge]=first[from];
	v[edge]=to;
	first[from]=edge++;
}

void dfs(int x){
	vn[x]=1;
	nn++;
	for(int e=first[x];e!=-1;e=next[e]){
		if(!vm[e]){
			vm[e]=vm[e^1]=1;mm++;
			if(!vn[v[e]]){
				dfs(v[e]);
			}
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		add_edge(b,a);
	}
	LL ans=1;
	memset(vn,0,sizeof(vn));
	memset(vm,0,sizeof(vm));
	for(int i=1;i<=n;i++){
		if(vn[i]) continue;
		nn=0;mm=0;
		dfs(i);
		if(mm>nn) ans*=0;
		else if(mm==nn) ans=(ans*2)%mod;
		else ans=(ans*nn)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
