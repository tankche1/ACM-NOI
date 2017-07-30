# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
const int mod=1000000000;
int n,f[maxn];
int main(){
	scanf("%d",&n);
	f[0]=1;
	for(int i=1;i<=n;i++){
		if(i&1) f[i]=f[i-1];
			else f[i]=(f[i-2]+f[i/2])%mod;
	}
	printf("%d\n",f[n]);
	return 0;
}
