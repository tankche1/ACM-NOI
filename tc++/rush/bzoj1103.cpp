# include<stdio.h>
# include<string.h>
# include<stack>
# include<algorithm>
# define lowbit(x) (x&(-x))
using namespace std;
const int maxn=250010;
int first[maxn],next[maxn],v[maxn],edge=0;

struct FenwickTree{
	int c[maxn<<1],n;
	
	void init(int nn){
		n=nn;
		memset(c,0,sizeof(c));
	}
	
	void add(int x,int d){
		while(x<=n){
			c[x]+=d;
			x+=lowbit(x);
		}
	}
	
	int sum(int x){
		int res=0;
		while(x>0){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
	
};
FenwickTree f;

void add_edge(int a,int b){
	next[edge]=first[a];
	first[a]=edge;
	v[edge++]=b;
}

int n,m;
stack<int> S;
int dfs[maxn*2],dfs_clock=1;
int cur[maxn];
bool vis[maxn];
int l[maxn],r[maxn];
int main(){
	int a,b;
	char op[20];
	scanf("%d",&n);
	memset(first,-1,sizeof(first));
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);add_edge(a,b);
	}
	S.push(1);
	for(int i=1;i<=n;i++) cur[i]=first[i];
	while(!S.empty()){
		loop:
		int x=S.top();
		if(!vis[x])
		{dfs[dfs_clock]=x;vis[x]=1;l[x]=dfs_clock++;}
		if(cur[x]==first[x]) l[x]=dfs_clock-1;
			else r[x]=dfs_clock-1;
			for(int &e=cur[x];e!=-1;e=next[e]){
				S.push(v[e]);
				cur[x]=next[e];
				goto loop;
			}
		dfs[dfs_clock]=x;r[x]=dfs_clock++;
		S.pop();
	}
	//for(int i=1;i<dfs_clock;i++) printf("%d",dfs[i]);
	f.init(2*n);
	for(int i=1;i<=n;i++){
		f.add(l[i],1);f.add(r[i],-1);
	}
	scanf("%d",&m);
	for(int i=1;i<=n+m-1;i++){
		scanf("%s",op);
		if(op[0]=='A'){
			scanf("%d%d",&a,&b);
			f.add(l[b],-1);f.add(r[b],1);
		}
		else{
			scanf("%d",&a);
			int ans=f.sum(l[a])-1;
			printf("%d\n",ans);
		}
	}
	return 0;
}
