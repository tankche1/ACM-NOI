# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxl=10;
LL dp[maxl+1][maxl+1];
LL power[maxl+1];

void _Dp(){
	power[0]=1;
	for(int i=1;i<=10;i++) power[i]=power[i-1]*10;
	for(int j=0;j<10;j++)
		dp[1][j]=1;
	for(int i=2;i<=maxl;i++){
		for(int j=0;j<10;j++){
			dp[i][j]=0;
			for(int k=0;k<10;k++)
				if(abs(j-k)>=2) dp[i][j]+=dp[i-1][k];
			//printf("dp[%d][%d]:%d\n",i,j,dp[i][j]);
		}
	}
}
LL a,b;

LL Count(LL x){
	//printf("x:%lld\n",x);
	LL sum=0;
	bool first=true;
	int last=-1;
	for(int i=maxl;i>=1;i--){
		if((!first)||x/power[i-1]>0){
			if(first){
				for(int j=1;j<i;j++)
					for(int k=1;k<=9;k++)
						sum+=dp[j][k];
			}
			//if(first) sum-=dp[i][0];
			int num=x/power[i-1];
			for(int j=first?1:0;j<num;j++){
				if(last==-1||abs(j-last)>=2){
					sum+=dp[i][j];
				}
			}
			if(last!=-1&&abs(num-last)<2) break;
			if(i==1) sum++;
			last=num;
			x-=num*power[i-1];first=false;
			//printf("i:%d sum:%d\n",i,sum);
		}
	}
	return sum;
}

int main(){
	_Dp();
	scanf("%lld%lld",&a,&b);
	printf("%lld\n",Count(b)-Count(a-1));
	return 0;
}
