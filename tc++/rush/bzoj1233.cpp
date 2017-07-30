#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n;
int w[maxn];
int f[maxn],area[maxn],sum[maxn];
int q[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	reverse(w+1,w+n+1);sum[0]=0;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+w[i];
	f[0]=0;area[0]=0;
	int head=0,tail=-1;
	q[++tail]=0;
	for(int i=1;i<=n;i++){
		while(head<=tail&&sum[i]-sum[q[head]]>=area[q[head]]) head++;
		head--;
		f[i]=f[q[head]]+1;area[i]=sum[i]-sum[q[head]];//printf("f[%d]:%d %d\n",i,f[i],q[head]);
		while(tail>=head&&area[i]+sum[i]<=area[q[tail]]+sum[q[tail]]) tail--;
		q[++tail]=i;
	}
	printf("%d\n",f[n]);
	return 0;
}
