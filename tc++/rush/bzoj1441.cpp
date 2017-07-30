# include<stdio.h>
inline int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}
int main(){
	int n,x,ans;
	scanf("%d",&n);
	scanf("%d",&ans);
	for(int i=1;i<n;i++){
		scanf("%d",&x);if(x<0) x=-x;
		ans=gcd(ans,x);
	}
	printf("%d\n",ans);
	return 0;
}
