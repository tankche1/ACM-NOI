# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef unsigned long long LL;
LL f[25][25];
int main(){
	memset(f,0,sizeof(f));
	f[1][0]=1;
	for(int i=2;i<=21;i++){
		for(int j=0;j<i;j++){
			f[i][j]=f[i-1][j];
			if(j)
				f[i][j]+=f[i-1][j-1]*(i-1);
			//printf("f[%d][%d]:%lld\n",i,j,f[i][j]);
		}
	}
	int n,k;
	while(scanf("%d%d",&n,&k)!=EOF){
		if(!n&&!k) break;
		printf("%llu\n",f[n][k]);
	}
	return 0;
}
