# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
int n,b;
int a[maxn];
int sum[maxn<<1];
int main(){
	scanf("%d%d",&n,&b);
	int posb;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);if(a[i]==b) posb=i;
	}
	int now=0;
	memset(sum,0,sizeof(sum));
	sum[0+maxn]=1;
	for(int i=posb-1;i>=1;i--){
		now+=a[i]<b?-1:1;
		sum[now+maxn]++;
	}
	now=0;
	long long ans=sum[0+maxn];
	for(int i=posb+1;i<=n;i++){
		now+=a[i]<b?-1:1;
		ans+=sum[-now+maxn];
	}
	printf("%lld\n",ans);
	return 0;
}
