# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxt=1000010;
int ans=0,n,l,r,sum;
int val[maxt];
int main(){
	memset(val,0,sizeof(val));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&l,&r),val[l]++,val[r+1]--;
	for(int i=1;i<maxt;i++){
		sum+=val[i];
		if(sum>ans) ans=sum;
	}
	printf("%d\n",ans);
	return 0;
}
