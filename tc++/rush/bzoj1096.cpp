#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1000010;
typedef long long LL;
int n;
LL dist[maxn],cost[maxn],sump[maxn],c[maxn],p[maxn];
int q[maxn],head,tail;
LL f[maxn];

LL X(int j){return dist[j-1];}
LL Y(int j) {return c[j-1]+f[j]-cost[j]+sump[j]*dist[j-1];}
LL K(int i) {return sump[i];}

bool check(int a,int b,int c){
	//return (Y(b)-Y(a))/(X(b)-X(a))<=K(c);
	return (Y(b)-Y(a))<=K(c)*(X(b)-X(a));//a>b
}

bool Slope(int a,int b,int c){
	return (Y(c)-Y(b))*(X(b)-X(a))>(Y(b)-Y(a))*(X(c)-X(b));
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&dist[i],&p[i],&c[i]);
	}
	for(int i=1;i<=n;i++)
		dist[i]=dist[n]-dist[i];
	sump[n+1]=0;
	for(int i=n;i>=1;i--)
		sump[i]=sump[i+1]+p[i],cost[i]=cost[i+1]+dist[i]*p[i];
	f[n+1]=0;c[0]=0;cost[n+1]=0;
	q[head=tail=0]=n+1;
	for(int i=n;i>=1;i--){
		while(head<tail&&check(q[head],q[head+1],i)) head++;
		//	printf("Y:%d K:%d X:%d\n",Y(q[head]),K(i),X(q[head]));
		f[i]=cost[i]+Y(q[head])-K(i)*X(q[head]);
		//printf("%d\n",f[i]);
		while(tail>head&&(!Slope(q[tail-1],q[tail],i))) tail--;
		q[++tail]=i;
	}
	printf("%lld\n",f[1]);
	return 0;
}
