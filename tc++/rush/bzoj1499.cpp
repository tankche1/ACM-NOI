# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=210;
int n,m,k,sx,sy;
char s[maxn][maxn];

struct Duty{
	int l,r,op;
}duty[maxn];
int dp[2][maxn][maxn];
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
int q[maxn],head,tail;
int main(){
	scanf("%d%d%d%d%d\n",&n,&m,&sx,&sy,&k);
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=k;i++)
		scanf("%d%d%d",&duty[i].l,&duty[i].r,&duty[i].op),duty[i].op--;
	memset(dp,-1,sizeof(dp));
	dp[0][sx][sy]=0;
	for(int kk=1;kk<=k;kk++){
		int now=kk&1;int last=now^1;
		memset(dp[now],-1,sizeof(dp[now]));
		int t=duty[kk].r-duty[kk].l+1;
		//
		if(duty[kk].op==0){
			for(int j=1;j<=m;j++){
				head=0;tail=-1;
				for(int i=n;i>=1;i--){
					if(s[i][j]=='x') {tail=-1,head=0;continue;}
					if(dp[last][i][j]!=-1){
						while(tail>=head&&dp[last][i][j]>=dp[last][q[tail]][j]+abs(i-q[tail])) tail--;
						q[++tail]=i;
						}
					while(head<=tail&&abs(i-q[head])>t) head++;
					if(head<=tail) dp[now][i][j]=dp[last][q[head]][j]+abs(i-q[head]);
				}
			}
		}
		//
		if(duty[kk].op==1){
			for(int j=1;j<=m;j++){
				head=0;tail=-1;
				for(int i=1;i<=n;i++){
					if(s[i][j]=='x') {tail=-1,head=0;continue;}
					if(dp[last][i][j]!=-1) {while(tail>=head&&dp[last][i][j]>=dp[last][q[tail]][j]+abs(i-q[tail])) tail--;
					q[++tail]=i;}
					while(head<=tail&&abs(i-q[head])>t) head++;
					if(head<=tail) dp[now][i][j]=dp[last][q[head]][j]+abs(i-q[head]);
				}
			}
		}
		//op=2
		if(duty[kk].op==2){
			for(int i=1;i<=n;i++){
				head=0;tail=-1;
				for(int j=m;j>=1;j--){
					if(s[i][j]=='x') {tail=-1,head=0;continue;}
					if(dp[last][i][j]!=-1) {while(tail>=head&&dp[last][i][j]>=dp[last][i][q[tail]]+abs(j-q[tail])) tail--;
					q[++tail]=j;}
					while(head<=tail&&abs(j-q[head])>t) head++;
					if(head<=tail) dp[now][i][j]=dp[last][i][q[head]]+abs(j-q[head]);
				}
			}
		}
		//op=3
		if(duty[kk].op==3){
			for(int i=1;i<=n;i++){
				head=0;tail=-1;
				for(int j=1;j<=m;j++){
					if(s[i][j]=='x') {tail=-1,head=0;continue;}
					if(dp[last][i][j]!=-1) {while(tail>=head&&dp[last][i][j]>=dp[last][i][q[tail]]+abs(j-q[tail])) tail--;
					q[++tail]=j;}
					while(head<=tail&&abs(j-q[head])>t) head++;
					if(head<=tail) dp[now][i][j]=dp[last][i][q[head]]+abs(j-q[head]);
				}
			}
		}
		/*for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++) printf("%d ",dp[now][i][j]);puts("");
			}puts("");*/
	}
	int ans=-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ans=max(ans,dp[k% 2][i][j]);
		printf("%d\n",ans);
	return 0;
}
