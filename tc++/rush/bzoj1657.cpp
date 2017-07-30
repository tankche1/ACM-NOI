# include<stdio.h>
# include<string.h>
# include<stack>
# include<algorithm>
using namespace std;
const int maxn=50010;
int h[maxn],v[maxn],q[maxn];
int ans[maxn];
int n;
stack<int> S;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&h[i],&v[i]);
	for(int i=1;i<=n;i++){
		ans[i]=0;
		while(!S.empty()&&h[S.top()]<h[i]) ans[i]+=v[S.top()],S.pop();
		S.push(i);
	}
	while(!S.empty()) S.pop();
		int result=0;
	for(int i=n;i>=1;i--){
		while(!S.empty()&&h[S.top()]<h[i]) ans[i]+=v[S.top()],S.pop();
		S.push(i);
		if(ans[i]>result) result=ans[i];
	}
	printf("%d\n",result);
	return 0;
}
