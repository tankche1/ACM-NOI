#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
const int maxt=10000010;
const int maxn=510;
const int maxb=30;
int n,Q;
int A[maxn][maxn],num[maxn*maxn],cnt=0;
int bcnt,len;
int start[maxb],end[maxb];

struct Node{
	int size;
	Node *ch[2];
	Node() {}
	void maintain() {size=ch[0]->size+ch[1]->size;}
};
Node seq[maxt];int seq_cnt=0;
Node *null;
Node *root[maxn][maxn],*block[maxb][maxn];
Node *q[maxb*3][2];

Node *New(){
	Node *o=&seq[seq_cnt++];o->ch[0]=o->ch[1]=null;o->size=0;return o;
}

void Add(Node* &x,Node* &y,int L,int R,int val){
	x->size=y->size+1;
	//printf("L:%d R:%d size:%d\n",L,R,x->size);
	if(L==R) return;
	int M=(L+R)>>1;
	if(val<=M)
		x->ch[1]=y->ch[1],x->ch[0]=New(),Add(x->ch[0],y->ch[0],L,M,val);
	else x->ch[0]=y->ch[0],x->ch[1]=New(),Add(x->ch[1],y->ch[1],M+1,R,val);
}

int main(){
	//freopen("input.txt","r",stdin);
	int x1,y1,x2,y2,k;
	null=new Node();null->size=0;null->ch[0]=null->ch[1]=null;
	scanf("%d%d",&n,&Q);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&A[i][j]),num[++cnt]=A[i][j];
	sort(num+1,num+cnt+1);cnt=unique(num+1,num+cnt+1)-num-1;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) A[i][j]=lower_bound(num+1,num+cnt+1,A[i][j])-num;
	Node *last;
	for(int i=0;i<n;i++){
		last=null;
		for(int j=0;j<n;j++){root[i][j]=New();//printf("i:%d j:%d\n",i,j);
			Add(root[i][j],last,1,cnt,A[i][j]);
			last=root[i][j];
		}
	}
	len=sqrt(n);bcnt=(n-1)/len+1;
	for(int i=0;i+1<bcnt;i++) start[i]=i*len,end[i]=(i+1)*len-1;
	start[bcnt-1]=(bcnt-1)*len;end[bcnt-1]=n-1;
	for(int i=0;i<bcnt;i++){
		for(int j=0;j<n;j++){
			Node *o;
			last=j==0?null:block[i][j-1];
			for(int k=start[i];k<=end[i];k++){
				o=New();Add(o,last,1,cnt,A[k][j]);last=o;
			}
			block[i][j]=o;
		}
	}
	
	for(int tt=1;tt<=Q;tt++){
		int q_cnt=0;
		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&k);x1--;y1--;x2--;y2--;
		int pos1=x1/len,pos2=x2/len;
		if(pos1==pos2){
			for(int i=x1;i<=x2;i++)
				q[q_cnt][0]=root[i][y2],q[q_cnt++][1]=y1==0?null:root[i][y1-1];
		}
		else{
			for(int i=x1;i<=end[pos1];i++)
				q[q_cnt][0]=root[i][y2],q[q_cnt++][1]=y1==0?null:root[i][y1-1];
			for(int i=pos1+1;i<pos2;i++)
				q[q_cnt][0]=block[i][y2],q[q_cnt++][1]=y1==0?null:block[i][y1-1];
			for(int i=start[pos2];i<=x2;i++)
				q[q_cnt][0]=root[i][y2],q[q_cnt++][1]=y1==0?null:root[i][y1-1];
		}
		
		int L=1,R=cnt;
		while(L<R){
			int M=(L+R)>>1;
			int tot=0;
		//	printf("L:%d R:%d q[0]->size:%d\n",L,R,q[0][0]->size);
			for(int i=0;i<q_cnt;i++)
				tot+=q[i][0]->ch[0]->size-q[i][1]->ch[0]->size;
			if(k<=tot) {R=M;for(int i=0;i<q_cnt;i++) q[i][0]=q[i][0]->ch[0],q[i][1]=q[i][1]->ch[0];}
			else {k-=tot,L=M+1;for(int i=0;i<q_cnt;i++) q[i][0]=q[i][0]->ch[1],q[i][1]=q[i][1]->ch[1];}
		}
		printf("%d\n",num[R]);
	}
	return 0;
}
