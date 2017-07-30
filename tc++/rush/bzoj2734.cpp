#include<stdio.h>
#include<string.h>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int Step=17;
const int mod=1000000001;
typedef long long LL;
LL dp[2][1<<18];
int n;
bool vis[maxn];
int A[Step+3][Step+3];
LL ans=1;
LL Two[35];

void update(LL &x,LL y){
	x+=y;if(x>=mod) x-=mod;
}

int get(int k,int c){
	return (k>>(c-1))&1;
}

void solve(int x){
	int c=1;
	memset(A,0,sizeof(A));
	A[1][1]=x;vis[x]=1;
	int row,col;
	for(row=1;row;row++){
		if(row!=1) {A[row][1]=A[row-1][1]*3;if(A[row][1]>n) {A[row][1]=0;row--;break;}vis[A[row][1]]=1;}
		for(col=2;;col++){
			A[row][col]=A[row][col-1]<<1;
			if(A[row][col]>n) {A[row][col]=0;break;}
			vis[A[row][col]]=1;
		}
		if(row==1) c=col-1;
	}
	
	int M=(1<<(c))-1;for(int j=0;j<=M;j++) dp[1][j]=0;
	dp[1][0]=1;int now=1;
	
	for(int i=1;i<=row;i++)
		for(int j=1;j<=c;j++){
			for(int j=0;j<=M;j++)
				dp[now^1][j]=0;
			for(int k=0;k<Two[c];k++)
				if(dp[now][k]){
					update(dp[now^1][(k<<1)&M],dp[now][k]);
					if(A[i][j]&&j==1&&!get(k,c)) update(dp[now^1][(k<<1|1)&M],dp[now][k]);
					if(A[i][j]&&j!=1&&!get(k,c)&&!get(k,1)) update(dp[now^1][(k<<1|1)&M],dp[now][k]);
				}
			now^=1;
		}
	LL res=0;
	for(int j=0;j<=M;j++)
		res+=dp[now][j];//,printf("j:%d dp:%d\n",j,dp[now][j]);
	res%=mod;
	ans=ans*res%mod;
}

int main(){
	Two[0]=1;
	for(int i=1;i<=30;i++) Two[i]=Two[i-1]<<1;
		
	scanf("%d",&n);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		if(!vis[i])
			solve(i);
	printf("%lld\n",ans);
	return 0;
}
