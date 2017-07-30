#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1000010;
typedef long long LL;
int n;
LL f[maxn],a[maxn],b[maxn],sumb[maxn],cost[maxn];

LL K(int i) {return i;}
LL X(int j) {return sumb[j];}
LL Y(int j) {return f[j]+cost[j];}
LL C(int i) {return a[i]-cost[i]+sumb[i]*i;}

bool check(int a,int b,int c){
	//return (Y(b)-Y(a))/(X(b)-X(a))>K(c);
	return (Y(b)-Y(a))<K(c)*(X(b)-X(a));
}

bool Slope(int a,int b,int c){
	//return (Y(b)-Y(a))/(X(b)-X(a))>(Y(c)-Y(b))/(X(c)-X(b));
	return (Y(b)-Y(a))*(X(c)-X(b))<(X(b)-X(a))*(Y(c)-Y(b));
}

int q[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%lld",&b[i]);
	cost[0]=0;
	for(int i=1;i<=n;i++)
		cost[i]=cost[i-1]+b[i]*i;
	sumb[0]=0;
	for(int i=1;i<=n;i++)
		sumb[i]=sumb[i-1]+b[i];
	int head,tail;
	f[0]=0;q[head=tail=0]=0;
	for(int i=1;i<=n;i++){
		while(head<tail&&check(q[head],q[head+1],i)) head++;
		f[i]=-K(i)*X(q[head])+Y(q[head])+C(i);
		//printf("f[%d]:%d\n",i,f[i]);
		while(tail>head&&(!Slope(q[tail-1],q[tail],i))) tail--;
		q[++tail]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}
