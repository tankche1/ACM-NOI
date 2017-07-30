# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxnode=6010;
const int mod=10007;

struct ACmachine{
	int last[maxnode],f[maxnode];
	int ch[maxnode][26];
	int val[maxnode];
	int sz;
	
	void init(){
		memset(ch[0],0,sizeof(ch[0]));
		val[0]=0;
		sz=0;
	}
	
	int id(char c){
		return c-'A';
	}
	
	void insert(char *s){
		int n=strlen(s),u=0;
		for(int i=0;i<n;i++){
			int c=id(s[i]);
			if(!ch[u][c]){
				sz++;
				memset(ch[sz],0,sizeof(ch[sz]));
				ch[u][c]=sz;
				val[sz]=0;
			}
			u=ch[u][c];
		}
		val[u]=1;
	}
	
	void getFail(){
		queue<int> q;
		f[0]=last[0]=0;
		for(int i=0;i<26;i++){
			int u=ch[0][i];
			if(u){
				f[u]=last[u]=0;
				q.push(u);
			}
		}
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int c=0;c<26;c++){
				int u=ch[x][c];
				if(!u) {ch[x][c]=ch[f[x]][c];continue;}
				q.push(u);
				f[u]=ch[x][c];
				last[u]=val[f[u]]>0?f[u]:last[f[u]];
				if(last[u]) val[u]=1;
			}
		}
	}
	
};
ACmachine ac;

int n,m;
char word[110];
int dp[2][maxnode];
int main(){
	scanf("%d%d",&n,&m);
	ac.init();
	for(int i=1;i<=n;i++){
		scanf("%s",word);
		ac.insert(word);
	}
	ac.getFail();
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	int now,next;
	for(int i=0;i<m;i++){
		now=i%2;next=!now;
		memset(dp[next],0,sizeof(dp[next]));
		for(int j=0;j<=ac.sz;j++){
			if(dp[now][j]){
				for(int c=0;c<26;c++){
					if(!ac.val[ac.ch[j][c]])
						dp[next][ac.ch[j][c]]+=dp[i][j];
				}
			}
		}
	}
	int sum=1,ans=0;
	for(int i=1;i<=m;i++)
		sum=(sum*26)%mod;
	for(int j=0;j<=ac.sz;j++)
		ans=(ans+dp[m%2][j])%mod;
	//printf("sum:%d ans:%d\n",sum,ans);
	printf("%d\n",(sum+mod-ans)%mod);
	return 0;
}
