# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n;
int main(){
	scanf("%d",&n);
	int ans=n;
	for(int i=2;i<=n;i++){
		int c=0;
		while(n%i==0) c++,n/=i;
		if(c) ans=ans*(i-1)/i;
	}
	printf("%d\n",ans);
	return 0;
}
