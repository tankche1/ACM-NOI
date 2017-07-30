#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=1210;
const int maxm=1510;
char s[maxn],word[maxm];
int m;
int ans=0;
int dp[maxn][maxm][2];
const int mod=1000000007;
queue<int> Q;
int f[maxn][maxm];

struct ACmachine{
	int ch[maxm][10];
	int val[maxm];
	int sz;
	int f[maxm],last[maxm];
	
	void init() {val[0]=0;memset(ch[0],0,sizeof(ch[0]));sz=0;}
	void insert(char *s){
		int n=strlen(s),u=0;
		for(int i=0;i<n;i++){
			int c=s[i]-'0';
			if(!ch[u][c]){
				ch[u][c]=++sz;memset(ch[sz],0,sizeof(ch[sz]));val[sz]=0;
			}
			u=ch[u][c];
		}
		//printf("u:%d\n",u);
		val[u]=1;
	}
	
	void get_Fail(){f[0]=0;
		for(int c=0;c<10;c++)
			if(ch[0][c]){
				f[ch[0][c]]=0;Q.push(ch[0][c]);
			}
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			for(int c=0;c<10;c++){
				int u=ch[x][c];
				if(!u) {ch[x][c]=ch[f[x]][c];continue;}
				Q.push(u);
				int r=f[x];
				while(r&&!ch[r][c]) r=f[r];
				f[u]=ch[r][c];
				val[u]=val[u]|val[f[u]];
				//printf("f[%d]:%d\n",u,f[u]);
			}
		}
	}
}ac;

void update(int &x,int c){
	x=(x+c)%mod;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	scanf("%s",s+1);s[0]='a';//puts(s+1);
	int n=strlen(s)-1;
	scanf("%d",&m);//printf("%d\n",m);
	ac.init();
	for(int i=1;i<=m;i++){
		scanf("%s",word);//puts(word);
		ac.insert(word);
	}//return 0;
	ac.get_Fail();
	
	memset(f,0,sizeof(f));
	for(int i=1;i<=9;i++) if(!ac.val[ac.ch[0][i]]) f[1][ac.ch[0][i]]++;
	for(int i=1;i<n-1;i++){
		for(int j=0;j<=ac.sz;j++)
			if(f[i][j]){
				for(int v=0;v<10;v++)
					if(!ac.val[ac.ch[j][v]]) update(f[i+1][ac.ch[j][v]],f[i][j]);
			}
		}
	for(int i=1;i<n;i++)
		for(int j=0;j<=ac.sz;j++){
			//printf("f[%d][%d]:%d\n",i,j,f[i][j]);
			update(ans,f[i][j]);
		}//printf("%d\n",ans);
		
	memset(dp,0,sizeof(dp));
	for(int i=1;i<s[1]-'0';i++)
		if(!ac.val[ac.ch[0][i]]) dp[1][ac.ch[0][i]][0]++;
	if(!ac.val[ac.ch[0][s[1]-'0']]) dp[1][ac.ch[0][s[1]-'0']][1]++;
	for(int i=1;i<n;i++){
		for(int j=0;j<=ac.sz;j++){
			//printf("dp[%d][%d]: 0:%d 1:%d\n",i,j,dp[i][j][0],dp[i][j][1]);
			if(dp[i][j][1]){
				for(int v=0;v<s[i+1]-'0';v++)
					if(!ac.val[ac.ch[j][v]]) update(dp[i+1][ac.ch[j][v]][0],dp[i][j][1]);
				if(!ac.val[ac.ch[j][s[i+1]-'0']]) update(dp[i+1][ac.ch[j][s[i+1]-'0']][1],dp[i][j][1]);
			}
			if(dp[i][j][0]){
				for(int v=0;v<10;v++)
					if(!ac.val[ac.ch[j][v]]) update(dp[i+1][ac.ch[j][v]][0],dp[i][j][0]);
			}
		}
	}
	for(int j=0;j<=ac.sz;j++)
		update(ans,dp[n][j][0]),update(ans,dp[n][j][1]);
	printf("%d\n",ans);
	return 0; 
}
/*
20
3
2
3
14

*/
