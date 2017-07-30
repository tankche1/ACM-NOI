# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n;
int main(){
	scanf("%d",&n);
	int ans=n/3*2;
	n-=n/3*3;
	if(n!=0) ans+=n-1;
		printf("%d\n",ans);
	return 0;
}
