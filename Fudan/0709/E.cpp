# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
int R,L;
int n;

struct tank{
	int a,b,cost;
	tank() {}
	tank(int a,int b,int cost):a(a),b(b),cost(cost) {}
};

vector<tank> Cost[27];
char s[110];
int dp[110][110][27];

void update(int &x,int c){
	if(x<0) x=c;
	else x=min(x,c);
}
int dfs(int L,int R,int C){
	int l,r;
	if(dp[L][R][C]!=-1) return dp[L][R][C];
		//printf("L:%d R:%d C:%d\n",L,R,C);
	dp[L][R][C]=-2;
	if(L==R){
		//printf("dp[%d][%d][%d]:",L,R,C);
		if(s[L]=='a'+C-1) {//printf("0\n");
			return dp[L][R][C]=0;}
		else {//puts("-2");
			return dp[L][R][C]=-2;}
	}
	for(int M=L;M<R;M++){
		for(int i=0;i<(int)Cost[C].size();i++){
			l=dfs(L,M,Cost[C][i].a);r=dfs(M+1,R,Cost[C][i].b);
			if(l>=0&&r>=0){
				//if(L==1&&R==4&&C==1)
					//printf("M:%d l:%d r:%d cost:%d a:%d b:%d\n",M,l,r,Cost[C][i].cost,Cost[C][i].a,Cost[C][i].b);
				update(dp[L][R][C],l+r+Cost[C][i].cost);
			}
		}
	}
	//printf("dp[%d][%d][%d]:%d\n",L,R,C,dp[L][R][C]);
	return dp[L][R][C];
}

int main()
{
	int Tcase,T=0;
	char c;int b1,b2,b3,b4;
	scanf("%d",&Tcase);
	while(Tcase--){
		printf("CASE #%d\n",++T);
		scanf("%d %d",&R,&L);
		for(int i=1;i<=26;i++) Cost[i].clear();
		for(int i=1;i<=R;i++){
			while((c=getchar())&&(c<'A'||c>'Z'));b1=c-'A'+1;
			while((c=getchar())&&(c<'A'||c>'Z'));b2=c-'A'+1;
			while((c=getchar())&&(c<'A'||c>'Z'));b3=c-'A'+1;
			scanf("%d",&b4);
			//printf("b1:%d b2:%d b3:%d b4:%d\n",b1,b2,b3,b4);
			Cost[b1].push_back(tank(b2,b3,b4));
		}
		for(int i=1;i<=L;i++){
			scanf("%d ",&n);
			scanf("%s",s+1);
			memset(dp,-1,sizeof(dp));
			dfs(1,n,1);
			if(dp[1][n][1]<=-1) puts("IMPOSSIBLE");
			else printf("POSSIBLE WITH %d DIAMONDS\n",dp[1][n][1]+n);
		}
	}
	return 0;
}
