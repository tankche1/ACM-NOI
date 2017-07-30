# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=21;
const int maxm=1025*1025;
int n;
int val[maxm];
int main(){
	int c,v;
	while(scanf("%d",&n)!=EOF){
		if(n<0) break;memset(val,0,sizeof(val));
		for(int i=1;i<=n;i++){
			scanf("%d%d",&c,&v);val[c]+=v;
		}
		for(int i=1;i<=20;i++){
			for(int j=0;j<(1<<20);j++){
				if((j>>(i-1))&1) val[j]+=val[j^(1<<(i-1))];
			}
		}
		int ans=-1;
		for(int j=0;j<(1<<20);j++)
			if(val[j]>ans) ans=val[j];
		printf("%d\n",ans);
	}
	return 0;
}
