# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=155;
int d[maxn];
int n;
int h[maxn];

void add_h(int x,int val){
	for(int i=2;i<=x;i++)
		while(x%i==0) x/=i,h[i]++;//printf("i:%d\n",i);
}

int main(){
	int sum=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&d[i]),sum+=d[i];
	if(sum!=2*n-2) {puts("0");return 0;}
	memset(h,0,sizeof(h));
	for(int i=2;i<=n-2;i++){
		add_h(i,1);
	}
	for(int i=1;i<=n;i++){
		if(d[i]==0&&n>1) {puts("0");return 0;}
		add_h(d[i]-1,-1);
	}
	long long ans=1;
	for(int i=1;i<=n;i++)
		while(h[i]) ans*=i,h[i]--;
			printf("%lld\n",ans);
	return 0;
}
