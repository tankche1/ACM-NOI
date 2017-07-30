# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=105;
const int mod=1000000007;
int T;
int m,n;
char s[2][maxn];

struct ACMachine{
	int ch[maxn*2][2];
	int f[maxn<<1],last[maxn<<1];
	int sz;int val[maxn*2];
	void init(){
		sz=0;ch[sz][0]=ch[sz][1]=0;val[0]=0;
	}
	
	int id(char c){
		if(c=='R') return 0;return 1;
	}
	
	void insert(char *s,int v){
		int u=0,n=strlen(s);
		for(int i=0;i<n;i++){
			int c=id(s[i]);
			if(!ch[u][c]){
				ch[u][c]=++sz;ch[sz][0]=ch[sz][1]=0;val[sz]=0;
				//printf("ch[%d][%d]:%d\n",u,c,ch[u][c]);
			}u=ch[u][c];
		}val[u]=v;
	}
	
	void getFailed(){
		queue<int> q;
		f[0]=last[0]=0;
		for(int i=0;i<2;i++){
			if(ch[0][i]){int u=ch[0][i];
				if(!u) continue;
				f[u]=last[u]=0;q.push(u);
			}
		}
		while(!q.empty()){
			int x=q.front();q.pop();
		//	printf("x:%d f:%d\n",x,f[x]);
			for(int c=0;c<2;c++){
				int u=ch[x][c];
				if(!u) {ch[x][c]=ch[f[x]][c];continue;}
				q.push(u);
				f[u]=ch[f[x]][c];
				last[u]=val[f[u]]?f[u]:last[f[u]];
			}
		}
	}
};
ACMachine ac;
int dp[maxn][maxn][maxn<<1][4];

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		scanf("%s%s",s[0],s[1]);//puts(s[0]);puts(s[1]);
		ac.init();
		ac.insert(s[0],1);ac.insert(s[1],2);
		//puts("a");
		ac.getFailed();//puts("a");
		memset(dp,0,sizeof(dp));
		dp[0][0][0][0]=1;
		int kk=50,cnt=0;
		//for(int i=0;i<=ac.sz;i++)
		//	printf("ch[%d][0]:%d ch[%d][1]:%d\n",i,ac.ch[i][0],i,ac.ch[i][1]);
		//for(int i=0;i<=ac.sz;i++)
			//if(ac.val[ac.last[i]]) printf("%d %d\n",i,ac.val[ac.last[i]]);
		for(int i=0;i<=m;i++)
			for(int j=0;j<=n;j++)
				for(int k=0;k<=ac.sz;k++)
					for(int l=0;l<4;l++){
						if(dp[i][j][k][l]){
						//	if(l&1) {printf("dp[%d][%d][%d][%d]:%d\n",i,j,k,l,dp[i][j][k][l]);int fuck;scanf("%d",&fuck);}
							if(i<m){
								int ll=ac.val[ac.ch[k][1]]|l|ac.val[ac.last[ac.ch[k][1]]];
								dp[i+1][j][ac.ch[k][1]][ll]=(dp[i+1][j][ac.ch[k][1]][ll]+dp[i][j][k][l])%mod;
							}
							if(j<n){
								int ll=ac.val[ac.ch[k][0]]|l|ac.val[ac.last[ac.ch[k][0]]];
								dp[i][j+1][ac.ch[k][0]][ll]=(dp[i][j+1][ac.ch[k][0]][ll]+dp[i][j][k][l])%mod;
							}
							if(dp[i][j][k][l]>100){
						//	int fuck;if((++cnt)==kk) {cnt=0;scanf("%d",&fuck);}
								}
						}
					}
		int ans=0;
		for(int k=0;k<=ac.sz;k++){
			ans=(ans+dp[m][n][k][3])%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
10
3 3
RDRDRD
DRD
49 18 
DDDRDDRRRRRDDDRDDRRDRDRDDDRRDDRRDRDR
RRRDDD
*/
