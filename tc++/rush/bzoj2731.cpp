#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=10010;
const int maxl=1000010;
const int INF=~0U>>1;
int sum[maxl<<1];

int n;
struct Node{
	Node *pre,*next;
	int bh;
	Node(){}
};
Node *head;
Node *null;
Node seq[maxn];int seq_cnt=0;
Node *New(){Node *o=&seq[seq_cnt++];return o;}

struct Triangle{
	int x,y,d,l,r;
	Triangle() {}
	bool operator > (const Triangle &B)const{
		return l<=B.l&&r>=B.r;
	}
};
Triangle tri[maxn];
int low,high;

bool cmp(Triangle A,Triangle B){
	return A.y<B.y;
}

void Delete(Node* x){
	if(head==x) {head=x->next;head->pre=null;return;}
	if(x->next!=null)
	x->next->pre=x->pre;
	if(x->pre!=null)
	x->pre->next=x->next;
}

void Insert(int bh){
	if(head==null) {head=New();head->pre=head->next=null;head->bh=bh;return;}
	Node *o=New();
	o->next=head;o->pre=null;o->bh=bh;head->pre=o;head=o;
}

void solve(){
	memset(sum,0,sizeof(sum));
	int len=0;
	double ans=0;
	int pos=0;
	for(int y=low;y<=high;y++){
		int lastlen=len;
		for(Node *e=head;e!=null;e=e->next){
			tri[e->bh].r--;sum[tri[e->bh].r]--;
			if(sum[tri[e->bh].r]==0) len--;
			if(tri[e->bh].r==tri[e->bh].l) {Delete(e);}
		}
		
		ans+=(len+lastlen)/2.0;
		while(pos<n&&tri[pos].y==y){
			bool ok=true;
			for(Node *e=head;e!=null;e=e->next){
				if(tri[e->bh]>tri[pos]){
					ok=false;break;
				}
				if(tri[pos]>tri[e->bh]){
					for(int j=tri[e->bh].l;j<tri[e->bh].r;j++){
						sum[j]--;if(sum[j]==0) len--;
					}
					Delete(e);
				}
			}
			if(ok&&tri[pos].d!=0){
				Insert(pos);
				for(int j=tri[pos].l;j<tri[pos].r;j++){
					sum[j]++;if(sum[j]==1) len++;
				}
			}
			pos++;
		}
	}
	printf("%.1lf\n",ans);
}

int main(){
	null=new Node();null->pre=null->next=null;
	head=null;
	scanf("%d",&n);
	low=INF;high=-INF;
	for(int i=0;i<n;i++){
		scanf("%d%d%d",&tri[i].x,&tri[i].y,&tri[i].d);
		tri[i].l=tri[i].x,tri[i].r=tri[i].l+tri[i].d;
		high=max(tri[i].y+tri[i].d,high),low=min(low,tri[i].y);
	}
	sort(tri,tri+n,cmp);
	solve();
	return 0;
}
/*
3
1 1 4
2 0 2
3 2 2
*/
