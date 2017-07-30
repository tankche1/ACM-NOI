# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1510;
const int INF=~0U>>1;
int m,n,k;
int A[maxn][maxn];
int S[maxn][maxn];
int RD[maxn][maxn],RU[maxn][maxn],LD[maxn][maxn],LU[maxn][maxn];
int Line[maxn];//第i行中的格子做右下角时的最大面积
int Row[maxn];
int X,Y;

int area(int i,int j){
	return S[i][j]-S[i-k][j]-S[i][j-k]+S[i-k][j-k];
}
int max(int a,int b,int c){
	return max(max(a,b),c);
}

int max(int a,LL b){
	if(b<0) return a;
		return a<b?b:a;
}

int main(){
	scanf("%d%d%d",&m,&n,&k);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&A[i][j]);
		memset(S,0,sizeof(S));
		for(int i=0;i<=m+1;i++){
			for(int j=0;j<=n+1;j++)
				LU[i][j]=LD[i][j]=RU[i][j]=RD[i][j]=Line[i]=Row[j]=-INF;
		}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)
			S[i][j]=S[i-1][j]+S[i][j-1]-S[i-1][j-1]+A[i][j];
	}
	for(int i=1;i<=n;i++) Row[i]=-INF;
	for(int i=k;i<=m;i++){
		for(int j=k;j<=n;j++){
			RD[i][j]=max(RD[i-1][j],RD[i][j-1],S[i][j]-S[i-k][j]-S[i][j-k]+S[i-k][j-k]);
			Line[i]=max(Line[i],area(i,j));
			Row[j]=max(Row[j],area(i,j));
		}
	}
		for(int i=m-k+1;i>=1;i--)
			for(int j=k;j<=n;j++)
				RU[i][j]=max(RU[i][j-1],RU[i+1][j],area(i+k-1,j));
		for(int i=m-k+1;i>=1;i--)
			for(int j=n-k+1;j>=1;j--)
				LU[i][j]=max(LU[i][j+1],LU[i+1][j],area(i+k-1,j+k-1));
		for(int i=k;i<=m;i++)
			for(int j=n-k+1;j>=1;j--)
				LD[i][j]=max(LD[i][j+1],LD[i-1][j],area(i,j+k-1));
		/*for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++){
				printf("i:%d j:%d RD:%d RU:%d LU:%d LD:%d\n",i,j,RD[i][j],RU[i][j],LU[i][j],LD[i][j]);
			}*/
			int ans=-INF;
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				ans=max(ans,(LL)(RD[i][j]+LD[i][j+1]+LU[i+1][1]));
				//if((LL)(RD[i][j]+LD[i][j+1]+LU[i+1][1])==183) printf(" aa i:%d j:%d\n",i,j);
				ans=max(ans,(LL)(RD[i][n]+RU[i+1][j]+LU[i+1][j+1]));
				//if((LL)(RD[i][n]+RU[i+1][j]+LU[i+1][j+1])==183) printf("bb i:%d j:%d\n",i,j);
			}
			for(int j=i+k;j<=m;j++){
				ans=max(ans,(LL)(RD[i][n]+Line[j]+LU[j+1][1]));
			//	if((LL)(RD[i][n]+Line[j]+LU[j+1][1])==183) printf("cc i:%d j:%d\n",i,j);
			}
		}
		
		for(int j=1;j<=n;j++){
			for(int i=1;i<=m;i++){
				ans=max(ans,(LL)(RD[m][j]+LD[i][j+1]+LU[i+1][j+1]));
				//if((LL)(RD[m][j]+LD[i][j+1]+LU[i+1][j+1])==183) printf("dd i:%d j:%d\n",i,j);
				ans=max(ans,(LL)(RD[i][j]+RU[i+1][j]+LU[1][j+1]));
				//if((LL)(RD[i][j]+RU[i+1][j]+LU[1][j+1])==183) printf("ee i:%d j:%d\n",i,j);
			}
			for(int i=j+k;i<=n;i++){
				ans=max(ans,(LL)(RD[n][j]+Row[i]+LU[1][i+1]));
				//if((LL)(RD[n][j]+Row[i]+LU[1][i+1])==183) printf("ff i:%d j:%d\n",i,j);
			}
		}
		printf("%d\n",ans);
	return 0;
}
/*
12 11 3

2 3 2 3 3 3 3 2 3 3 2

3 3 3 2 2 3 3 4 2 2 3

3 4 3 4 2 3 4 3 4 3 2

4 4 4 5 3 2 4 4 4 3 3

4 5 3 3 6 6 6 3 5 2 3

5 5 4 5 5 6 6 4 5 3 2

3 4 2 3 6 7 6 3 3 3 3

2 3 3 3 2 2 2 2 3 4 3

2 2 4 3 4 3 2 3 3 2 4

3 3 3 3 2 4 3 3 3 2 3

2 3 2 3 4 4 3 3 2 3 2

3 3 3 3 3 3 4 2 3 4 3
*/
