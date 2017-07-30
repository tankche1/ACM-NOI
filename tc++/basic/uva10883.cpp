# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=50010;
double log_C[maxn];
int n;double a[maxn];
int main(){
	int T;
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%lf",&a[i]);
		log_C[0]=0;
		for(int i=1;i<=n-1;i++)//log(C(n,i))
			log_C[i]=log_C[i-1]+log10((n-1)+1-i)-log10(i);
		double ans=0;
		for(int i=1;i<=n;i++){
			if(a[i]>0)
			ans+=pow(10,log_C[i-1]+log10(a[i])-log10(2)*(n-1));
			else 
				ans-=pow(10,log_C[i-1]+log10(-a[i])-log10(2)*(n-1));
		}
		  printf("Case #%d: %.3lf\n",kase,ans);
	}
	return 0;
}
