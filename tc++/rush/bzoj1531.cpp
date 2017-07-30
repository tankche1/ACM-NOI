# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=205;
const int maxc=20005;
const int INF=maxc<<1;
int f[maxc];
int v[maxn],c[maxn],n;
int Cost;
struct state{
	int cost,num;
	state(int cost=0,int num=0):cost(cost),num(num) {}
};

int main(){
	for(int i=0;i<maxc;i++) f[i]=INF;
	f[0]=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	scanf("%d",&Cost);	
	int head,tail;
	state Q[maxc];
	for(int i=1;i<=n;i++){
		for(int j=0;j<v[i];j++){
			tail=0;head=-1;
			Q[++head]=state(f[j],0);
			for(int k=1;j+k*v[i]<=Cost;k++){
				int o=f[j+k*v[i]];
				while(tail<=head&&c[i]-Q[tail].num<k) tail++;
				if(head>=tail) f[j+k*v[i]]=min(f[j+k*v[i]],Q[tail].cost+k);
				while(head>=tail&&o-k<=Q[head].cost) head--;
				Q[++head]=state(o-k,-k);
			}
		}
	}
	printf("%d\n",f[Cost]);
	return 0;
}
/*
1
5 
10
25
*/
