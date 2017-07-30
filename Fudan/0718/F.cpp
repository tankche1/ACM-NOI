# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxm=1010;
const int INF=10000;
char gene[4]={'A','C','G','T'};
inline int code(char t){
	for(int i=0;i<4;i++) if(gene[i]==t) return i;
}

queue<int> Q;
int m;

struct ACmachine{
	int ch[maxm][4];
	int val[maxm];
	int sz;
	int f[maxm],last[maxm];
	
	void init() {val[0]=0;memset(ch[0],0,sizeof(ch[0]));sz=0;}
	void insert(char *s,int bh){
		int n=strlen(s),u=0,c;if(n>m) return;
		for(int i=0;i<n;i++){
			c=code(s[i]);
			if(!ch[u][c]){
				ch[u][c]=++sz;memset(ch[sz],0,sizeof(ch[sz]));val[sz]=0;
			}
			u=ch[u][c];
		}
		//printf("u:%d\n",u);
		val[u]|=(1<<(bh-1));
	}
	
	void get_Fail(){ 
		f[0]=0;
		for(int c=0;c<4;c++)
			if(ch[0][c]){
				f[ch[0][c]]=0;Q.push(ch[0][c]);
			}
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			for(int c=0;c<4;c++){
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
char s[1010];
int n;
int w[20];
bool dp[2][maxm][1030];
int cost[1025];

int main(){
	int cc;
	while(scanf("%d%d\n",&n,&m)!=EOF){
	ac.init();
	for(int i=1;i<=n;i++){
		scanf("%s",s);ac.insert(s,i);scanf("%d",&w[i]);
	}
	ac.get_Fail();
	for(int i=0;i<(1<<n);i++){
		cost[i]=0;
		for(int j=1;j<=n;j++)
			if((i>>(j-1))&1) cost[i]+=w[j];
	}
	memset(dp[0],0,sizeof(dp[0]));
	dp[0][0][0]=1;
	int now,nextt,t;
	for(int digit=0;digit<m;digit++){
		now=digit&1;nextt=now^1;
		memset(dp[nextt],0,sizeof(dp[nextt]));
				
		for(int j=0;j<=ac.sz;j++)
			for(int k=0;k<(1<<n);k++){
				if(!dp[now][j][k]) continue;
				for(int c=0;c<4;c++){
					t=ac.ch[j][c];
					dp[nextt][t][k|ac.val[t]]=1;
				}
			}
	}
	now=m&1;
	int ans=-INF;
	for(int j=0;j<=ac.sz;j++)
			for(int k=0;k<(1<<n);k++)
				if(dp[now][j][k])
					ans=max(ans,cost[k]);
	if(ans<0) puts("No Rabbit after 2012!");
	else printf("%d\n",ans);
	}
	return 0;
}
