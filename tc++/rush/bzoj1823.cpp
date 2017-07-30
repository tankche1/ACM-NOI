# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=110;
# define val(c) c=='h'?1:0

struct TwoSat{
	int n;
	vector<int> G[maxn<<1];
	bool mark[maxn<<1];
	int S[maxn<<1],c;
	
	void init(int nn){
		n=nn;
		memset(mark,false,sizeof(mark));
		for(int i=0;i<2*n;i++) G[i].clear();
	}
	
	void add_edge(int x,int xval,int y,int yval){
		x=x*2+xval;y=y*2+yval;
		G[x^1].push_back(y);
		G[y^1].push_back(x);
	}
	
	bool dfs(int x){
		if(mark[x^1]) return false;
		if(mark[x]) return true;
		mark[x]=true;S[c++]=x;
		for(int i=0;i<G[x].size();i++){
			if(!dfs(G[x][i])) return false;
		}
		return true;
	}
	
	bool solve(){
		for(int i=0;i<n;i++){
			if(!mark[2*i]&&!mark[2*i+1]){
				c=0;
				if(!dfs(2*i)){
					while(c) mark[S[--c]]=false;
					if(!dfs(2*i+1)) return false;
				}
			}
		}
		return true;
	}
};
TwoSat sat;
int n,m;
char t1,t2;
int main(){
	int tcase;
	int x,y;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&n,&m);
		sat.init(n);
		for(int i=1;i<=m;i++){
			while((t1=getchar())&&t1!='h'&&t1!='m');
				scanf("%d",&x);x--;
			while((t2=getchar())&&t2!='h'&&t2!='m');
				scanf("%d",&y);y--;
			sat.add_edge(x,val(t1),y,val(t2));
		}
		if(sat.solve()) puts("GOOD");
			else puts("BAD");
	}
	return 0;
}
