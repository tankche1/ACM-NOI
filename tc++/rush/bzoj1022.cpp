# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=52;
int T,n,a[maxn],sg=0;
int main(){
	scanf("%d",&T);
	while(T--){
		sg=0;
		scanf("%d",&n);bool ok=true;
		for(int i=1;i<=n;i++) 
		{scanf("%d",&a[i]);sg=sg^a[i];if(a[i]>1) ok=false;}
		if(ok) printf("%s\n",sg==0?"John":"Brother");
		else printf("%s\n",sg>0?"John":"Brother");
	}
	return 0;
}
