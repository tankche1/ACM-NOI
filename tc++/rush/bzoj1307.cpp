#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1000010;
typedef long long LL;
int n;
int A[maxn];
int pos[maxn];
int r[maxn];
LL sum[maxn];

void prepare(){
	for(int i=1;i<maxn;i++) pos[i]=n+1;
	r[n+1]=n;
	for(int i=n;i>=1;i--)
		r[i]=min(pos[A[i]]-1,r[i+1]),pos[A[i]]=i;
}
int ans=0;

void Renew(){
	int p=0;sum[0]=0;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+A[i];
	for(int i=1;i<=n;i++)
		if(A[i]==1){
			int _max=0;
			for(int l=i;l>p;l--){
				_max=max(_max,A[l]);
				if(r[l]-l+1<_max) continue;
				if(sum[l+_max-1]-sum[l-1]==(LL)(_max+1)*_max/2){
					ans=max(ans,_max);
				}
			}
			p=i;
		}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	prepare();
	Renew();
	reverse(A+1,A+n+1);
	prepare();
	Renew();
	printf("%d\n",ans);
	return 0;
}
