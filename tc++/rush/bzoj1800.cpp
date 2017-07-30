# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n;
int a[22];
int sum[22];
int main(){
	scanf("%d",&n);
	sum[0]=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);sum[i]=sum[i-1]+a[i];
	}
	int all=sum[n];
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			for(int k=j+1;k<=n;k++)
				if(sum[k]-sum[i]==all/2)
				for(int l=k+1;l<=n;l++){
					if(sum[l]-sum[j]==all/2)
						ans++;
				}
		}
	}
	printf("%d\n",ans);
	return 0;
}
