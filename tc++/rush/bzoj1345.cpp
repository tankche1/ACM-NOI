# include<stdio.h>
# include<string.h>
# include<stack>
# include<algorithm>
using namespace std;
const int maxn=1000010;
int a[maxn],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		stack<int> S;
	long long ans=0;
	for(int i=1;i<=n;i++){
		if((!S.empty())&&a[S.top()]<=a[i]){
			S.pop();ans+=a[i];
		while((!S.empty())&&a[S.top()]<=a[i]) {
			ans+=a[S.top()];S.pop();
		}
	}
	S.push(i);
	}
	S.pop();
	while(!S.empty()){
		ans+=a[S.top()];S.pop();
	}
	printf("%lld\n",ans);
	return 0;
}
