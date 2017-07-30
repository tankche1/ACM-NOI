# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=60;
const int INF=~0U>>1;
char s[maxn];
int dp[maxn][maxn][2];

bool fuck(char *a,char *b,int p){
	for(int i=0;i<p;i++) if(a[i]!=b[i]) return false;
		return true;
}

int dfs(int L,int R,bool P){//s[L-1]是M 从L到R 能否放M 的最短
	if(dp[L][R][P]!=-1) return dp[L][R][P];
	int &ans=dp[L][R][P];
	ans=INF;
	int len=R-L+1;
	if(len==1) return ans=1;
	if(P) for(int k=L;k<R;k++) ans=min(ans,dfs(L,k,1)+1+dfs(k+1,R,1));
	for(int k=L;k<R;k++) ans=min(ans,dfs(L,k,P)+R-k);
	if((len)%2==0&&fuck(s+L,s+L+len/2,len/2)) ans=min(ans,1+dfs(L,L+len/2-1,0));
	return ans;
}

int main(){
	scanf("%s",s+1);
	s[0]='0';
	int n=strlen(s)-1;
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(1,n,1));
	return 0;
}
