# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=38;
int A[maxn][maxn];
int best;
int ans[maxn];
int n,m;

void Swap(int a,int b){
	if(a==b) return;
	for(int i=1;i<=n+1;i++)
		swap(A[a][i],A[b][i]);
}

void dfs(int num,int count){
	if(count>=best) return;
	if(num==0){
		best=count;
		//for(int i=1;i<=n;i++) printf("%d ",ans[i]);puts("");
		return;
	}
	int result=A[num][n+1];
		for(int i=num+1;i<=n;i++){
			result^=ans[i]*A[num][i];
		}
	if(A[num][num]==1){
		ans[num]=result;
		dfs(num-1,count+result);
	}
	else{
		if(result>0) return;
		ans[num]=0;dfs(num-1,count);
		ans[num]=1;dfs(num-1,count+1);
	}
	return;
}

void gaossi(){
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			if(A[j][i]!=0){
				Swap(i,j);
			}
		}
		if(A[i][i]==0) continue;
		for(int j=i+1;j<=n;j++){
			if(A[j][i]){
				for(int k=i;k<=n+1;k++)
					A[j][k]^=A[i][k];
			}
		}
	}
	best=maxn;
	dfs(n,0);
}

int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	memset(A,0,sizeof(A));
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		A[a][b]=A[b][a]=1;
	}
	for(int i=1;i<=n;i++) A[i][n+1]=1,A[i][i]=1;
	gaossi();
	printf("%d\n",best);
	return 0;
}
