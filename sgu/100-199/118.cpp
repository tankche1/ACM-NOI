# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
int a[maxn],sum[maxn],n;

inline int get(int x){
	int ret=0;
	while(x) ret+=x%10,x/=10;
	return ret;
}
int main(){
	int tcase,ans;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sum[0]=1;
		for(int i=1;i<=n;i++)
			sum[i]=get(sum[i-1]*get(a[i]));
		ans=0;
		for(int i=1;i<=n;i++)
			ans+=sum[i];
		while(ans>=10)
			ans=get(ans);
		printf("%d\n",ans);
	}
	return 0;
}
