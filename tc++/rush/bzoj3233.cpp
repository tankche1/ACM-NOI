#include<stdio.h>
#include<string.h>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=60;
const int maxa=100000;
vector<int> prime[maxa+1];
int A[maxn],n;
int ans=0;
int p[100010],cnt=0;
bool vis[100010];
int C[maxn];
int G[maxn][maxn];
void getprime(){
	for(int i=2;i<=maxa;i++){
		if(!vis[i]){
			p[cnt++]=i;//printf("i:%d\n",i);
			prime[i].push_back(i);
			for(int j=i+i;j<=maxa;j+=i) vis[j]=1,prime[j].push_back(i);
		}
	}
}

void dfs(int now,int res){
	if(res>=ans) return;
	if(C[now-1]==1) {ans=res;return;}
	if(now==1){
		for(int i=A[n]/2+1;i<=A[n];i++){
			C[now]=i;
			int tt=res;
			for(int j=1;j<=n;j++)
				tt+=G[now][j]/C[now],G[now+1][j]=G[now][j]%C[now];
			dfs(now+1,tt);
		}
	}
	else{
			for(int e=0;e<(int)prime[C[now-1]].size();e++){
				int p=prime[C[now-1]][e];
				C[now]=C[now-1]/p;
				int tt=res;
				for(int j=1;j<=n;j++)
					tt+=G[now][j]/C[now],G[now+1][j]=G[now][j]%C[now];
				dfs(now+1,tt);
			}
	}
}

int main(){
	scanf("%d",&n);
	getprime();
	for(int i=1;i<=n;i++){ 
		scanf("%d",&A[i]);
		for(int j=0;j<=17;j++)
			if(A[i]&(1<<j)) ans++;
	}
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++) G[1][i]=A[i];
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
