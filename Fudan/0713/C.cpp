# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=510;
typedef long long LL;
int mod=1000000009;
int n,k;

struct tank{
	int val,op;
	tank() {}
	bool operator < (const tank &rhs)const{
		return val<rhs.val;
	}
}t[maxn<<1];
LL dp[2][maxn][maxn];

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		t[i].op=1;scanf("%d",&t[i].val);
	}
	for(int i=n+1;i<=n+n;i++){
		t[i].op=2;scanf("%d",&t[i].val);
	}
	sort(t+1,t+n+n+1);
	if((n+k)&1){
		puts("0");return 0;
	}
	
	int s1=0,s2=0,now,to,t1,t2;
	memset(dp,0,sizeof(dp));
	dp[0][0][0]=1;
	for(int i=0;i<2*n;i++){
		now=i%2;to=now^1;
		for(int j=0;j+j<=i;j++)
			for(int g=0;j+g+j+g<=i;g++){
				if(dp[now][j][g]==0) continue;
				t1=s1-j-g;t2=s2-j-g;
				//拿来输
				dp[to][j][g]=(dp[now][j][g]+dp[to][j][g])%mod;
				//win
				if(t[i+1].op==1){
					dp[to][j+1][g]=(dp[to][j+1][g]+dp[now][j][g]*t2)%mod;
				}
				else{
					dp[to][j][g+1]=(dp[to][j][g+1]+dp[now][j][g]*t1)%mod;
				}
			}
		if(t[i+1].op==1) s1++;
			else s2++;
		memset(dp[now],0,sizeof(dp[now]));
	}
	int a=(n+k)/2,b=(n-k)/2;
	printf("%I64d\n",dp[(2*n)%2][a][b]);
	return 0;
}
