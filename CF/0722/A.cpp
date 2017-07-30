# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int ans=0;
int a[7];
int get(int a) {return a*a;}
int num(int a) {return 2*a+1;}
int main(){
	for(int i=1;i<=6;i++) scanf("%d",&a[i]);
	ans+=get(a[1]+a[5]+a[6]);
	ans-=get(a[1]);
	ans-=get(a[5]);
	ans-=get(a[3]);
	printf("%d\n",ans);
	return 0;
}
