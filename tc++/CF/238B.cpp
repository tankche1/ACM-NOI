#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int s=1000000;
int n;
int x[s+10];
bool use[s+10];
int pos=1;
int ans[s+10];
int main(){
	memset(use,0,sizeof(use));
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x[i]);
	//	int x=x[i]<=499999?x[i]:s+1-x[i];
		use[x[i]]=1;
	}
	ans[0]=0;
	for(int i=1;i<=n;i++){
		//printf("%d\n",x[i]);
		if(!use[s+1-x[i]]){
			ans[++ans[0]]=s+1-x[i];use[s+1-x[i]]=1;
		//	printf("ans:%d\n",ans[ans[0]]);
		}
		else if(x[i]<=500000) {
			while(use[pos]||use[s-pos+1]) pos++;
			ans[++ans[0]]=pos;ans[++ans[0]]=s-pos+1;
			use[pos]=use[s-pos+1]=1;
		}
	}
	printf("%d\n",ans[0]);
	for(int i=1;i<=ans[0];i++)
		printf("%d ",ans[i]);puts("");
	return 0;
}
