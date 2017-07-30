# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int a[maxn],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	bool ok=true;
	if(n%2==0){
		for(int i=1;i<n;i+=2)
			if(a[i]!=a[i+1]) goto Loop;
		ok=false;
	}
	Loop:
	if(ok) puts("first player");
		else puts("second player");
	return 0;
}
