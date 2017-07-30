# include<stdio.h>
# include<queue>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
int n;
int ans[maxn];

struct cell{
	int op,p;
	cell() {}
};
cell c[maxn];

struct Heap{
	int val,index;
	Heap() {}
	Heap(int val,int index):val(val),index(index) {}
	bool operator < (const Heap &rhs)const{
		return val<rhs.val;
	}
};

priority_queue<Heap>heap;

int main(){
	char t;
	scanf("%d",&n);n--;
	for(int i=1;i<=n;i++){
		while((t=getchar())&&t!='d'&&t!='p');
		if(t=='d') c[i].op=0;else c[i].op=1;
		scanf("%d",&c[i].p);if(c[i].op==1) c[i].p--;
	}
	c[0].op=1;c[0].p=0;
	int gold=0;
	int limit=2*n,kill=0,num;
	ans[0]=0;
	for(int i=n-1;i>=0;i--){
		//printf("c[%d] op:%d p:%d\n",i,c[i].op,c[i].p);
		if(c[i].op==0){
			heap.push(Heap(c[i].p,i));continue;
		}
		if(c[i].p>=limit) continue;
		else{
			num=limit-c[i].p;
			while(num>0&&!heap.empty()) {
				//printf("i:%d top.val:%d top.index:%d\n",i,heap.top().val,heap.top().index);
				gold+=heap.top().val;ans[++ans[0]]=heap.top().index;
				heap.pop();
				num--;kill++;
			}
			limit=c[i].p;
		}
	}
	if(kill<=c[n].p) {puts("-1");return 0;}
	sort(ans+1,ans+ans[0]+1);
	printf("%d\n%d\n",gold,kill);
	for(int i=1;i<=ans[0];i++)
		printf("%d ",ans[i]+1);
	puts("");
	return 0;
}
