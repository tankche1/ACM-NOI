# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
struct state{
	int a,b;
	bool operator <(const state &rhs)const{
		return a+b<rhs.a+rhs.b;
	}
};
state h[maxn];
int n,ans=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&h[i].a,&h[i].b);
	sort(h+1,h+n+1);
	for(int i=1;i<=n/2;i++)
		ans+=min(h[i].a,h[i].b);
	for(int i=n/2+1;i<=n;i++)
		ans-=max(h[i].a,h[i].b);
	printf("%d\n",ans);
	return 0;
}
