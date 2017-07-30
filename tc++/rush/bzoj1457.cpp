# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=102;
int sg[maxn][maxn];
bool vis[maxn*maxn];
int x[maxn*maxn],y[maxn*maxn];

void add(int a,int b){
	if(a>0&&b>0&&a!=b) vis[sg[a][b]]=1;
}

int main(){
	memset(sg,0,sizeof(sg));
	sg[0][0]=0;
	for(int i=1;i<maxn;i++)
		for(int j=1;j<maxn;j++){
			memset(vis,false,sizeof(vis));
			for(int k=1;k<=max(i,j);k++){
				if(i>=k) add(i-k,j);
				if(i>=k&&j>=k) add(i-k,j-k);
				if(j>=k) add(i,j-k);
			}
			int l=0;
			while(vis[l]) l++;
			sg[i][j]=l;
			//printf("sg[%d][%d]:%d\n",i,j,sg[i][j]);
		}
	int tcase,n;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		bool ok=false;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&x[i],&y[i]);if(x[i]==0||y[i]==0||x[i]==y[i]) ok=true;}//x[i]--,y[i]--;
		int ans=sg[x[1]][y[1]];
		for(int i=2;i<=n;i++)
			ans=ans^sg[x[i]][y[i]];
		if(ans||ok) puts("^o^");
			else puts("T_T");
	}
	return 0;
}
