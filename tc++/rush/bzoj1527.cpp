# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int n;
struct Duty{
	int t,v;
};
Duty duty[maxn];
bool cmp(Duty a,Duty b){
	return a.t<b.t;
}

struct HeapNode{
	int val;
	HeapNode(int val):val(val) {}
	bool operator < (const HeapNode &rhs)const{
		return val<rhs.val;
	}
};
priority_queue<HeapNode> Q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&duty[i].t,&duty[i].v);
	sort(duty+1,duty+n+1,cmp);
	int last=1000000000;
	LL ans=0;
	for(int i=n;i>=1;i--){
		int len=last-duty[i].t;
		int k=i;
		while(duty[k-1].t==duty[i].t) k--;
		for(int j=0;j<len&&(!Q.empty());j++){
			ans+=Q.top().val;Q.pop();
		}
		for(int j=i;j>=k;j--) Q.push(HeapNode(duty[j].v));
		i=k;last=duty[i].t;
	}
	int len=last;
	for(int j=0;j<len&&(!Q.empty());j++){
			ans+=Q.top().val;Q.pop();
		}
	printf("%lld\n",ans);
	return 0;
}
