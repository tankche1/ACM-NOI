# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=10;
const int maxm=210;
int first[maxn],next[maxm],u[maxm],v[maxm],bh[maxm],edge=0;
bool face[maxm];
bool nouse[maxm];
int n=7,m;
int du[maxn];
vector<int> ans;
int bian=0;

inline void dfs(int x){
	//printf("x:%d\n",x);
	for(int e=first[x];e!=-1;e=next[e]){
		if(!nouse[e]){
			nouse[e]=nouse[e^1]=1;
			dfs(v[e]);
			ans.push_back(e);bian++;
		}
	}
}

void add_edge(int a,int b,int num,bool fac){
	next[edge]=first[a];
	u[edge]=a;v[edge]=b;bh[edge]=num;face[edge]=fac;
	nouse[edge]=false;
	first[a]=edge++;
}

int main(){
	int a,b;
	scanf("%d",&m);memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&a,&b),add_edge(a,b,i,1),add_edge(b,a,i,0),du[a]++,du[b]++;
	int jishu=0,st=-1;
	for(int i=0;i<n;i++)
		if(du[i]%2==1) jishu++;
	if(jishu==0||jishu==2){
		for(int i=0;i<n;i++)
			if(du[i]&1) st=i;
				else if(st==-1&&du[i]) st=i;
		dfs(st);
		if(bian!=m) puts("No solution");
			else
		for(int i=ans.size()-1;i>=0;i--)
			printf("%d %c\n",bh[ans[i]],face[ans[i]]==1?'+':'-');
	}
	else puts("No solution");
	
	return 0;
}
