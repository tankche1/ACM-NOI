#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=10010;
const int maxnode=2000010;
const int mod=1000000009;
typedef long long LL;
LL pre[maxnode],next[maxnode],L[maxnode],down[maxnode];
LL ans=0;
LL R,C,n,a[maxnode];
inline LL pos(LL x,LL y){return (x-1)*(C+2)+y;}
inline LL lowbit(LL x) {return (x&(-x));}


//fwt1[i] 有几个L[x]=i的top和 fwt2[i] L[x]=i的和*top  fwt3[i] L[x]=i 的(i-1)*i/2*top
struct FenwickTree{
	LL A[maxn];
	void init() {memset(A,0,sizeof(A));}
	void add(LL pos,LL val){
		if(pos<=0) return;
		for(;pos<=C;pos+=lowbit(pos))
			A[pos]+=val;
	}
	
	LL sum(LL pos){
		LL ans=0;
		for(;pos>0;pos-=lowbit(pos))
			ans+=A[pos];
		return ans;
	}
};
FenwickTree fwt1,fwt2,fwt3;

void prepare(){
	for(LL i=1;i<=R;i++){
		pre[pos(i,0)]=0;
		for(LL j=1;j<=C;j++){
			if(a[pos(i,j)]==0) pre[pos(i,j)]=j;
				else pre[pos(i,j)]=pre[pos(i,j-1)];
		}
		next[pos(i,C+1)]=C+1;
	for(LL j=C;j>=1;j--)
		next[pos(i,j)]=a[pos(i,j)]==0?j:next[pos(i,j+1)],L[pos(i,j)]=min(next[pos(i,j)]-j-1,j-pre[pos(i,j)]-1);
	}
	for(LL j=1;j<=C;j++){
		down[pos(R+1,j)]=0;
		for(LL i=R;i>=1;i--)
			if(a[pos(i,j)]==0) down[pos(i,j)]=0;
				else down[pos(i,j)]=down[pos(i+1,j)]+1;
	}
}

void init(){
	fwt1.init();fwt2.init();fwt3.init();
}

void cal(LL col){
	init();
	LL top=-1;
	for(LL row=1;row<=R;row++){
		if(row>3&&top<=row-3&&top!=-1){
			fwt1.add(L[pos(row-2,col)],(row-2-top));fwt2.add(L[pos(row-2,col)],L[pos(row-2,col)]*(row-2-top));fwt3.add(L[pos(row-2,col)],((L[pos(row-2,col)]+1)*L[pos(row-2,col)]/2)*(row-2-top));
			//if(row==4&&col==5) printf("%lld %lld\n",L[pos(row-2,col)],(row-2-top));
		}
		if(a[pos(row,col)]==0) {top=-1,init();}
		else if(top==-1) top=row;
		if(L[pos(row,col)]<=1) continue;
		LL num=fwt1.sum(C)-fwt1.sum(L[pos(row,col)]-1);
		//printf("num:%lld L:%lld\n",num,L[pos(row,col)]);
		LL tot=0;
		tot+=fwt2.sum(L[pos(row,col)]-1)*L[pos(row,col)];
		tot-=fwt3.sum(L[pos(row,col)]-1);
		tot+=num*(L[pos(row,col)]*(L[pos(row,col)]-1)-(L[pos(row,col)])*(L[pos(row,col)]-1)/2);
		tot*=down[pos(row+1,col)];
		ans+=tot;ans%=mod;
		//ans+=(fwt2.sum(L[pos(row,col)]-1)*L[pos(row,col)]-fwt3.sum(L[pos(row,col)]-1)+num*((L[pos(row,col)])*(L[pos(row,col)]-1)-((L[pos(row,col)]-2)*(L[pos(row,col)]-1))/2))*down[pos(row,col)];
		//printf("row:%lld col:%lld tot: %lld down:%lld\n",row,col,tot,down[pos(row+1,col)]);
	}
}

int main(){
	LL x,y;
	scanf("%lld%lld",&R,&C);
	for(LL i=1;i<=R;i++) for(LL j=1;j<=C;j++) a[pos(i,j)]=1;
	scanf("%lld",&n);
	for(LL i=1;i<=n;i++)
		scanf("%lld%lld",&x,&y),a[pos(x,y)]=0;
	prepare();
	for(LL i=1;i<=C;i++)
		cal(i);
	printf("%lld\n",ans);
	return 0;
}
