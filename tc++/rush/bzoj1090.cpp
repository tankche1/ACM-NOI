# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
const int INF=~0U>>1;
char s[maxn];
int dp[maxn][maxn];

bool Repeat(int start,int end,int len){
	if((end-start+1)%len) return false;
	for(int i=start+len;i<=end;i++)
		if(s[i]!=s[i-len]) return false;
	return true;
}

int dfs(int left,int right){
	if(dp[left][right]!=-1) return dp[left][right];
	if(left==right) return 1;
	int &ans=dp[left][right];ans=INF;
	for(int i=left;i<right;i++) ans=min(ans,dfs(left,i)+dfs(i+1,right));
	for(int len=1;len<(-left+right+1);len++){
		if(Repeat(left,right,len)) ans=min(ans,dfs(left,left+len-1)+2+(((right-left+1)/len)>9?((right-left+1)>=100?3:2):1));
	}
	//printf("left:%d right:%d ans:%d\n",left,right,ans);
	return ans;
}

int n;
int main(){
	scanf("%s",s+1);
	s[0]='0';
	n=strlen(s)-1;
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(1,n));
	return 0;
}
