#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1000;
int c[3],m;
int sg[maxn+10];
bool vis[maxn+10];

/*bool SG(int x){
	if(sg[x]!=-1) return sg[x];
	if(x<c[0]&&x<c[1]&&x<c[2]) return sg[x]=0;
	memset(vis,false,sizeof(vis));
	for(int j=0;j<3;j++)
	for(int i=0;i*2<=x-c[j];i++)
		vis[SG(i)^SG(x-c[j]-i)]=1,printf("x:%d %d %d %d\n",x,i,x-c[j]-i,SG(i)^SG(x-c[j]-i));
	for(int i=0;i<maxn;i++)
		if(!vis[i]) return sg[x]=i;
}*/

int main(){
	int tcase;
	scanf("%d%d%d",&c[0],&c[1],&c[2]);
	scanf("%d",&tcase);
	memset(sg,-1,sizeof(sg));
	sg[0]=0;
	for(int x=1;x<=maxn;x++){
		if(x<c[0]&&x<c[1]&&x<c[2]) {sg[x]=0;continue;}
		memset(vis,false,sizeof(vis));
		for(int j=0;j<3;j++)
			for(int i=0;i*2<=x-c[j];i++)
		vis[sg[i]^sg[x-c[j]-i]]=1;//printf("x:%d %d %d %d\n",x,i,x-c[j]-i,SG(i)^SG(x-c[j]-i));
		for(int i=0;i<maxn+10;i++)
		if(!vis[i]) {sg[x]=i;break;}
	}
	while(tcase--){
		scanf("%d",&m);
		printf("%d\n",sg[m]==0?2:1);
	}
	//for(int i=1;i<=100;i++) printf("sg[%d]:%d\n",i,sg[i]);
	return 0;
}
