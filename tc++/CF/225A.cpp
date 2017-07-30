#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int n;
bool col[1010][1010];
int main(){
	scanf("%d",&n);
	int black=n*(n/2);
	if(n&1) black+=(n+1)/2;
	printf("%d\n",black);
	for(int i=1;i<=n;i++) col[1][i]=i&1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=n;j++)
		col[i][j]=col[i-1][j]^1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			if(col[i][j]) printf("C");else printf(".");puts("");}
	return 0;
}
