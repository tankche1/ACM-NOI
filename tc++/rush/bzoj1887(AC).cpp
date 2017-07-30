# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int mod=1000000007;
typedef long long LL;
int n;
int first[maxn],next[maxn<<1],v[maxn<<1],w[maxn<<1],edge;
bool vis[maxn];
LL sum[maxn];//代表此节点往下的路径之和
inline void mo(LL &x){
	if(x>=mod) x%=mod;
}

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}
int q[maxn],head,tail;

LL solve(){
	memset(vis,false,sizeof(vis));
	head=0;tail=-1;
	q[++tail]=1;
	while(head<=tail){
		int x=q[head++];vis[x]=1;
		//printf("%d\n",x);
		for(int e=first[x];e!=-1;e=next[e])
			if(vis[v[e]]) v[e]=-1;
			else{
				q[++tail]=v[e];
			}
	}
	LL ans=0;
	for(int i=tail;i>=0;i--){
		int x=q[i];
		sum[x]=0;
		for(int e=first[x];e!=-1;e=next[e])
			if(v[e]!=-1){
				//printf("x:%d v[e]:%d\n",x,v[e]);
				sum[x]+=LL(w[e]*sum[v[e]])%mod;
				sum[x]+=w[e];
				mo(sum[x]);
			}
		//	printf("sum[%d]:%d\n",x,sum[x]);
		ans+=sum[x];mo(ans);
		LL _sum=sum[x];
		for(int e=first[x];e!=-1;e=next[e])
			if(v[e]!=-1){
				LL tmp=LL(w[e]*(sum[v[e]]+1))%mod;
				_sum-=tmp;if(_sum<0) _sum+=mod;
			//		printf("tmp:%lld _sum:%lld\n",tmp,_sum);
				ans+=(tmp*_sum)%mod;
				mo(ans);
			}
			//printf("x:%d ans:%lld\n",x,ans);
	}
	return ans;
}

int main(){
	int a,b,c;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++)
		scanf("%d%d%d",&a,&b,&c),add_edge(a,b,c),add_edge(b,a,c);
	printf("%lld\n",solve());
	return 0;
}
