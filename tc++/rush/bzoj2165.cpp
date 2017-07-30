#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=105;
const LL INF=(LL)1<<61;
LL n,m;
LL g[maxn][maxn][maxn];
LL p[maxn],q[maxn];

inline void checkmax(LL &x, LL y) {    if (y > x)        x = y;}
inline void checkmin(LL &x, LL y) {    if (y < x)        x = y;}

int main(){
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				scanf("%lld",&g[i][j][0]);
				checkmin(g[i][j][0],m);
			}
		LL t,ans;
		for(ans=0;;ans++){
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++){
					g[i][j][ans+1]=0;
					for(int k=1;k<=n;k++)
						if(g[i][k][ans]&&g[k][j][ans]) checkmax(g[i][j][ans+1],g[i][k][ans]+g[k][j][ans]);
					checkmin(g[i][j][ans+1],m);
				}t=0;
			for(int j=1;j<=n;j++)
				checkmax(t,g[1][j][ans]);
			if(t>=m) break;
		}
		memset(p,0,sizeof(p));m++;
		LL tot=0;p[1]=1;for(int i=2;i<=n;i++) p[i]=0;
		for(;ans>=0;){
			if(ans) ans--;
			LL t=0;
			for(int i=1;i<=n;i++) q[i]=p[i];
			for(int i=1;i<=n;i++){
				LL res=-INF;
				for(int j=1;j<=n;j++){
					if(q[j]&&g[j][i][ans]) checkmax(res,q[j]+g[j][i][ans]);
				}checkmin(res,m);
				p[i]=res;checkmax(t,res);
			}
			if(t<m||ans==0){
				tot+=(LL)1<<ans;
				if(ans==0&&t>=m) break;
			}
			else for(int i=1;i<=n;i++) p[i]=q[i];
		}
		printf("%lld\n",tot);
	}
	return 0;
}
