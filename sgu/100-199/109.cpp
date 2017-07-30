# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n;
# define pos(x,y) ((x-1)*n+y)
int main(){
	scanf("%d",&n);
	int K=n;
	/*if(n%2==0){
		printf("%d %d\n",K,n*n);
	}
	else{
		printf("%d %d\n",K,n*n);
	}K-=2;*/
	if(n==2){
		printf("3 4\n5 2 3\n");return 0;
	}
	printf("%d",n);if(!(n&1)) K++;else K+=2;
	for(int i=1;i<=n;i++){
		for(int j=i-2;j>0;j--)
			printf(" %d",pos(i,n+1-j));
	}puts("");
	for(int i=n-1;i<2*n-1;i++,K+=2){
		printf("%d",K);
		int limit=i<=n?i:2*n-i;
		for(int j=limit;j>=1;j--){
			if(i<=n)
			printf(" %d",pos(n+1-j,n-i+j));
			else
				printf(" %d",pos(n-(i-n)-j+1,j));
		}
		puts("");
	}
	return 0;
}
