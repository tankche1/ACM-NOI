# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL mod=1000000007;
LL inverse;
bool vis[10004];
LL prime[10000],prime_cnt=0;
LL n;

void get_prime(){
	prime[++prime_cnt]=2;
	for(LL i=3;i<=10000;i+=2){
		if(!vis[i]){
			prime[++prime_cnt]=i;
			for(LL j=3;i*j<=10000;j+=2)
				vis[i*j]=1;
		}
	}
}

LL pow(LL a,LL x){
	if(x==0) return 1;
	LL half=pow(a,x>>1);
	half=half*half%mod;
	if(x&1) half=half*a%mod;
		//printf("a:%lld x:%lld half:%lld\n",a,x,half);
	return half;
}
LL b[10];

LL calc(LL N){
	LL s=1,res=0;
	for (LL i=1;i<=5;i++){
		s=s*N%mod;
		res=(res+s*b[i])%mod;
	}
	res=res*inverse%mod;
	//printf("N:%lld res:%lld\n",N,res);
	return res;
}
LL p[10004],p_cnt,m;

int main(){
	get_prime();inverse=pow(30,mod-2);//printf("inverse:%lld\n",inverse);
	b[1]=-1;b[2]=0;b[3]=10;b[4]=15;b[5]=6;
	int tcase;
	scanf("%d",&tcase);
	LL ans;
	while(tcase--){
		scanf("%lld",&n);m=n;
		p_cnt=0;
		for(LL i=1;i<=prime_cnt;i++){
			if(m%prime[i]==0){
				p[++p_cnt]=prime[i];while(m%prime[i]==0) m/=prime[i];
			}
		}
		if(m>1) p[++p_cnt]=m;
		ans=calc(n);int step;LL base,sum;
		//printf("ans:%lld\n",ans);
		for(LL i=1;i< (1<<p_cnt);i++){
			step=0;base=1;
			for(LL j=1;j<=p_cnt;j++)
				if((i>>(j-1))&1){
					step^=1;base*=p[j];
				}
			//printf("base:%lld step:%d\n",base,step);
			sum=calc(n/base);
			sum=sum*pow(base,4)%mod;
			if(step){
				ans=(ans-sum+mod)%mod;
			}
			else ans=(ans+sum)%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
