#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef unsigned long long LL;
//typedef long long int;
const int mod=10000007;
const int Step=61;
LL n;
LL C[62][62];

void init(){
	C[0][0]=1;
	C[1][0]=C[1][1]=1;
	for(LL i=2;i<=Step;i++){
		C[i][0]=1;
		for(LL j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j]);
	}
}

/*LL pow(LL a,LL b){
	if(a==0) return 1;
	if(b==0) return 1;
	LL half=pow(a,b>>1);
	if(b&1) return ((half*half)%mod)*a%mod;
	else return half*half%mod;
}*/
LL pow(LL a,LL b){
	if(a==0) return 1;
	if(b==0) return 1;
	LL res=a,ans=1;
	while(b){
		if(b&1) ans=(ans*res)%mod;
		b>>=1;res=(res*res)%mod;
	}
	return ans;
}

LL getans(LL x,LL num){
		//printf("x:%lld num:%d\n",x,num);
	if(x==0) return num;
	
	LL j;
	for(j=Step;j>=0;j--){
		if((x>>j)&1) break;
	}
	LL ans=1;
	for(LL k=0;k<=j;k++)
		ans=(ans*pow(k+num,C[j][k]))%mod;
	//printf("x:%lld num:%d ans:%lld \n",x,num,ans%mod);
	return ans*getans(x^(LL)((LL)1<<j),num+1)%mod;
}

int main(){
		//freopen("input.txt","r",stdin);
	//freopen("output.b","w",stdout);
	init();
	scanf("%lld",&n);//printf("%lld\n",n);
		printf("%lld\n",getans(n,0));
	return 0;
}
//1000000000000000
