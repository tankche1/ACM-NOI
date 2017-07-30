#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=50010;
const int maxm=maxn<<2;
typedef pair<int,int> pi;
int n,m;
int A[maxn],next[maxn],num[maxn],cnum=0;
int col[maxn];
struct Duty{
	int l,r,bh;
	Duty() {}
	Duty(int l,int r,int bh):l(l),r(r),bh(bh) {}
};
Duty duty[maxm];

bool cmp(Duty A,Duty B) {return A.l<B.l;}

inline int lowbit(int x) {return x&(-x);}
int ans[maxm];

struct FenwickTree{
	int n;
	int C[maxn];
	void init(int nn) {n=nn;memset(C,0,sizeof(C));}
	
	void Add(int x,int val){
		//printf("x:%d val:%d\n",x,val);
		while(x<=n){
			C[x]+=val;x+=lowbit(x);
		}
	}
	
	int Sum(int x){
		int res=0;
		while(x>0)
			res+=C[x],x-=lowbit(x);
		return res;
	}
};
FenwickTree fwt;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]),num[cnum++]=A[i];
	sort(num,num+cnum);cnum=unique(num,num+cnum)-num;
	for(int i=1;i<=n;i++) A[i]=lower_bound(num,num+cnum,A[i])-num,col[i]=n+1;
	col[0]=n+1;
	
	for(int i=n;i>=1;i--){
		next[i]=col[A[i]];col[A[i]]=i;//printf("next[%d]:%d\n",i,next[i]);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&duty[i].l,&duty[i].r),duty[i].bh=i;
	sort(duty+1,duty+m+1,cmp);
	int last=1;
	memset(col,0,sizeof(col));
	fwt.init(n);
	for(int i=1;i<=n;i++)
		if(!col[A[i]]) fwt.Add(i,1),col[A[i]]=1;
	for(int i=1;i<=m;i++){
		for(int j=last;j<duty[i].l;j++) {fwt.Add(j,-1);if(next[j]!=n+1) fwt.Add(next[j],1);}
		ans[duty[i].bh]=fwt.Sum(duty[i].r);
		last=duty[i].l;
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
