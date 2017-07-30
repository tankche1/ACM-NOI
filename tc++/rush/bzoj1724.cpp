# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=20005;
int n,a[maxn];

int main(){
	scanf("%d",&n);
	priority_queue<int> q;
	for(int i=1;i<=n;i++)
	{scanf("%d",&a[i]);q.push(-a[i]);}
	long long ans=0;
	for(int i=1;i<n;i++){
		int x=q.top();q.pop();
		int y=q.top();q.pop();
		ans+=-(x+y);
		q.push(x+y);
	}
	printf("%lld\n",ans);
	return 0;
}
