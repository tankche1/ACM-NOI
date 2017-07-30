# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
int a[maxn][maxn];
int s[maxn][maxn];
int m,n,k;
int x[maxn];
int ans;
void check(){
	int res=0;
	for(int i=1;i<=m;i++){
		int tot=0;
		for(int j=1;j<=n;j++){
			tot+=a[i][j]^x[j];
		}
		res+=min(tot,n-tot);
	}
	ans=min(ans,res);
}

int main(){
	ans=maxn*maxn;
	scanf("%d%d%d",&m,&n,&k);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	if(n>m){
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				s[n-j+1][i]=a[i][j];
		swap(m,n);
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=s[i][j];//printf("%d ",a[i][j]);
			}//puts("");
		}
	}
	if(n<=k){
		for(int mask=0;mask<(1<<n);mask++){
			for(int i=0;i<n;i++)
				x[i+1]=(mask>>i)&1;
			check();
		}
	}
	else{
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++) x[j]=a[i][j];
			check();
		}
	}
	if(ans>k) puts("-1");
	else printf("%d\n",ans);
	return 0;
}
