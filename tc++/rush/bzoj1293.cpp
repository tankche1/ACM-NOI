# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxk=65;
const int INF=~0U>>1;
int n,k;
struct HeapNode{
	int x,kind,num;
	HeapNode() {}
	HeapNode(int x,int kind,int num) :x(x),kind(kind),num(num) {}
	bool operator < (HeapNode rhs) const{
		return x>rhs.x;
	}
};

int len[maxk];
vector<int> ball[maxk];

int main(){
	int pos;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++){
		scanf("%d",&len[i]);
		for(int j=1;j<=len[i];j++){
			scanf("%d",&pos);
			ball[i].push_back(pos);
		}
	}
	priority_queue<HeapNode> q;
	int now_max=0,ans=INF;
	for(int i=1;i<=k;i++){
		q.push(HeapNode(ball[i][0],i,1));
		now_max=max(now_max,ball[i][0]);
	}
	while(1){
		HeapNode now=q.top();q.pop();
		ans=min(ans,now_max-now.x);
		if(len[now.kind]==now.num) break;
		q.push(HeapNode(ball[now.kind][now.num],now.kind,now.num+1));
		now_max=max(now_max,ball[now.kind][now.num]);
	}
	printf("%d\n",ans);	
	return 0;
}
