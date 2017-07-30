# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL alice,bob,x,y;
int winner;
int n;
const int maxn=110;
int a[maxn],b[maxn];
int sg[2200][2200];
const int INF=(~0U>>1)-5;

int SG(int x,int y){
	if(sg[x][y]!=INF) return sg[x][y];
	if(x==1) return sg[x][y]=-(y-1);
	if(y==1) return sg[x][y]=x-1;
		sg[x][y]=-INF;
	for(int k=1;k<x;k++){
		if(SG(y,k)>0) sg[x][y]=max(sg[x][y],1-sg[y][k]+SG(x-k,y));
		else sg[x][y]=max(sg[x][y],1-sg[y][k]-SG(y,x-k));
	}
	return sg[x][y];
}

int main(){
	int Tcase,t=0;
	for(int i=1;i<=2000;i++)
		for(int j=1;j<=2000;j++)
			sg[i][j]=INF;
	//memset(sg,999999999,sizeof(sg));
	//printf("%d %d\n",sg[2][3],INF);
	while(1){
		scanf("%d",&t);
		for(int i=1;i<=10;i++)
			printf("SG(%d,%d):%d\n",t,i,SG(t,i));
	}
	/*
	scanf("%d",&Tcase);
	while(Tcase--){
		alice=bob=0;
		printf("Case %d: ",++t);
		scanf("%d",&n);
		winner=2;
		for(int i=1;i<=n;i++){
			scanf("%I64d%I64d",&x[i],&y[i]);
		}

	}*/
	return 0;
}
