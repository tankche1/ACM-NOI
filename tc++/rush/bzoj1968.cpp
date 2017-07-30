# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int main(){
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		ans+=n/i;
	printf("%d\n",ans);
	return 0;
}
