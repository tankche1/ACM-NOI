# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int a[10010],sum[10010];

int tcase,num,n,ans;
bool check(int x){
	int now=0;
	for(int i=1;i<=n;i++){
		if(sum[i]-sum[now]==x) now=i;
		if(sum[i]-sum[now]>x) return false;
	}
	if(now!=n) return false;
	return true;
}

int main(){
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&num,&n);sum[0]=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
		for(int i=n;i>=1;i--){
			if(check(sum[i])) ans=sum[i];
		}
		printf("%d %d\n",num,ans);
	}
	return 0;
}
