# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxlen=205;

int id(char c){
	if(c=='W') return 1;
		else if(c=='I') return 2;
			else if(c=='N') return 3;
				return 4;
}
int num[5];
bool to[60][6];
char s[maxlen];
int dp[maxlen][maxlen][5];

bool dfs(int L,int R,int goal){
	if(dp[L][R][goal]!=-1) return dp[L][R][goal];
	int &ans=dp[L][R][goal];
	if(L==R) return ans=(id(s[L])==goal);
	if(R-L==1) 
		return ans=(to[id(s[L])*10+id(s[R])][goal]);
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++){
			if(to[i*10+j][goal]){
				for(int k=L;k<R;k++)
					if(dfs(L,k,i)&&dfs(k+1,R,j)) return ans=1;
			}
		}
		return ans=0;
}

int main(){
	char op[10];
	for(int i=1;i<=4;i++)
	scanf("%d",&num[i]);
	memset(to,0,sizeof(to));
	for(int i=1;i<=4;i++){
		for(int j=1;j<=num[i];j++){
			scanf("%s",op);
			to[id(op[0])*10+id(op[1])][i]=1;
		}
	}s[0]='0';
	scanf("%s",s+1);int n=strlen(s)-1;
	char ans[5]={'0','W','I','N','G'};
	bool wrong=true;
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=4;i++){
		if(dfs(1,n,i)) {wrong=false;printf("%c",ans[i]);}
	}
	if(wrong)
		puts("The name is wrong!");
	return 0;
}
