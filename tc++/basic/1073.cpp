# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int R=0,O=1;
long long f[520][520][2][2];
//bool vis[510][510][2][2];

void dp(int x,int y,int k,int p){
	if(p==R)
		f[x][y][k][R]=f[x-1][y][k][R]+f[x-1][y][k][O];
	else f[x][y][k][O]=f[x][y-1][k][R];
	//	printf("f[%d] [%d] [%d] [%d] :%d\n",x,y,k,p,f[x][y][k][p]);
}

int main(){
	memset(f,0,sizeof(f));//memset(vis,false,sizeof(vis));
	f[1][0][R][R]=f[0][1][O][O]=1;
	for(int i=1;i<505;i++){
		f[i][0][R][R]=1;
		for(int j=max(i-5,1);j<=i+1;j++){
			dp(i,j,R,R);
			if(j>=0) {dp(i,j,R,O);dp(i,j,O,R);dp(i,j,O,O);}
		}
	}
		int n,kase=0;
		while((scanf("%d",&n)!=EOF)&&n){
			printf("Case %d: ",++kase);
						if(n%2==1||n<3) printf("0\n");
							else
			printf("%lld\n",f[(n+4)/2][(n-4)/2][R][R]+f[(n+4)/2][(n-4)/2][R][O]+f[(n+4)/2][(n-4)/2][O][R]);
		}
/*	for(int i=1;i<=1000;i++)
	{
		int n=i;
		printf("i:%d ",i);
		if(i<3||i%2==1) printf("0\n");
			else printf("%d\n",f[(n+4)/2][(n-4)/2][R][R]+f[(n+4)/2][(n-4)/2][R][O]+f[(n+4)/2][(n-4)/2][O][R]);
				int a;
			scanf("%d",&a);
	}*/
	return 0;
}
