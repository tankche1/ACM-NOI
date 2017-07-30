#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int Step=30;
const int maxn=32;
int dp[maxn][maxn][maxn][maxn][2];
int a,b,c,n;
int A[3];
int x,y,z;
int Two[maxn];

void update(int &x,int a,int b){
	if(a==-1) return;
	if(x==-1) x=a+b;
	else x=min(x,a+b);
}
int main(){
	Two[0]=1;
	for(int i=1;i<=Step;i++) Two[i]=Two[i-1]<<1;
	scanf("%d%d%d",&A[0],&A[1],&A[2]);
	//sort(A,A+3);
	int t=0;t=max(max(max(t,A[0]),A[1]),A[2]);
	a=A[0],b=A[1],c=A[2];
	for(n=Step;n>=0;n--)
		if(t>=Two[n]) break;
	n++;
	int x=0,y=0,z=0;
	for(int i=n-1;i>=0;i--){
		if(a&Two[i]) x++;
		if(b&Two[i]) y++;
		if(c&Two[i]) z++;
	}
//	if(x+y<z) {puts("-1");return 0;}
	memset(dp,-1,sizeof(dp));
	dp[0][0][0][0][0]=0;
	for(int i=1;i<=n;i++){
		for(int a=0;a<=i&&a<=x;a++){
			for(int b=0;b<=i&&b<=y;b++){
				for(int c=0;c<=z&&c<=i;c++){
					update(dp[i][a][b][c][0],dp[i-1][a][b][c][0],0);//0+0
					if(c) update(dp[i][a][b][c][0],dp[i-1][a][b][c-1][1],Two[i-1]);//0+0
					
					if(b&&c) update(dp[i][a][b][c][0],dp[i-1][a][b-1][c-1][0],Two[i-1]);//0+1
					if(b) update(dp[i][a][b][c][1],dp[i-1][a][b-1][c][1],0);//0+1
					
					if(a&&c) update(dp[i][a][b][c][0],dp[i-1][a-1][b][c-1][0],Two[i-1]);//1+0
					if(a) update(dp[i][a][b][c][1],dp[i-1][a-1][b][c][1],0);//1+0
					
					if(a&&b&&c) update(dp[i][a][b][c][1],dp[i-1][a-1][b-1][c-1][1],Two[i-1]);//1+1
					if(a&&b) update(dp[i][a][b][c][1],dp[i-1][a-1][b-1][c][0],0);//1+1
				}
			}
		}
	}
	printf("%d\n",dp[n][x][y][z][0]);
	return 0;
}
