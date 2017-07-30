# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=30;
int two[32],K;
inline int pos(int i,int j){
	return 3*(i-1)+2+j;
}
int G[1010][1010];
int main(){
	//printf("%lld\n",(long long )1<<30);
	two[0]=1;
	for(int i=1;i<=31;i++)
		two[i]=two[i-1]<<1;
	scanf("%d",&K);
	if(K==1){
		puts("2");puts("NY\nYN");return 0;
	}
	memset(G,0,sizeof(G));
	G[2][3]=G[2][4]=1;
	int step;
	for(step=1;;step++) if(two[step]>K) break;step--;
	for(int i=1;i<step;i++){
		G[pos(i,1)][pos(i+1,1)]=G[pos(i,1)][pos(i+1,2)]=G[pos(i,2)][pos(i+1,1)]=G[pos(i,2)][pos(i+1,2)]=1;
		//printf("%d %d\n",pos(i,1),pos(i+1,1));
		G[pos(i,3)][pos(i+1,3)]=1;
		if(i>=2&&(K&two[i-2])) G[pos(i,3)][pos(i-1,2)]=1;
	}
	for(int i=step;i<=step+1;i++) if(i>=2&&(K&two[i-2])) G[pos(i,3)][pos(i-1,2)]=1;
	G[pos(step,1)][pos(step+1,1)]=G[pos(step,2)][pos(step+1,1)]=G[pos(step,3)][pos(step+1,3)]=1;
	G[1][pos(step+1,1)]=G[1][pos(step+1,3)]=1;
	int n=pos(step+1,3);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			G[i][j]=G[i][j]|G[j][i];
	printf("%d\n",pos(step+1,3));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			if(G[i][j]) printf("Y");
				else printf("N");puts("");}
	return 0;
}
