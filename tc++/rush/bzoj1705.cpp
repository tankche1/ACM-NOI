# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxc=105;
const int INF=10000000;

int n,c;
int h[maxn];
int dp[2][maxc];
int pre[maxc],next[maxc];
int main(){
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	for(int i=1;i<h[1];i++)
		pre[i]=INF,dp[1][i]=INF;
	for(int i=h[1];i<=100;i++){
		dp[1][i]=(i-h[1])*(i-h[1]);
		pre[i]=min(pre[i-1],dp[1][i]-c*i);//if(i<=5) printf("dp[%d][%d]:%d\n",1,i,dp[1][i]);
	}
	next[101]=INF;
	for(int i=100;i>=0;i--){
		next[i]=min(next[i+1],dp[1][i]+c*i);
	}
	for(int i=2;i<=n;i++){
		int now=i%2;//int last=!now;
		for(int j=1;j<=100;j++) dp[now][j]=INF;
		for(int j=0;j<h[i];j++) pre[j]=INF;
		for(int j=h[i];j<=100;j++){
			dp[now][j]=min(pre[j]+c*j+(j-h[i])*(j-h[i]),next[j]-c*j+(j-h[i])*(j-h[i]));
			//if(j<=5) printf("pre[%d]:%d\n",j,pre[j]);
			pre[j]=min(pre[j-1],dp[now][j]-c*j);
			//if(j<=5) printf("dp[%d][%d]:%d\n",i,j,dp[now][j]);
		}next[101]=INF;
		for(int j=100;j>=1;j--)
			next[j]=min(next[j+1],dp[now][j]+c*j);
	}
	int ans=INF;
	for(int j=h[n];j<=100;j++)
		ans=min(ans,dp[n%2][j]);
	printf("%d\n",ans);
	return 0;
}
