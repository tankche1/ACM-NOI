# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=5010;
const int INF=~0U>>1;
int n;
int a[maxn];
int b[maxn];
int main(){
	char t;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		while((t=getchar())&&t!='B'&&t!='F');
		a[i]=t=='B'?1:0;
	}
	int ans=INF,ansk;
	for(int k=1;k<=n;k++){
		int now=0;
		memset(b,0,sizeof(b));
		int num=0;
		int i;
		for(i=1;i+k-1<=n;i++){
			if((a[i]+now)%2!=0) now++,b[i+k-1]++,num++;
			now-=b[i];
		}
		bool ok=true;
		for(;i<=n;i++){
			if((a[i]+now)%2!=0) {ok=false;break;}
			now-=b[i];
		}
		if(ok){
			if(num<ans) ans=num,ansk=k;
		}
	}
	printf("%d %d\n",ansk,ans);
	return 0;
}
