#include<stdio.h>
#include<string.h>
# include<vector>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=52;
priority_queue<int> len[maxn];
int k;

struct HeapNode{
	int col,val;
	HeapNode(int col=0,int val=0):col(col),val(val) {}
	bool operator < (const HeapNode &rhs)const{
		return val<rhs.val;
	}
};
priority_queue<HeapNode> Q;

int main(){
	int x,aa;
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		scanf("%d",&x);
		while(x--){
			scanf("%d",&aa),len[i].push(aa);
		}
	}
	for(int i=1;i<=k;i++)
		Q.push(HeapNode(i,len[i].top())),len[i].pop();
	while(Q.size()>2){
		HeapNode a=Q.top();Q.pop();HeapNode b=Q.top();Q.pop();HeapNode c=Q.top();Q.push(b);
		if(b.val+c.val>a.val){
			printf("%d %d %d %d %d %d\n",a.col,a.val,b.col,b.val,c.col,c.val);return 0;
		}
		if(!len[a.col].empty())
			Q.push(HeapNode(a.col,len[a.col].top())),len[a.col].pop();
	}
	puts("NIE");
	return 0;
}
