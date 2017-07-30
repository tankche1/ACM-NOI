# include<stdio.h>
# include<string.h>
# include<stack>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=70;
LL dp[maxn][maxn];
int num[maxn][maxn];
int n,m;
stack<int> tower[maxn];
bool ocu[maxn];

void Move(int an,int am,int st,int ed){
	if(an==1){
		if(tower[ed].size()) printf("move %d from %d to %d atop %d\n",tower[st].top(),st,ed,tower[ed].top());
		else printf("move %d from %d to %d\n",tower[st].top(),st,ed);
		tower[ed].push(tower[st].top());tower[st].pop();
		return;
	}
	int To;
	for(int i=1;i<=m;i++)
		if(!ocu[i]&&i!=st&&i!=ed)
		{To=i;break;}
	Move(num[an][am],am,st,To);
	ocu[To]=1;
	Move(an-num[an][am],am-1,st,ed);
	ocu[To]=0;
	Move(num[an][am],am,To,ed);
}

int main()
{
	freopen("hanoi.in","r",stdin);
	freopen("hanoi.out","w",stdout);
	//freopen("input.txt","r",stdin);
	//freopen("output.a","w",stdout);
	scanf("%d%d",&n,&m);
	memset(dp,-1,sizeof(dp));
	for(int i=2;i<=m;i++) dp[1][i]=1;
	for(int i=2;i<=n;i++)
		for(int j=2;j<=m;j++){
			
			for(int x=1;x<i;x++){
				if(dp[x][j]==-1||dp[i-x][j-1]==-1) continue;
				if(0<dp[i][j]-dp[i-x][j-1]-dp[x][j]-dp[x][j]||dp[i][j]==-1){
					dp[i][j]=2*dp[x][j]+dp[i-x][j-1];num[i][j]=x;
				}
			}
			//printf("dp[%d][%d]:%I64d\n",i,j,dp[i][j]);
		}
	printf("%llu\n",dp[n][m]);
	for(int i=n;i>=1;i--)
		tower[1].push(i);
	memset(ocu,0,sizeof(ocu));
	Move(n,m,1,m);
	return 0;
}
