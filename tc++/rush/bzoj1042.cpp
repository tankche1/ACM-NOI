# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxs=100010;
typedef long long LL;
int money[4],tot,d[4],s;
LL dp[maxs];

void getDP(){
	memset(dp,0,sizeof(dp));
	dp[0]=1;
	for(int i=0;i<4;i++)
		for(int j=0;j+money[i]<maxs;j++)
			if(dp[j])
				dp[j+money[i]]+=dp[j];
	//for(int i=0;i<=20;i++) printf("dp[%d]:%lld\n",i,dp[i]);
}

LL Fn(int x){
	if(x<0) return 0;
		return dp[x];
}
int a[4]={1,2,4,8};
int main(){
	for(int i=0;i<4;i++) scanf("%d",&money[i]);
	scanf("%d",&tot);
	getDP();
	LL ans;
	for(int i=0;i<tot;i++){
		for(int l=0;l<4;l++) scanf("%d",&d[l]);
		scanf("%d",&s);
		ans=0;
		for(int l=0;l<16;l++){
			int num=0,op;
			for(int j=0;j<4;j++) if((l&a[j])==a[j]) num++;
			if(num%2==1) op=-1;else op=1;
			int sum=s;
			for(int j=0;j<4;j++)
				if(l&a[j]){
					sum-=money[j]*(d[j]+1);
					//printf("j:%d sum:%d money:%d cishu:%d \n",j,sum,money[j],d[j]+1);
				}
			ans+=op*Fn(sum);
			//printf("l:%d sum:%d ans:%lld num:%d\n",l,sum,ans,num);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
