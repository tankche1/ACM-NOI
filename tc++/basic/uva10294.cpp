# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;

int gcd(int a,int b){
	if(a==0) return b;
	return gcd(b%a,a);
}

int main(){
	int n,t;
	while((scanf("%d%d",&n,&t)!=EOF)&&n){
		LL a=0,b=0;
		LL pow[60];
		pow[0]=1;
		for(int i=1;i<=n;i++) pow[i]=pow[i-1]*t;
		for(int i=0;i<n;i++){
			a+=pow[gcd(i,n)];
		}
		if(n%2){
			b=(LL)n*pow[(n+1)/2];
		}
		else{
			b=(LL)n/2*(pow[n/2+1]+pow[n/2]);
		}
		printf("%lld %lld\n",a/n,(a+b)/2/n);
	}
	return 0;
}
