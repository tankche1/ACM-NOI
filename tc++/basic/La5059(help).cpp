# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int SG[110];
int main(){
	SG[1]=0;
	bool vis[110];
	for(int i=2;i<=30;i++){
		memset(vis,false,sizeof(vis));
		for(int j=1;2*j<=i;j++)
			vis[SG[i-j]]=true;
		for(int k=0;k<=i;k++) if(!vis[k]) {SG[i]=k;break;}
		printf("%d\n",SG[i]);
	}
	return 0;
}
