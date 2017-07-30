#include<stdio.h>
# include<string>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1800;
const int maxm=3510;
const int INF=~0U>>2;
char str[510];
int n,m,N;
int digit[maxn];
string s[11];
int val[11][11];
int size[10];
int dp[maxn][maxm][2];
int nmatch=0;
int len;

void prepare(){
	s[0]="1110111";
	s[1]="0010010";
	s[2]="1011101";
	s[3]="1011011";
	s[4]="0111010";
	s[5]="1101011";
	s[6]="1101111";
	s[7]="1010010";
	s[8]="1111111";
	s[9]="1111011";
	s[10]="0000000";
	memset(val,0,sizeof(val));
	for(int i=0;i<=10;i++){
		for(int j=0;j<=10;j++)
			for(int k=0;k<7;k++)
				if(s[i][k]!=s[j][k])
					val[i][j]++;
				size[i]=0;
				for(int j=0;j<7;j++)
					size[i]+=s[i][j]-'0';
				//printf("%d\n",size[i]);
	}
}

int dfs(int n,int s,bool t){
	if(s>nmatch) return dp[n][s][t]=INF;//必须要赋值 不然pint时以为是-1会出错
	if(dp[n][s][t]!=-1) return dp[n][s][t];
	int &ans=dp[n][s][t];ans=INF;
	if(n==0){
		//printf("0 %d %d\n",s,t);
		if(s==nmatch) return ans=0;
		return ans;
	}
	if(n>len){
		for(int i=7;i>=1;i-=6){
			ans=min(ans,dfs(n-1,s+size[i],false)+val[i][digit[n]]);
			//printf("i:%d ans:%d\n",i,dfs(n-1,s+size[i],false)+val[i][digit[n]]);
		}
	}
	else{
		for(int i=9;i>=0;i--){
			ans=min(ans,dfs(n-1,s+size[i],false)+val[i][digit[n]]);
			//printf("i:%d %d\n",i,dfs(n-1,s+size[i],false)+val[i][digit[n]]);
		}
	}
	if(t)
		ans=min(ans,dfs(n-1,s,t));
	//printf("dp[%d][%d][%d]:%d\n",n,s,t,dp[n][s][t]);
	return ans;
}

void print(int n,int s,int t,int rest){
	if(n==0) return;
	if(n>len){
		for(int i=7;i>=1;i-=6)
			if(dp[n-1][s+size[i]][0]+val[i][digit[n]]<=rest){
				printf("%d",i);
				print(n-1,s+size[i],0,rest-val[i][digit[n]]);
				return;
			}
	}
	else{
		for(int i=9;i>=0;i--)
			if(dp[n-1][s+size[i]][0]+val[i][digit[n]]<=rest){
				printf("%d",i);
				print(n-1,s+size[i],0,rest-val[i][digit[n]]);return;
			}
	}
	if(t)
		print(n-1,s,t,rest);
	return;
}

int main(){
	prepare();
	scanf("%s",str);scanf("%d",&m);
	m=min(m,2500);
	n=strlen(str);len=n;
	for(int i=1;i<=n;i++)
		digit[i]=str[n-i]-'0',nmatch+=size[digit[i]];
	//printf("nmatch:%d\n",nmatch);
	N=n+m/2;
	for(int i=n+1;i<=N;i++)
		digit[i]=10;
	memset(dp,-1,sizeof(dp));
	dfs(N,0,1);
	print(N,0,1,2*m);puts("");
	return 0;
}
