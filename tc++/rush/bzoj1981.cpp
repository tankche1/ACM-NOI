#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=110;
const int maxl=100010;
const LL INF=(LL)1<<62;
LL L;
int n;
int B[maxn],maxB;
LL dist[maxl];bool inq[maxl];
int head,tail,q[maxl];

void add(int &x){
	x++;if(x==maxl) x=0;
}
int main(){
	int tcase,T=0;
	//printf("%lld\n",INF);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%lld%d",&L,&n);
		maxB=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&B[i]),maxB=max(maxB,B[i]);
		for(int i=1;i<maxB;i++) dist[i]=INF;
		dist[0]=L/maxB;head=-1;
		q[tail=0]=0;memset(inq,0,sizeof(inq));
		while(head!=tail){
			add(head);
			int x=q[head];inq[x]=false;
			for(int i=1;i<=n;i++){
				LL nc=x+B[i]>=maxB?dist[x]:dist[x]+1;
				int nx=(x+B[i])%maxB;
				if(dist[nx]>nc){
					dist[nx]=nc;
					if(!inq[nx])
						inq[nx]=1,add(tail),q[tail]=nx;
				}
			}
		}
		printf("Case #%d: ",++T);
		if(dist[L%maxB]==INF) puts("IMPOSSIBLE");
		else printf("%lld\n",dist[L%maxB]);
	}
	return 0;
}
/*
100
1000000000000000000 5
99999 1000 9999 22222 33333
*/
