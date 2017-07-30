#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=50010;
LL n;
LL dp[maxn];
struct square{
	LL a,b;
	bool operator < (const square &rhs)const{
		return b<rhs.b;
	}
};
square A[maxn],B[maxn];
bool cmp(square x,square y){
	if(x.a	!=y.a) return x.a>y.a;return x.b>y.b;
}

inline LL X(int j) {return A[j+1].a;}
inline LL Y(int j) {return dp[j];}
inline LL get(int i,int j) {return dp[j]+A[i].b*A[j+1].a;}

bool Cross(int i,int j,int k){//k(i,j)>=k(j,k)
	return (Y(i)-Y(j))*(X(j)-X(k))>=(X(i)-X(j))*(Y(j)-Y(k));
}

int q[maxn],head,tail;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&B[i].a,&B[i].b);
	sort(B+1,B+n+1,cmp);
	int m=0;
	LL wide=-1;
	for(int i=1;i<=n;i++){
		if(B[i].b>wide) A[++m]=B[i];
		wide=max(wide,B[i].b);
	}
	n=m;
	sort(A+1,A+n+1);A[n+1].a=0;
	dp[0]=0;q[head=tail=0]=0;
	for(int i=1;i<=n;i++){
		while(head<tail&&get(i,q[head])>=get(i,q[head+1])) head++;
		dp[i]=get(i,q[head]);
		while(tail>head&&Cross(i,q[tail],q[tail-1])) tail--;
		q[++tail]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
