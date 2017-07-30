#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=110;
typedef long long LL;
int n,A[maxn];
int p[maxn],cnt=0;
int a[40][maxn];

bool check(){
	int n=30,m=cnt;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			a[i][j]=(p[j]>>(i-1))&1;
		a[i][m+1]=0;
	}
/*	for(int i=1;i<=cnt;i++) printf("p[%d]:%d\n",i,p[i]);
	for(int i=1;i<=5;i++)
		for(int j=1;j<=m+1;j++){
			printf("a[%d][%d]:%d\n",i,j,a[i][j]);
		}*/
	int h=1;
	for(int i=1;i<=m;i++){
		int j=h;
		for(;j<=n&&a[j][i]==0;j++);
		if(j>n) return false;
		if(j!=h) for(int k=1;k<=m+1;k++) swap(a[h][k],a[j][k]);
		for(int l=h+1;l<=n;l++){
			if(a[l][i])
				for(int k=i;k<=m+1;k++)
					a[l][k]^=a[h][k];
		}
		h++;
	}
	return true;
}

int main(){
	LL sum=0,ans;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),sum+=A[i];ans=sum;
	sort(A+1,A+n+1);
	for(int i=n;i>=1;i--){
		//if(A[i]==A[i+1]) continue;
		p[++cnt]=A[i];
		if(!check()) cnt--;
	}
	if(cnt==0) puts("-1");
	else{
		for(int i=1;i<=cnt;i++) ans-=p[i];//printf("p[%d]:%d\n",i,p[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
