# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int n,mod;

int Euler(int x){
	//printf("x:%d\n",x);
	int ans=x;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){//printf("i:%d\n",i);
			ans=ans/i*(i-1);
			while(x%i==0) x/=i;
		}
	}
	if(x>1) ans=ans/x*(x-1);
		return ans%mod;
}

int get_pow(int a,int b){
	int r=a%mod;
	int ans=1;
	//printf("a:%d b:%d ",a,b);
	while(b){
		if(b&1) ans=(ans*r)%mod;
		//	printf("ans:%d r:%d\n",ans,r);
		b>>=1;
		r=(r*r)%mod;
	}
	//printf(" %d\n",ans);
	return ans;
}

int main(){
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&n,&mod);
			int ans=0;
		for(int L=1;L*L<=n;L++){
			if(n%L) continue;
			ans=(ans+Euler(L)*get_pow(n,n/L-1))%mod;
			//printf("L:%d Euler(L):%d n^(n/L-1):%d\n",L,Euler(L),get_pow(n,n/L-1));
			if(L*L!=n){
				ans=(ans+(Euler(n/L))*get_pow(n,L-1))%mod;
			//printf("L:%d Euler(L):%d n^(n/L-1):%d\n",n/L,Euler(n/L),get_pow(n,L-1));
			}
		}
		printf("%d\n",ans);
	}
return 0;
}
