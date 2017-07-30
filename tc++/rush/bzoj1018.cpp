/*
维护只经过这个区间的点 4个顶点之间的连通性
更新一下 注意绕一大圈的情况
吐槽下网上的解释真的很烂 第一句话都没人讲清 一点点看代码得出来的。。
*/
# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
bool g[maxn][3];

struct IntervalTree{
	bool A[maxn<<1][6];
	bool res[6];
	int last;
	
	void build(int o,int L,int R){
		memset(A[o],0,sizeof(A[o]));
		if(L==R){
			A[o][0]=A[o][1]=1;
			return;
		}
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
	}
	
	void update(bool *A,bool *L,bool *R,int x){
		A[0]=(g[x][0]&&L[0]&&R[0])||(g[x][1]&&L[4]&&R[5]);A[1]=(g[x][1]&&L[1]&&R[1])||(g[x][0]&&L[5]&&R[4]);
		A[2]=L[2]||(g[x][0]&&L[0]&&R[2]&&g[x][1]&&L[1]);A[3]=R[3]||(R[0]&&g[x][0]&&g[x][1]&&R[1]&&L[3]);
		A[4]=(g[x][0]&&L[0]&&R[4])||(g[x][1]&&L[4]&&R[1]);A[5]=(g[x][0]&&L[5]&&R[0])||(g[x][1]&&L[1]&&R[5]);
	}
	
	void change(int o,int L,int R,int qL,int qR){
		//printf("o:%d L:%d R:%d\n",o,L,R);
		if(L==R){
			A[o][2]=A[o][3]=A[o][4]=A[o][5]=g[qL][2];
			return;
		}
		int M=(L+R)>>1;
		if(qR<=M) change(o<<1,L,M,qL,qR);
			else if(qL>M) change(o<<1|1,M+1,R,qL,qR);
		update(A[o],A[o<<1],A[o<<1|1],M);
	}
	
	void Ask(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R){
			if(!last) {memcpy(res,A[o],sizeof(A[o]));last=R;return;}
			bool P[6];
			memcpy(P,res,sizeof(res));
			update(res,P,A[o],last);
			last=R;
			return;
		}
		int M=(L+R)>>1;
		if(qL<=M) Ask(o<<1,L,M,qL,qR);
		if(qR>M) Ask(o<<1|1,M+1,R,qL,qR);
	}
	
	void print(int o,int L,int R){
		printf("o:%d L:%d R:%d\n",o,L,R);
		for(int i=0;i<6;i++) printf("A[%d]:%d ",i,A[o][i]);printf("\n");
		if(L==R) return;
		int M=(L+R)>>1;
		print(o<<1,L,M);
		print(o<<1|1,M+1,R);
	}
};
IntervalTree tree;

int n;
char op[10];
int x1,y1,x2,y2;
int main(){
	scanf("%d",&n);
	tree.build(1,1,n);
	while(1){
		scanf("%s",op);
		if(op[0]=='E') break;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);x1--;x2--;
		if(y2<y1) swap(x1,x2),swap(y1,y2);
		if(op[0]=='A'){
			tree.last=0;tree.Ask(1,1,n,y1,y2);
			int t=(y1==y2)?2:(x1==x2)?x1:(x1>x2)?5:4;
			bool ok=tree.res[t];
			if(!ok){
				bool A[6],B[6],C[6];
				memcpy(B,tree.res,sizeof(tree.res));
				tree.last=0;tree.Ask(1,1,n,1,y1);
				memcpy(A,tree.res,sizeof(tree.res));
				tree.last=0;tree.Ask(1,1,n,y2,n);
				memcpy(C,tree.res,sizeof(tree.res));
				ok=(A[3]&&C[2]&&(B[x1^1]))||(A[3]&&B[t==0?5:t==4?1:t==1?4:0])||(C[2]&&B[t==0?4:t==1?5:t==4?0:1]);
			}
			printf("%c\n",ok?'Y':'N');
		}
		else{
			g[y1][x1==x2?x1:2]=op[0]=='O';
			tree.change(1,1,n,y1,y2);
		}
		//tree.print(1,1,n);
	}
	return 0;
}
