# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=55;
const int maxm=2002;
const int INF=1<<29;

int money[maxn],maxnum[maxn],son[maxn][maxn],need[maxn][maxn],power[maxn];
bool basic[maxn],vis[maxn];

int N,M;
int f[maxn][maxm][110];
int g[maxn][maxm];
int ans=0;
bool v[maxn];

void TreeDp(int x){
	vis[x]=true;
	if(basic[x]){
			for(int k=0;k<=maxnum[x]&&k*money[x]<=M;k++)
			for(int j=0;j<=k;j++)
			{f[x][money[x]*(k)][j]=(k-j)*power[x];//printf("f[%d][%d][%d]:%d\n",x,money[x]*k,j,(k-j)*power[x]);
				if(f[x][money[x]*k][j]+j*power[x]>ans) ans=f[x][money[x]*k][j]+j*power[x];
			}
		return;
	}
	for(int i=1;i<=son[x][0];i++)
	if(!vis[son[x][i]]) TreeDp(son[x][i]);
	//memset(g,0,sizeof(g));
	//printf("x:%d\n",x);
	for(int k=0;k<=maxnum[x];k++){//make k (x)
		//printf("k:%d\n",k);
		int sum=0;
			for(int i=1;i<=son[x][0];i++){
				for(int j=0;j<=M;j++){
					g[i][j]=-INF;
					for(int kk=0;kk<=j;kk++){
						{g[i][j]=max(g[i][j],g[i-1][kk]+f[son[x][i]][j-kk][k*need[x][i]]);
						}
					}
				//	printf("g[%d][%d]:%d\n",i,j,g[i][j]);
				}
				sum+=k*need[x][i]*money[son[x][i]];
			}
		for(int j=0;j<=M;j++)
			for(int l=k;l>=0;l--)
		{f[x][j][l]=max(f[x][j][l],g[son[x][0]][j]+power[x]*(k-l));//printf("f[%d][%d][%d]:%d\n",x,j,l,f[x][j][l]);
			if(f[x][j][l]+l*power[x]>ans) ans=f[x][j][l]+l*power[x];
		}
	}
	return;
}

void pre_dfs(int x){
	vis[x]=true;
	if(basic[x]) {maxnum[x]=min(maxnum[x],M/money[x]);return;};
	for(int i=1;i<=son[x][0];i++)
	if(!vis[son[x][i]]) pre_dfs(son[x][i]);
	int num=INF,sum=0;
	for(int i=1;i<=son[x][0];i++){
		num=min(num,maxnum[son[x][i]]/need[x][i]);
		sum+=need[x][i]*money[son[x][i]];
	}
	maxnum[x]=min(num,M/sum);
	money[x]=sum;
}

int main(){
	//freopen("out.txt","w",stdout);
	char op;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++){
		scanf("%d",&power[i]);
		while((op=getchar())&&op!='A'&&op!='B');
		basic[i]=op=='B';
		if(basic[i]){
			scanf("%d%d",&money[i],&maxnum[i]);
		}
		else{
			scanf("%d",&son[i][0]);
			for(int j=1;j<=son[i][0];j++)
			{scanf("%d%d",&son[i][j],&need[i][j]);v[son[i][j]]=true;}
		}
	}
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=N;i++)
		if(!vis[i])
	pre_dfs(i);
	memset(vis,false,sizeof(vis));
	memset(f,0,sizeof(f));
		g[0][0]=0;
		for(int i=1;i<maxm;i++) g[0][i]=-INF;
		for(int i=0;i<maxn;i++)
			for(int j=0;j<maxm;j++)
				for(int l=0;l<110;l++) f[i][j][l]=-INF;
	for(int i=1;i<=N;i++){
		if(!vis[i]) {TreeDp(i);
			for(int j=0;j<=M;j++)
				for(int k=0;k<=maxnum[i];k++)
					ans=max(ans,f[i][j][k]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*
3 23
1 B 5 3
1 B 4 2
7 A 2 1 2 2 1
*/
