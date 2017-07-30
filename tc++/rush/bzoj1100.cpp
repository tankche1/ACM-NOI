#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
const int INF=~0U>>1;
int n;
LL x[maxn],y[maxn];
LL s[maxn<<3];
int cnt=0;

inline LL sqr(LL x) {return x*x;}

int p[maxn<<3];

void Manacher(int n){
	int mx=0,id=0;//memset(p,0,sizeof(p));
	p[0]=1;
	for(int i=1;i<n;i++){
		if(mx>i)
		p[i]=min(p[id*2-i],mx-i);
		else p[i]=1;
		while(i+p[i]<n&&i-p[i]>=0&&s[i+p[i]]==s[i-p[i]]) p[i]++;
		if(i+p[i]-1>mx) mx=i+p[i]-1,id=i;
	}
}

int main(){
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		cnt=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld%lld",&x[i],&y[i]);
		x[n+1]=x[1];y[n+1]=y[1];x[n+2]=x[2];y[n+2]=y[2];
		for(int i=1;i<=n;i++){
			s[cnt++]=sqr(x[i+1]-x[i])+sqr(y[i+1]-y[i]);
			s[cnt++]=INF;
			s[cnt++]=(x[i+1]-x[i])*(y[i+2]-y[i+1])-(x[i+2]-x[i+1])*(y[i+1]-y[i]);
			s[cnt++]=INF;
		}
		for(int i=0;i<cnt;i++)
			s[i+cnt]=s[i];
		cnt<<=1;
		//for(int i=0;i<cnt;i++) printf("%d ",s[i]);puts("");
		Manacher(cnt);
		//for(int i=0;i<cnt;i++) printf("p[%d]:%d\n",i,p[i]);
		int ans=0;
		for(int i=0;i<cnt;i++) if(p[i]-1>=2*n) ans++;
		printf("%d\n",ans/2);
	}
	return 0;
}
