# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int a[40][40];
int m,n,k;
int L[40];
bool ok;
int cnt=0;
int col[400];
bool vis[400][400];
bool dfs(int x,int y){
	if(y>n) y=1,x++;
	if(a[x][y]) return dfs(x,y+1);
	if(x==m+1){
		return true;
	}
	for(int i=1;i<=k;i++){
		if(n-y+1>=L[i]){
			ok=true;
			for(int j=y;j<y+L[i];j++)
				if(a[x][j]) {ok=false;break;}
			if(ok){
				cnt++;
				for(int j=y;j<y+L[i];j++) a[x][j]=cnt;
				if(dfs(x,y+L[i])) return true;
				for(int j=y;j<y+L[i];j++) a[x][j]=0;cnt--;
			}
		}
		if(m-x+1>=L[i]){
			ok=true;
			for(int j=x;j<x+L[i];j++)
				if(a[j][y]) {ok=false;break;}
			if(ok){
				cnt++;
				for(int j=x;j<x+L[i];j++) a[j][y]=cnt;
				if(dfs(x,y+1)) return true;
				for(int j=x;j<x+L[i];j++) a[j][y]=0;cnt--;
			}
		}
	}
	return false;
}

int main()
{
	scanf("%d%d%d",&m,&n,&k);
	for(int i=1;i<=k;i++)
		scanf("%d",&L[i]);
	memset(a,0,sizeof(a));
	bool ok=dfs(1,1);
	if(!ok) {puts("NO");return 0;}
	puts("YES");
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			vis[a[i][j]][a[i][j+1]]=vis[a[i][j+1]][a[i][j]]=1;
			vis[a[i][j]][a[i+1][j]]=1;vis[a[i+1][j]][a[i][j]]=1;
		}
	bool pp[30];
	memset(col,0,sizeof(col));
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(!col[a[i][j]]){
				memset(pp,0,sizeof(pp));
				for(int k=1;k<=cnt;k++)
					if(vis[a[i][j]][k]) pp[col[k]]=1;
				for(int k=1;k<=26;k++) if(!pp[k]) {col[a[i][j]]=k;break;}
			}
			printf("%c",col[a[i][j]]+'a'-1);
	}puts("");
}
	return 0;
}
