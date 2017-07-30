# include<stdio.h>
# include<string.h>
# include<map>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=10010;
int n,m;
map<int,int> id;
int use;
int vis[maxn];

struct HeapNode{
	int find_cnt,ti,bh;
	HeapNode() {}
	HeapNode(int find_cnt,int ti,int bh) :find_cnt(find_cnt),ti(ti),bh(bh) {}
	bool operator < (HeapNode rhs)const{
		if(find_cnt!=rhs.find_cnt)
		return find_cnt>rhs.find_cnt;
		return ti>rhs.ti;
	}
};

int main(){
	scanf("%d%d",&n,&m);
	use=0;
	int ans=0;
	priority_queue<HeapNode> q;
	for(int i=1;i<=m;i++){
		int go;
		scanf("%d",&go);
		if(id.count(go)){//a
			vis[id[go]]++;
			ans++;
		}
		else if(use<n){//b
			id[go]=++use;
			vis[use]=0;
			q.push(HeapNode(0,i,go));
		}
		else{//c
			HeapNode now;
			while(1){
				now=q.top();q.pop();
				if(vis[id[now.bh]]>0) q.push(HeapNode(now.find_cnt+vis[id[now.bh]],now.ti,now.bh)),vis[id[now.bh]]=0;
				else break;
			}
			id[go]=id[now.bh];
			q.push(HeapNode(0,i,go));
			id.erase(now.bh);
		}
	}
	printf("%d\n",ans);
	return 0;
}
