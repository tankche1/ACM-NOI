#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
const int maxn=510;
const int maxm=maxn*maxn;
int n,m;
int d[maxn];
int u[maxm],v[maxm];
double w[maxm];
double A[maxn][maxn];
	
void gauss(){
	int i,j,k,r;
	for(i=1;i<=n;i++){
		r=i;
		for(j=i+1;j<=n;j++) if(fabs(A[j][i])>fabs(A[r][i])) r=j;
		if(r!=i) for(int j=1;j<=n+1;j++) swap(A[i][j],A[r][j]);
		for(j=i+1;j<=n;j++){
			double t=A[j][i]/(A[i][i]*1.0);
			for(k=i;k<=n+1;k++)
				A[j][k]-=t*A[i][k];
		}
	}
	for(i=n;i>=1;i--){
		for(j=i+1;j<=n;j++)
			A[i][n+1]-=A[i][j]*A[j][n+1];
		A[i][n+1]/=A[i][i];
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	scanf("%d%d",&n,&m);
	memset(d,0,sizeof(d));
	for(int i=1;i<=m;i++)
		scanf("%d%d",&u[i],&v[i]),d[u[i]]++,d[v[i]]++;
	memset(A,0,sizeof(A));
	for(int i=1;i<=m;i++){
		if(u[i]!=n&&v[i]!=n) A[u[i]][v[i]]=1/(d[v[i]]*1.0);
		if(v[i]!=n&&u[i]!=n) A[v[i]][u[i]]=1/(d[u[i]]*1.0);
	}
	for(int i=1;i<=n;i++)
		A[i][i]=-1;
	A[1][n+1]=-1;
	A[n][n+1]=-1;
	//for(int i=1;i<=n;i++){
	//	for(int j=1;j<=n+1;j++)
	//		printf("A[%d][%d]:%.3lf ",i,j,A[i][j]);puts("");}
	gauss();
	//for(int i=1;i<=n;i++)
	//	printf("ans[%d]:%.3lf\n",i,A[i][n+1]);
	//printf("fuck:%d %d\n",u[514],v[514]);
	for(int i=1;i<=m;i++){
		//printf("i:%d u:%d v:%d\n",i,u[i],v[i]);
		w[i]=0;
		if(u[i]!=n) w[i]+=A[u[i]][n+1]/(d[u[i]]*1.0);
		if(v[i]!=n) w[i]+=A[v[i]][n+1]/(d[v[i]]*1.0);
	}
	sort(w+1,w+m+1);
	double ans=0;
	for(int i=m;i>=1;i--)
		ans+=w[i]*(m-i+1);//,printf("%.3lf\n",w[i]);
	printf("%.3lf\n",ans);
	return 0;
}
