# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=(~0U>>1)-1;
const int maxn=210;
struct tank{
	int x;
	tank(int x=0):x(x){}
	bool operator <(const tank &rhs)const{
		return x>rhs.x;
	}
};

priority_queue<int> heap2;
priority_queue<tank> heap1;
int n,k;
int a[maxn],sum[maxn];

void init(){
	while(!heap1.empty()) heap1.pop();
	while(!heap2.empty()) heap2.pop();
}
int main(){
	int res=-INF;
	scanf("%d%d",&n,&k);sum[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
	for(int l=1;l<=n;l++)
		for(int r=l;r<=n;r++){
			init();
			for(int kk=l;kk<=r;kk++){
				heap1.push(tank(a[kk]));
			}
			for(int kk=1;kk<l;kk++) heap2.push(a[kk]);
			for(int kk=r+1;kk<=n;kk++) heap2.push(a[kk]);
			int t=min(r-l+1,min(n-(r-l+1),k));
			int ans=sum[r]-sum[l-1];
			for(int j=1;j<=t;j++){
				if(heap1.top().x>=heap2.top()) break;
				ans+=heap2.top()-heap1.top().x;heap1.pop();heap2.pop();
			}
			res=max(res,ans);
			//printf("l:%d r:%d ans:%d\n",l,r,ans);
		}printf("%d\n",res);
	return 0;
}
