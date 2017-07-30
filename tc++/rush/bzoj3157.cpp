#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int mod=1000000007;
const int maxm=210;
typedef long long LL;
int n,m;
int stack[130],top=-1;
LL ans[130][maxm];
LL C[maxm][maxm];

LL power(LL a,LL b){
	if(b==0) return 1;
	LL half=power(a,b>>1);
	if(b&1) return (half*half%mod)*a%mod;
	else return (half*half%mod);
}

int main(){
	memset(C,0,sizeof(C));C[0][0]=1;
	for(int i=1;i<=200;i++) {C[i][0]=1;
		for(int j=1;j<=200;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	scanf("%d%d",&n,&m);
	while(n){
		stack[++top]=n;
		if(n&1) n^=1;
		else n>>=1;
	}stack[++top]=0;
	reverse(stack,stack+top+1);
	memset(ans[0],0,sizeof(ans[0]));
	for(int t=1;t<=top;t++){
		//printf("%d\n",stack[t]);
		if(stack[t]==stack[t-1]+1){
			LL x=stack[t];
			for(int j=0;j<=m;j++)
				ans[t][j]=(ans[t-1][j]+(power(x,j)*power(m,stack[t])%mod))%mod;
		}
		else{
			for(int a=0;a<=m;a++){
				ans[t][a]=ans[t-1][a];
				LL k=power(m,stack[t-1]);
				for(int j=0;j<=a;j++){
					ans[t][a]=(ans[t][a]+(((k*ans[t-1][j]%mod)*C[a][j]%mod)*power(stack[t-1],a-j)%mod))%mod;
				}
			}
		}
		//for(int j=0;j<=m;j++) printf("ans[%d][%d]:%d\n",t,j,ans[t][j]);
	}
	printf("%lld\n",ans[top][m]);
	return 0;
}
