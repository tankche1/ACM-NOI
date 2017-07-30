# include<stdio.h>
# include<string.h>
# include<queue>
# include<string>
# include<algorithm>
using namespace std;
const int maxlen=51;
const int INF=~0U>>1;
const int maxn=13;
char news[50*13];
typedef pair<int,int> pi;
int n;
char s[maxn][maxlen],ss[maxn][maxlen];
int connect[maxn][maxn];
int dp[1][maxn][1<<12];
char last[1][maxn][1<<12][50*12+3];
int len[maxn];
int bh[maxn];
bool cmp(int a,int b){
	return strcmp(s[a],s[b])<0;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]),bh[i]=i;
	sort(bh+1,bh+n+1,cmp);
	memcpy(ss,s,sizeof(s));
	for(int i=1;i<=n;i++){
		for(int j=0;j<=strlen(ss[bh[i]]);j++)
			s[i][j]=ss[bh[i]][j];
		len[i]=strlen(s[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			int len1=strlen(s[i]);
			int len2=strlen(s[j]),k;
			for(int k=min(len1,len2);k>=0;k--){
				bool ok=true;
				for(int kk=1;kk<=k;kk++)
					if(s[j][kk-1]!=s[i][len1-k-1+kk]) {ok=false;break;}
				if(ok) {connect[i][j]=k;break;}
			}
			//printf("%d %d %d\n",i,j,connect[i][j]);
		}
	}
	memset(dp[0],-1,sizeof(dp[1]));
	queue<pi> q;
	for(int i=1;i<=n;i++){
		dp[0][i][1<<(i-1)]=strlen(s[i]);
		//for(int j=0;j<=len[i];j++) last[1][i][1<<(i-1)][j]=s[i][j];
		strcpy(last[0][i][1<<(i-1)],s[i]);
		q.push(pi(i,1<<(i-1)));
	}
	int now=0,next=1,maxstate=1<<(n);
	while(!q.empty()){
		int i=q.front().first;int state=q.front().second;q.pop();
		now=next=0;
		if(state==maxstate-1) break;
		//memset(dp[next],-1,sizeof(dp[next]));
				if(dp[now][i][state]!=-1){
					//printf("num:%d i:%d state:%d dp:%d\n",num,i,state,dp[now][i][state]);
					for(int k=1;k<=n;k++){
						if(!(state&(1<<(k-1)))){
						//	puts("fuck");
							int newstate=state|(1<<(k-1));
							//printf("i:%d state:%d dp:%d\n",k,newstate,dp[next][k][newstate]);
							if(dp[next][k][newstate]==-1||(dp[next][k][newstate]>dp[now][i][state]+len[k]-connect[i][k])){
								if(dp[next][k][newstate]==-1) q.push(pi(k,newstate));
								dp[next][k][newstate]=dp[now][i][state]+len[k]-connect[i][k];
								//last[next][k][newstate]=i;
								strcpy(last[next][k][newstate],last[now][i][state]);strcat(last[next][k][newstate],s[k]+connect[i][k]);
								//printf("dp[%d][%d][%d]:%d\n",next,k,newstate,dp[next][k][newstate]);
								//printf("%s\n",last[next][k][newstate]);
							}
							else if(dp[next][k][newstate]==dp[now][i][state]+len[k]-connect[i][k]){
								news[0]='\0';
								strcpy(news,last[now][i][state]);
								strcat(news,s[k]+connect[i][k]);
								if(strcmp(news,last[next][k][newstate])<0) {strcpy(last[next][k][newstate],news);
								//	printf("dp[%d][%d][%d]:%d\n",next,k,newstate,dp[next][k][newstate]);
								//printf("%s\n",last[next][k][newstate]);
								}
								//for(int j=0;j<strlen(last[next][k][newstate]);j++) newj=last[next][k][newstate][j];
							}
						}
					}
				}
	}
	int ans=INF,ansi;
	char anss[50*13];
	for(int i=n;i>=1;i--){
		if(dp[next][i][maxstate-1]!=-1&&dp[next][i][maxstate-1]<ans)
			ans=dp[next][i][maxstate-1],ansi=i,strcpy(anss,last[next][i][maxstate-1]);
		else if(dp[next][i][maxstate-1]==ans&&strcmp(last[next][i][maxstate-1],anss)<0) {
			strcpy(anss,last[next][i][maxstate-1]);
		}
	}
	printf("%s\n",anss);
	return 0;
}
/*
5
AA
AAA
AAAA
AAAAA
AB
3
A
B
C
*/
