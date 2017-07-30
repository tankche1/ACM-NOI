# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
bool vis[12];
int a[12][12],now,ans;

void dfs(int x){
	if(x==12) {ans=max(ans,now);return;}
	for(int i=1;i<=11;i++)
		if(!vis[i]&&a[i][x]){
			vis[i]=1;now+=a[i][x];dfs(x+1);vis[i]=0;now-=a[i][x];
		}
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--){
		for(int i=1;i<=11;i++)
			for(int j=1;j<=11;j++)
				scanf("%d",&a[i][j]);
		memset(vis,0,sizeof(vis));now=0;
		ans=0;
		dfs(1);
		printf("%d\n",ans);
	}
	return 0;
}
