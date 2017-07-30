# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int ans=0;
inline bool get(int a,int b){
	if(a>b) swap(a,b);
		if(!a) return true;
		//	printf("%d %d\n",a,b);
	if(a%2==0&&b%2==0) a/=2,b/=2;
	else if((a+b)%2==1) return false;
	else b-=a,a*=2,ans++;
	return get(a,b);
}
int a,b;
int main(){
	scanf("%d%d",&a,&b);
	bool ok=get(a,b);
	if(!ok) puts("-1");
		else
	printf("%d\n",ans);
	return 0;
}
