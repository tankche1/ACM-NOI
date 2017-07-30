# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
# define FUCK(x) printf("fuck %d\n",x);
const int maxn=1002;
const int INF=1<<25;
int people[3][6];
int end[3],debt[3],start[3];
int money[6]={1,5,10,20,50,100};
int dp[2][maxn][maxn];
int yue[6]={1,5,10,10,50,100};
int now,last;

void Doit(int A,int B,int C,int a,int b,int c,int num){//A->B,C
	int p[3],q[3];
	q[A]=a;q[B]=b;q[C]=c;
	for(int i=0;i<=people[A][num];i++){
		for(int j=0;j<=i;j++){
			p[A]=a-i*money[num];
			p[B]=b+j*money[num];
			p[C]=c+(i-j)*money[num];
			dp[now][p[0]][p[1]]=min(dp[now][p[0]][p[1]],dp[last][q[0]][q[1]]+i);
		}
	}
}

void given(int A,int B,int C,int a,int b,int c,int num){//A,B->C
	int p[3],q[3];
	q[A]=a;q[B]=b;q[C]=c;
	for(int i=0;i<=people[A][num];i++){
		for(int j=0;j<=people[B][num];j++){
			p[A]=a-i*money[num];
			p[B]=b-j*money[num];
			p[C]=c+(i+j)*money[num];
			dp[now][p[0]][p[1]]=min(dp[now][p[0]][p[1]],dp[last][q[0]][q[1]]+(i+j));
		}
	}
}

int main(){
	for(int i=0;i<=2;i++) scanf("%d",&debt[i]);
		int sum=0;
	for(int i=0;i<=2;i++){
		start[i]=0;
		for(int j=5;j>=0;j--)
		{scanf("%d",&people[i][j]);start[i]+=people[i][j]*money[j];}
		sum+=start[i];
	}
	for(int i=0;i<=2;i++){
		end[i]=start[i]-debt[i]+debt[i-1==-1?2:i-1];
	}
	for(int i=0;i<=sum;i++)
		for(int j=0;j<=sum;j++)
			dp[1][i][j]=INF;
	dp[1][start[0]][start[1]]=0;
		if(end[0]<0||end[1]<0||end[2]<0){
			printf("impossible\n");return 0;
		}
	for(int i=0;i<6;i++){
		now=i%2;last=now^1;//FUCK(1)
		for(int j=0;j<=sum;j++) for(int k=0;k<=sum;k++) dp[now][j][k]=INF;//FUCK(2)
		for(int j=0;j<=sum;j++)
			for(int k=0;k<=sum;k++){
				if(dp[last][j][k]==INF||(abs(end[0]-j)%yue[i])!=0||(abs(end[1]-k)%yue[i])!=0) continue;
									//printf("%d %d %d\n",i,j,k);
				Doit(0,1,2,j,k,sum-j-k,i);Doit(1,0,2,k,j,sum-j-k,i);Doit(2,0,1,sum-j-k,j,k,i);
				given(0,1,2,j,k,sum-j-k,i);given(1,0,2,k,j,sum-j-k,i);given(2,0,1,sum-j-k,j,k,i);
			}
	/*	for(int j=0;j<=sum;j++)
			for(int k=0;k<=sum;k++)
				if(dp[now][j][k]!=INF)
					printf("dp[%d][%d][%d][%d]:%d\n",i,j,k,sum-j-k,dp[now][j][k]);*/
	}
	if(dp[now][end[0]][end[1]]!=INF)
	printf("%d\n",dp[now][end[0]][end[1]]);
	else printf("impossible\n");
	return 0;
}
