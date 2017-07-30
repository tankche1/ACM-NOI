# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
int n;
int a[maxn],b[maxn];
int main(){
	int u;
	scanf("%d",&u);
	while(u--){
	scanf("%d",&n);
	a[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<n;i++)
		b[i]=a[i+1]-a[i];
	int ans=0;
	for(int i=0;i<n;i++)
		if((i&1)!=(n&1)) ans=ans^b[i];
	if(!ans) puts("NIE");
		else puts("TAK");
	}
	return 0;
}
