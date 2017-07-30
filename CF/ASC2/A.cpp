# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
char s[30];
int alpha;
int n;
int to[maxn][27];
int edge[maxn][27];
int st,ed_num,ed[maxn];
bool again[maxn][27];
int Len;
bool vis[maxn][27];

int dfs(int x,int c){
	//printf("x:%d c:%d\n",x,c);
	if(to[x][c]!=-1) return to[x][c];
	if(vis[x][c]) return to[x][c]=-2;
	vis[x][c]=1;
	if(!again[x][c]) return to[x][c]=edge[x][c];
	else return to[x][c]=dfs(edge[x][c],c);
}

struct Big{
	int Len,A[50];
	Big() {memset(A,0,sizeof(A));Len=1;}
	
	void operator += (const Big &B){
		int n=max(Len,B.Len);
		for(int i=0;i<n;i++)
			A[i]=A[i]+B.A[i];
		for(int i=0;i<n;i++){
			if(A[i]>=100000) A[i+1]++,A[i]-=100000;
		}
		Len=n;
		while(A[Len]>0) Len++;
	}
	
	void print(){
		printf("%d",A[Len-1]);
		for(int i=Len-2;i>=0;i--){
			if(A[i]<10000) printf("0");
			if(A[i]<1000) printf("0");
			if(A[i]<100) printf("0");
			if(A[i]<10) printf("0");
			printf("%d",A[i]);
		}
		puts("");
	}
}dp[65][maxn],ans;

int main()
{
	freopen("dfa.in","r",stdin);
	freopen("dfa.out","w",stdout);
	scanf("%s",s);alpha=strlen(s);
	memset(to,-1,sizeof(to));
	scanf("%d",&n);
	scanf("%d%d",&st,&ed_num);
	for(int i=1;i<=ed_num;i++)
		scanf("%d",&ed[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=alpha;j++)
			scanf("%d",&edge[i][j]);
	}
	int b;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=alpha;j++)
			scanf("%d",&b),again[i][j]=b;
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=alpha;j++)
			dfs(i,j);
	scanf("%d",&Len);
	//memset(dp,0,sizeof(dp));
	dp[0][st].A[0]=1;
	for(int i=0;i<Len;i++){
		for(int j=1;j<=n;j++){
			if(dp[i][j].Len==1&&dp[i][j].A[0]==0) continue;
				for(int k=1;k<=alpha;k++)
					if(to[j][k]>0) dp[i+1][to[j][k]]+=dp[i][j];
		}
	}
	for(int i=1;i<=ed_num;i++)
		ans+=dp[Len][ed[i]];
	ans.print();
	return 0;
}
