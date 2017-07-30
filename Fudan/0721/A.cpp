# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;

int digit[20],cnt;
LL dp[20][20][3600];

LL dfs(int len,int o,int num,bool limit){//第len位 支点为o 目前力矩为num 
	if(len<=0) return num==0;
	if(num<0) return 0;
	if(!limit&&dp[len][o][num]!=-1) return dp[len][o][num];
	LL res=0;
	int to=limit==1?digit[len]:9,nextnum;
	for(int i=0;i<=to;i++){
		nextnum=num+i*(len-o);
		res+=dfs(len-1,o,nextnum,limit&&i==to);
	}
	if(!limit) dp[len][o][num]=res;
	return res;
}

LL solve(LL x){
	cnt=0;
	while(x) digit[++cnt]=x%10,x/=10;
	LL ans=0;
	for(int i=1;i<=cnt;i++)
		ans+=dfs(cnt,i,0,1);
	return ans-(cnt-1);
}

int main(){
	LL x,y;
	int tcase;
	scanf("%d",&tcase);
	memset(dp,-1,sizeof(dp));
	while(tcase--){
		scanf("%I64d%I64d",&x,&y);
		LL ans=solve(y);
		if(x) ans-=solve(x-1);
		printf("%I64d\n",ans);
	}
	return 0;
}
