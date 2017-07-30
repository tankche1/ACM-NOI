# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
typedef long long LL;
int n;
int a[maxn];
LL s[maxn];
int main(){
	LL sum=0,avg;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);sum+=a[i];
	}
	avg=sum/n;
	s[1]=0;
	for(int i=2;i<=n;i++)
		s[i]=s[i-1]+a[i-1]-avg;
	for(int i=1;i<=n;i++) s[i]=-s[i];
	sort(s+1,s+n+1);
	LL k=n%2==0?(s[n/2]+s[n/2+1])/2:s[n/2+1];
	LL ans=0;
	for(int i=1;i<=n;i++){
		ans+=abs(k-s[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
