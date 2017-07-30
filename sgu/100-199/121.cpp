# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=105;
int n;
int first[maxn],next[maxn*maxn],col[maxn*maxn],v[maxn*maxn],edge;
int du[maxn];
vector<int> res;

void add_edge(int a,int b){
	next[edge]=first[a];v[edge]=b;col[edge]=-1;
	first[a]=edge++;
}

bool have[2];

void dfs(int x,int c){
	//printf("x:%d\n",x);
	for(int e=first[x];e!=-1;e=next[e])
		if(col[e]==-1){
			//printf("v:%d c:%d\n",v[e],c);
			col[e]=col[e^1]=c;
			dfs(v[e],!c);
			c=!c;
			//return true;
		}
	return;
}

int main(){
	int x;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=n;i++){
		while((scanf("%d",&x))&&x!=0) if(i<x) add_edge(i,x),add_edge(x,i),du[i]++,du[x]++;
	}
	for(int i=1;i<=n;i++)
		if(du[i]&1)
			dfs(i,0);
	for(int i=1;i<=n;i++)
		dfs(i,0);
	bool ans=true;
	for(int i=1;i<=n;i++){
		if(du[i]>=2){
		have[0]=have[1]=false;
		for(int e=first[i];e!=-1;e=next[e])
			have[col[e]]=1;
			if(have[0]+have[1]==1) ans=false;//,printf("i:%d\n",i);
		}
	}
	if(!ans) puts("No solution");
		else{
			for(int i=1;i<=n;i++){
				res.clear();
			for(int e=first[i];e!=-1;e=next[e])
				res.push_back(col[e]);
			for(int j=res.size()-1;j>=0;j--)
				printf("%d ",res[j]+1);
			puts("0");
			}
		}
	return 0;
}
