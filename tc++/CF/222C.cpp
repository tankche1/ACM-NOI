#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=110;
const int maxm=20;
int n,m;
int A[maxn];
char op[maxm];
int who[maxm];
int dp[maxm][1<<maxm];

int dfs(int now,int state){
	if(now==m) return 0;
	if(dp[now][state]!=-1) return dp[now][state];
	int &ans=dp[now][state];ans=0;
	if(op[now]=='p'){
		for(int i=0;i<m;i++)
			if((state&(1<<i))==0){
				ans+=A[i]*who[now];//printf("i:%d A:%d\n",i,A[i]);
				ans+=dfs(now+1,state|(1<<i));
				break;
			}
	}
	else{
		if(who[now]==1) ans=-INF;
		else ans=INF;
		for(int i=0;i<m;i++)
			if((state&(1<<i))==0){
				if(who[now]==1) ans=max(ans,dfs(now+1,state|(1<<i)));
				else ans=min(ans,dfs(now+1,state|(1<<i)));
			}
	}
	//printf("now:%d state:%d ans:%d\n",now,state,ans);
	return ans;
}

bool cmp(int a,int b) {return a>b;}

int main(){
	char t;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&A[i]);
	sort(A,A+n,cmp);
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		while((t=getchar())&&t!='p'&&t!='b');op[i]=t;scanf("%d",&who[i]);if(who[i]==2) who[i]=-1;
	}
	//for(int i=0;i<m;i++) printf("A[%d]:%d\n",i,A[i]);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(0,0));
	return 0;
}
