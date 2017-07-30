#include<stdio.h>
#include<string.h>
# include<set>
# include<map>
#include<algorithm>
using namespace std;
const int maxn=100010;
//vector<int> G[maxn];
typedef pair<int,int> pi;

map<pi,int> id;
set<int> s;
typedef set<int>::iterator it;
int n,m;
void dfs(int x){
	printf("%d\n",x);
	s.erase(x);
	for(it p=s.begin();p!=s.end();p++){
		int a=x,b=*p;if(a>b) swap(a,b);
		if(!id.count(pi(a,b))) {dfs(*p);return;}
	}
	return;
}

int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) s.insert(i);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);if(a>b) swap(a,b);
		//G[a].push_back(b);G[b].push_back(a);
		id[pi(a,b)]=1;
	}
	dfs(1);
	return 0;
}
