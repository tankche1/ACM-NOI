# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=210;

struct Matching{
	int n;
	bool a[maxn][maxn];
	int ans;
	bool T[maxn];
	int left[maxn];
	
	void read(){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",&a[i][j]);
	}
	
	bool dfs(int x){
		for(int i=1;i<=n;i++){
			if(a[x][i]&&!T[i]){
				T[i]=true;
				if(!left[i]||dfs(left[i])){
					left[i]=x;
					return true;
				}
			}
		}
		return false;
	}
	
	int match(){
		memset(left,0,sizeof(left));
		ans=0;
		for(int i=1;i<=n;i++){
			memset(T,false,sizeof(T));
			if(dfs(i)) {ans++;}
		}
		return ans;
	}
};
Matching solve;

int T;
int main(){
	scanf("%d",&T);
	while(T--){
		solve.read();
		printf("%s\n",solve.match()==solve.n?"Yes":"No");
	}
	return 0;
}
