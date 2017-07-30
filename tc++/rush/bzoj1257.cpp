# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int n,k;
int main(){
	scanf("%d%d",&n,&k);
	LL sum=(LL)n*k;
	for(int i=1;i<=n;i++){
		int x=k/i;
		int L=i,R=n;
		while(L<=R){
			int M=(L+R)>>1;
			if(k/M>=x) L=M+1;
				else R=M-1;
		}
		int y=L-1;
		sum-=(LL)(y-i+1)*(y+i)/2*x;
		i=y;
	}
	printf("%lld\n",sum);
	return 0;
}
