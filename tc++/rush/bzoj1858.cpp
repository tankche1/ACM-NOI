# include<stdio.h>
# include<string.h>
# include<algorithm>
# define root 1,1,n
# define lson t<<1,l,(l+r)>>1
# define rson t<<1|1,l,((l+r)>>1)+1
# define Tree int t,int l,int r
using namespace std;
const int maxn=100010;
int n,m;
int A[maxn];
struct Info{
	int lmax,rmax,size,sum,mmax;
	void set(int val){lmax=rmax=sum=mmax=val?val*size:0;}
};
struct Node{
	Info I[2];
	void set(int val){for(int i=0;i<2;i++) I[i].set(val);}
};
Node T[maxn<<2];

Node operator + (const Node A,const Node B){
	
}

void build(Tree){
	if(l==r) T[t].set(A[l]);
	build(lson);build(rson);
	T[t]=T[t<<1]+T[t<<1|1];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	build(root);
	return 0;
}
