# include<stdio.h>
# include<string.h>
# include<stack>
# include<algorithm>
using namespace std;
const int maxn=50010;
int n,x;
int h[maxn];
int main(){
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&h[i]);
	}
	stack<int> S;
	int ans=0;
	for(int i=1;i<=n;i++){
		while(!S.empty()&&h[S.top()]>=h[i]) ans+=h[S.top()]!=h[i],S.pop();
			S.push(i);
	}
	while(!S.empty()) ans+=h[S.top()]!=0,S.pop();
	printf("%d\n",ans);
	return 0;
}
