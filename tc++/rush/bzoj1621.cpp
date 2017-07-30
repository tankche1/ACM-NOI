# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
int n,k;
map<int,int> f;

int dfs(int x){
	if(x<=k||((x+k)&1)) return 1;
	if(f.count(x)) return f[x];
		
	f[x]=dfs((x-k)/2)+dfs((x+k)/2);
	return f[x];
}

int main(){
	scanf("%d%d",&n,&k);
	printf("%d\n",dfs(n));
	return 0;
}
