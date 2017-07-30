# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL d[2][1<<10];

int m,n;
int main(){
	while(scanf("%d%d",&n,&m)!=EOF){
		if(n<m) swap(n,m);
		memset(d,0,sizeof(d));
		d[0][(1<<m)-1]=1;
		int cur=0,b;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cur=cur^1;
				memset(d[cur],0,sizeof(d[cur]));
				//printf("i:%d j:%d\n",i,j);
				for(int a=0;a<(1<<m);a++)
					if(d[cur^1][a]){//printf("a:%d  %d\n",a,a&(1<<(m-1)));
						if((a&(1<<(m-1)))>0) {b=(a<<1)^(1<<m);d[cur][b]+=d[cur^1][a];//printf("%d\n",b);
							}
						if(i&&(!(a&(1<<(m-1))))) {b=(a<<1)^1;d[cur][b]+=d[cur^1][a];//printf("%d\n",b);
							}
						if(j&&(!(a&1))&&(a&(1<<(m-1)))) {b=(a<<1)^(1<<m)^3;d[cur][b]+=d[cur^1][a];//printf("%d\n",b);
							}
					}
				}
		}
		printf("%lld\n",d[cur][(1<<m)-1]);
	}
	return 0;
}
