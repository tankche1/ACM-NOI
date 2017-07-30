# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=150010;
struct square{
	int T1,T2;
	bool operator< (const square &rhs)const{
		return T2<rhs.T2;
	}
};
square a[maxn];
struct HeapNode{
	int Time;
	bool operator<(const HeapNode& rhs)const{
		return Time<rhs.Time;
	}
};
priority_queue<HeapNode> q;
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].T1,&a[i].T2);
	sort(a+1,a+n+1);
	int Time=0,ans=0;
	HeapNode h;
	for(int i=1;i<=n;i++){
		if(Time+a[i].T1<=a[i].T2){
			ans++;
			Time+=a[i].T1;
			h.Time=a[i].T1;
			q.push(h);
		}else{
			if(a[i].T1<q.top().Time){
				Time+=a[i].T1-q.top().Time;
				q.pop();
				h.Time=a[i].T1;
				q.push(h);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
