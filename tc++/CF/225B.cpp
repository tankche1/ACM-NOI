#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int n,m,k;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	int ans=m*(m-1)/2;printf("%d\n",ans);
	if(k==0){
		for(int i=1;i<=m;i++) for(int j=i+1;j<=m;j++) printf("%d %d\n",i,j);
	}
	else
		for(int i=1;i<=m;i++) for(int j=i+1;j<=m;j++) printf("%d %d\n",j,i);
	return 0;
}
