# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
const int mod=1000000007;
int n;
int first[maxn],next[maxn<<1],v[maxn<<1],w[maxn<<1],edge;
int fa[maxn],size[maxn];
bool used[maxn];
inline void mo(LL &x){
	if(x>=mod) x%=mod;
}

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}

void dfs(int x){
	size[x]=1;
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa[x]) fa[v[e]]=x,dfs(v[e]),size[x]+=size[v[e]];
}
int num;

void find(int &x){
	int mx=0,k;
	for(int e=first[x];e!=-1;e=next[e]){
		if(!used[v[e]]&&mx<size[v[e]])
			mx=size[v[e]],k=v[e];
	}
	if(mx>num/2){
		size[x]-=size[k];size[k]+=x;fa[x]=k;fa[k]=0;
		x=k;
		find(x);
	}
}
typedef pair<int,int> pi;
queue<pi> Q;
int dis[maxn],cnt;
LL sum[maxn];
LL cal(int x,int dist){
	Q.push(pi(x,dist));cnt=0;
	while(!Q.empty()){
		pi now=Q.front();Q.pop();dis[cnt++]=now.second;
		for(int e=first[now.first];e!=-1;e=next[e]){
			if(!used[v[e]]&&v[e]!=fa[now.first]){
				LL aa=((now.second*w[e]));mo(aa);
				Q.push(pi(v[e],aa));
			}
		}
	}
	sum[0]=dis[0];for(int i=1;i<cnt;i++) sum[i]=sum[i-1]+dis[i],mo(sum[i]);
	LL ans=0;
	for(int i=0;i<cnt;i++)
		ans=(ans+(((sum[cnt-1]-sum[i]+mod))*dis[i])),mo(ans);
	//printf("x:%d dis:%d ans:%d\n",x,dist,ans);
	return ans;
}

LL ans=0;

void solve(int x){
	num=size[x];
	if(num==1) return;
	find(x);
	//printf("root:%d\n",x);
	ans+=cal(x,1);
	for(int e=first[x];e!=-1;e=next[e]){
		if(!used[v[e]])
		ans=(ans+mod-cal(v[e],w[e]))%mod;
	}
	used[x]=1;
	for(int e=first[x];e!=-1;e=next[e])
		if(!used[v[e]]) solve(v[e]);
}

int main(){
	int a,b,c;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++)
		scanf("%d%d%d",&a,&b,&c),add_edge(a,b,c),add_edge(b,a,c);
	fa[1]=0;
	dfs(1);solve(1);
	printf("%lld\n",ans);
	return 0;
}
