# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1010;

double P[maxn],f[maxn];
int main(){
	int T,n,k,m;
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++){
		scanf("%d%d%d",&n,&k,&m);
		for(int i=0;i<n;i++) scanf("%lf",&P[i]);
		f[0]=0;
		for(int i=1;i<=m;i++){
			f[i]=0;
			for(int j=0;j<n;j++){
				f[i]+=P[j]*pow(f[i-1],j);
			}
		}
		double ans=pow(f[m],k);
			printf("Case #%d: %.7lf\n",kase,ans);
		}
	return 0;
}
