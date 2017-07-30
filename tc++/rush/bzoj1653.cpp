# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int A[12][12];
int n,sum;
int num[11];
bool vis[11];

void build(){
	A[1][1]=1;
	for(int i=2;i<=10;i++){
		A[i][1]=A[i][i]=1;
		for(int j=2;j<i;j++)
			A[i][j]=A[i-1][j-1]+A[i-1][j];
	}
}

bool dfs(int cur){
	if(cur>n){
		int tot=0;
		for(int i=1;i<=n;i++)
			tot+=A[n][i]*num[i];
		if(tot==sum){
			printf("%d",num[1]);
			for(int i=2;i<=n;i++)
				printf(" %d",num[i]);puts("");return true;
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=true;
			num[cur]=i;
			if(dfs(cur+1)) return true;
			vis[i]=false;
		}
	}
	return false;
}

int main(){
	build();
	scanf("%d%d",&n,&sum);
	memset(vis,false,sizeof(vis));
	dfs(1);
	return 0;
}
