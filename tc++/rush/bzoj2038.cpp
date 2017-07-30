#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
const int maxn=50010;
int n,m;
int c[maxn];
int num[maxn];

struct Ask{
	int l,r,w,s;
	bool operator < (const Ask &rhs)const{
		return rhs.w==w?r<rhs.r:w<rhs.w;
	}
};
Ask A[maxn];
int ans[maxn];
int gcd(int a,int b){
	if(a==0) return b;
	return gcd(b%a,a);
}
int length[maxn];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	int len=sqrt(m),cnt=ceil(m/(len*1.0));
	for(int i=1;i<=m;i++){
		scanf("%d%d",&A[i].l,&A[i].r);
		A[i].w=ceil(A[i].l/(len*1.0));
		A[i].s=i;
		length[i]=A[i].r-A[i].l+1;
	}
	sort(A+1,A+m+1);memset(ans,0,sizeof(ans));
	for(int i=1;i<=m;i++){
		memset(num,0,sizeof(num));
		for(int j=A[i].l;j<=A[i].r;j++) ans[A[i].s]+=num[c[j]]++;
		int now=A[i].w;i++;
		for(;A[i].w==now;i++){
			ans[A[i].s]=ans[A[i-1].s];
			for(int j=A[i-1].r+1;j<=A[i].r;j++)
				ans[A[i].s]+=num[c[j]]++;
			if(A[i].l>A[i-1].l)
				for(int j=A[i-1].l;j<A[i].l;j++)
					ans[A[i].s]-=--num[c[j]];
			else
				for(int j=A[i].l;j<A[i-1].l;j++)
					ans[A[i].s]+=num[c[j]]++;
		}
		i--;
	}
	for(int i=1;i<=m;i++){
		if(ans[i]==0) puts("0/1");
		else{
			int a=ans[i],b=(long long)length[i]*(length[i]-1)/2;//printf("a:%d b:%d\n",a,b);
			int d=gcd(a,b);a/=d;b/=d;
			printf("%d/%d\n",a,b);
		}
	}
	return 0;
}
