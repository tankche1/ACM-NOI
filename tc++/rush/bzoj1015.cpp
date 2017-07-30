# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=400010;
const int maxm=200010;
int first[maxn],next[maxm*2],v[maxm*2],edge_cnt=0;

void add_edge(int x,int y){
	next[edge_cnt]=first[x];
	v[edge_cnt]=y;
	first[x]=edge_cnt++;
}

int p[maxn];
int find(int x){
	int fa=p[x];
	while(p[fa]!=fa) fa=p[fa];
	int pa=x,y;
	while(p[pa]!=fa){
		y=p[pa];
		p[pa]=fa;
		pa=y;
	}
	return p[x];
}

bool p_union(int x,int y){
	int px=find(x),py=find(y);
	if(px==py) return false;
	p[px]=py;
	return true;
}

int n,m,K;
int ans[maxn];
int del[maxn];
bool vis[maxn];
int main(){
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y);add_edge(y,x);
	}
	scanf("%d",&K);
	memset(vis,true,sizeof(vis));
	for(int i=1;i<=K;i++) {scanf("%d",&del[i]);vis[del[i]]=false;}
	int num=0;
	for(int i=0;i<n;i++) p[i]=i;
	for(int i=0;i<n;i++)
		if(vis[i]){num++;
			for(int e=first[i];e!=-1;e=next[e]){
				if(vis[v[e]]){
					if(p_union(i,v[e])) num--;
				}
			}
		}
		ans[0]=0;ans[++ans[0]]=num;
		for(int i=K;i>=1;i--){
			vis[del[i]]=true;num++;
			for(int e=first[del[i]];e!=-1;e=next[e])
				if(vis[v[e]])
					if(p_union(del[i],v[e])) num--;
			ans[++ans[0]]=num;
		}
		
		for(int i=ans[0];i>0;i--)
			printf("%d\n",ans[i]);
	return 0;
}
