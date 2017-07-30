# include<stdio.h>
# include<string.h>
# include<algorithm>
# include <map>
typedef long long LL;
#define maxn 1010000
using namespace std;
const LL mod = 1000000007;

LL l,ans;
map<int,int> id;
LL sum[maxn],tank[maxn];
int A[maxn],n,k,tp;

int main() {
	scanf("%d%I64d%d",&n,&l,&k);
	for (int i=0;i<n;i++) {scanf("%d",&A[i]);id[A[i]] = 1;}
	tp=0;
	for(map<int,int> :: iterator i = id.begin();i != id.end();i++) i -> second = ++tp;
	for (int i = 1; i <= tp; i++) sum[i] = 1;
	for (int i = 0; i < n; i++) A[i] = id[A[i]];
	for (int x = 1; x <= k; x++) {
		for (int i = 0; i < n; i++) {
			tank[i] = sum[A[i]];
			if (i < (l % n)) {
				if (((l/(LL)n)%mod+1LL-(LL)x+1LL)>0)
				ans+=sum[A[i]]*((l/(LL)n)%mod+1LL-(LL)x+1LL)%mod;
			}
			else {
				if ((l/(LL)n-(LL)x+1LL)>0)
					ans+=sum[A[i]]*((l/(LL)n-(LL)x+1LL)%mod)%mod;
			}
			ans %= mod;
		}
		for (int i = 1; i <= tp; i++) sum[i] = 0;
		for (int i = 0; i < n; i++) sum[A[i]] += tank[i], sum[A[i]] %= mod;
		for (int i = 1; i <= tp; i++) sum[i] += sum[i - 1], sum[i] %= mod;
	}
	printf("%I64d\n",ans);
	return 0;
}
