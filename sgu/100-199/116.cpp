# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=10010;
int prime[maxn],prime_cnt;
int super[maxn],super_cnt;
bool vis[maxn];
int dp[maxn],last[maxn];
vector<int> ans;
int main(){
	memset(vis,false,sizeof(vis));
	vis[2]=0;prime[prime_cnt=1]=2;vis[1]=1;
	for(int i=3;i<=10000;i+=2){
		if(!vis[i]){
			//if(prime_cnt<=20) printf("i:%d\n",i);
			prime[++prime_cnt]=i;//if(prime_cnt<=20) printf("prime[%d]:%d\n",prime_cnt,i);
			for(int j=3;i*j<=10000;j+=2)
				vis[i*j]=1;
		}
	}
	
	super_cnt=0;super[super_cnt=1]=3;
	for(int i=3;i<=prime_cnt;i+=2){
		if(!vis[i]){
			super[++super_cnt]=prime[i];
			//if(super_cnt<=20)
			//	printf("supere[%d]:%d\n",super_cnt,prime[i]);
		}
	}
	
	int n;scanf("%d",&n);
	memset(dp,-1,sizeof(dp));dp[0]=0;
	for(int i=super_cnt;i>0;i--){
		if(super[i]>n) continue;
		//printf("super:%d\n",super[i]);
		for(int j=0;j+super[i]<=n;j++)
			if(dp[j]!=-1){
				if(dp[j+super[i]]==-1||dp[j]+1<dp[j+super[i]]){
					//printf("j:%d\n",j+super[i]);
					dp[j+super[i]]=dp[j]+1,last[j+super[i]]=j;
				}
			}
	}
	if(dp[n]==-1||n==0) {puts("0");return 0;}
	printf("%d\n",dp[n]);
	ans.clear();
	int x=n;
	while(x>0){
		ans.push_back(x-last[x]);
		x=last[x];
	}
	sort(ans.begin(),ans.end());
	printf("%d",ans[ans.size()-1]);
	for(int i=ans.size()-2;i>=0;i--)
		printf(" %d",ans[i]);
	puts("");
	return 0;
}
