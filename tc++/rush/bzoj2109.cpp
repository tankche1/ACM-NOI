# include<stdio.h>
# include<string.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=2010;
const int maxm=10010;
int n,m;
int first[maxn],next[maxm<<1],v[maxm<<1],edge;
int in[maxn];
int num[maxn];
int ans[maxn];
int k[maxn];
int dp[maxn];
vector<int> son;

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

queue<int> Q;
int bh[maxn];
bool vis[maxn];

bool cmp(int a,int b){return k[a]<k[b];}


int dfs(int x){
	vis[x]=true;
	son.push_back(x);
	int num=1;
	for(int e=first[x];e!=-1;e=next[e])
		if(!vis[v[e]]) num+=dfs(v[e]);
	return num;
}

int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	edge=0;memset(first,-1,sizeof(first));memset(in,0,sizeof(in));
	for(int i=1;i<=n;i++){
		scanf("%d",&k[i]);k[i]=min(k[i],n);bh[i]=i;
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);//G[a].push_back(b);
		in[a]++;
		add_edge(b,a);
	}
	
	for(int i=1;i<=n;i++){
		if(!in[i]) Q.push(i);
	}
	
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		//printf("x:%d k:%d\n",x,k[x]);
		for(int e=first[x];e!=-1;e=next[e]){
			k[v[e]]=min(k[v[e]],k[x]-1);
			if(--in[v[e]]==0) Q.push(v[e]);
		}
	}
	
	sort(bh+1,bh+n+1,cmp);
	for(int i=1;i<=n;i++) printf("%d ",bh[i]);puts("");
		
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++)
		num[k[i]]++;
	for(int i=1;i<=n;i++)
		num[i]+=num[i-1];
//	for(int i=1;i<=n;i++) printf("%d\n",k[i]);
	
	for(int i=1;i<=n;i++){
		son.clear();memset(vis,0,sizeof(vis));
		dfs(i);
		sort(son.begin(),son.end(),cmp);
		//printf("i:%d\n",i);
		//for(int i=0;i<son.size();i++) printf("son:%d ",son[i]);puts("");
		int cnt=son.size(),j;
		for(j=n;j>=1;j--){
			while(cnt>0&&k[son[cnt-1]]>j) cnt--;
			if(j-num[j]>=son.size()-cnt) continue;
			else {printf("%d ",j+1);break;}
		}
		if(!j) printf("%d ",1);
	}puts("");
	return 0;
}
