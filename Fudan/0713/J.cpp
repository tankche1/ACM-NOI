# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;

struct Heap{
	int t,index;
	Heap() {}
	Heap(int t,int index):t(t),index(index) {}
	bool operator < (const Heap &rhs)const{
		return t>rhs.t;
	}
};
priority_queue<Heap>heap;

int n,t[3];
int main(){
	scanf("%d%d%d",&n,&t[1],&t[2]);
	int now=0,nowt=0,id;
	heap.push(Heap(t[1],1));heap.push(Heap(t[2],2));
	while(!heap.empty()){
		nowt=heap.top().t;id=heap.top().index;
		heap.pop();
		if(nowt==heap.top().t){//同时
			now+=2;heap.pop();
			if(now<n){
				for(id=1;id<=2;id++)
					heap.push(Heap(nowt+t[id],id));
			}
			else{
				break;
			}
			continue;
		}
		//不同时
		now++;
		if(now<n) heap.push(Heap(nowt+t[id],id));
		else {now++;nowt=heap.top().t;break;}
	}
	printf("%d %d\n",now,nowt);
	return 0;
}
