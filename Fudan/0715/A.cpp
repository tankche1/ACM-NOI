# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int winner;
int n;
const int maxn=110;
int a[maxn],b[maxn];

int SG(int x,int y){
	LL now=1;
	while(x>=now) now*=2;
	now/=2;now--;if(y<=now) return 1;
	return 0;
}

void print(int ans){
	if(ans==1) puts("Alice");
	else puts("Bob");
}

int main(){
	//freopen("in.txt","r",stdin);
	int Tcase,t=0;
	/*while(1){
		scanf("%d",&t);
		for(int i=1;i<=t;i++)
			printf("SG(%d,%d):%d\n",t,i,SG(t,i));
	}*/
	scanf("%d",&Tcase);
	while(Tcase--){
		printf("Case %d: ",++t);
		scanf("%d",&n);
		winner=2;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i],&b[i]);
		}
		if(n==1){
			print(SG(a[1],b[1]));continue;
		}
		int ans=SG(a[1],b[1])^SG(a[2],b[2]);
		for(int i=3;i<=n;i++)
			ans=ans^SG(a[i],b[i]);
		print(ans);
	}
	return 0;
}
