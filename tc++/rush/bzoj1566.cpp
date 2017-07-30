# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int mod=1024523;
const int maxn=505;
int n,m;
char s1[maxn],s2[maxn];
int f[2][maxn][maxn];

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",s1+1);
	scanf("%s",s2+1);
	f[0][0][0]=1;
	for(int i=0;i<=n;i++){
		int now=i%2;int next=!now;memset(f[next],0,sizeof(f[next]));
		for(int j=0;j<=m;j++)
			for(int k=max(0,i+j-m);k<=i+j&&k<=n;k++){
				//printf("i:%d j:%d k:%d\n",i,j,k);
				//printf("f[%d][%d][%d]:%d\n",i,j,k,f[now][j][k]);
				if(f[now][j][k]!=0){
					int l=i+j-k;
					//printf("f[%d][%d][%d]:%d\n",i,j,k,f[now][j][k]);
					if(f[now][j][k]>=mod) f[now][j][k]%=mod;
					if(i<n&&k<n&&s1[n-i]==s1[n-k])
						f[next][j][k+1]+=f[now][j][k];//,puts("a"),printf("f[%d][%d][%d]:%d\n",i+1,j,k+1,f[next][j][k+1]);
					if(i<n&&l<m&&s1[n-i]==s2[m-l])
						f[next][j][k]+=f[now][j][k];//puts("b");
					if(j<m&&k<n&&s2[m-j]==s1[n-k])
						f[now][j+1][k+1]+=f[now][j][k];//puts("c");
					if(j<m&&l<m&&s2[m-j]==s2[m-l])
						f[now][j+1][k]+=f[now][j][k];//puts("d");
				}
			}
	}
	printf("%d\n",f[n%2][m][n]%mod);
	return 0;
}
