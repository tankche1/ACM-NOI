# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxnode=maxn*33;
int n;
int first[maxn],next[maxn<<1],v[maxn<<1],w[maxn<<1],edge;
int dist[maxn];
int two[33];

struct Trie{
	int ch[maxnode][2],sz;
	
	void init(){
		sz=0;
		ch[0][0]=ch[0][1]=0;
	}
	
	void insert(int num){
		int u=0,j;
		//printf("insert:%d\n",num);
		j=30;
		for(int pos=j;pos>=0;pos--){
			int go=(num&two[pos])?1:0;
			//printf("%d",go);
			if(!ch[u][go]){
				ch[u][go]=++sz;memset(ch[sz],0,sizeof(ch[sz]));
			}
			u=ch[u][go];
			//if(go) printf("go:%d\n",pos);
			//if(go) num^=two[j];
		}
		//val[u]=1;
	}
	
	int Renew(int val){
		int u=0,go;
		//printf("val:%d\n",val);
		int ans=0;//printf("val:%d\n",val);
		for(int j=30;j>=0;j--){
			if(val&two[j]) go=0;else go=1;
			if(ch[u][go])
				u=ch[u][go],ans^=two[j];//printf("j:%d go:%d\n",j,go);
			else
				u=ch[u][!go];
		}
		//printf("val:%d ans:%d\n",val,ans);
		return ans;
	}
	
}trie;

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}

int ans=0;

void dfs(int x,int fa){
	if(trie.sz) ans=max(ans,trie.Renew(dist[x]));
	trie.insert(dist[x]);
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa) continue;
		dist[v[e]]=dist[x]^w[e];
		dfs(v[e],x);
	}
}

int main(){
	int a,b,c;
	two[0]=1;for(int i=1;i<=31;i++) two[i]=two[i-1]<<1;
	while(scanf("%d",&n)!=EOF){
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++)
		scanf("%d%d%d",&a,&b,&c),add_edge(a,b,c),add_edge(b,a,c);
	dist[1]=0;
	trie.init();ans=0;
	dfs(1,0);
	printf("%d\n",ans);
}
	return 0;
}
