#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=14;
bool used[maxn];
int n,A[maxn];
bool ok;

void dfs(int cur,int now,bool qu){
	if(qu&&now==0){ok=true;return;}
	if(cur==n) return;
	dfs(cur+1,now,qu);
	dfs(cur+1,now^A[cur],1);
}

int main(){
	for(int tcase=1;tcase<=10;tcase++){
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			scanf("%d",&A[i]);
		ok=false;
		dfs(0,0,0);
		if(ok) puts("NO");
			else puts("YES");
	}
	return 0;
}
