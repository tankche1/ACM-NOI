# include<stdio.h>
# include<string.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=500010;
int n;

struct Heap{
	LL val;
	Heap(LL val=0):val(val) {}
	bool operator < (const Heap &rhs)const{
		return val>rhs.val;
	}
};

priority_queue<Heap> heap;
LL ans;

int main()
{
	freopen("huffman.in","r",stdin);
	freopen("huffman.out","w",stdout);
	LL a,b;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&b);heap.push(Heap(b));
	}
	for(int i=1;i<n;i++){
		a=heap.top().val;
		heap.pop();b=heap.top().val;heap.pop();
		ans+=a+b;
		heap.push(Heap(a+b));
	}
	printf("%llu\n",ans);
	return 0;
}
