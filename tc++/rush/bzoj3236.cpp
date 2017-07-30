#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=1000010;
int n,m;
int num[maxn],stack[maxn],top;

void clear(){
	memset(num,0,sizeof(num));
}

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
	int C[maxn],n;
	void init(int nn){
		n=nn;memset(C,0,sizeof(C));
	}
	
	void add(int x,int val){
		while(x<=n) C[x]+=val,x+=lowbit(x);
	}
	
	int sum(int x){
		int res=0;
		while(x) res+=C[x],x-=lowbit(x);
		return res;
	}
};
FenwickTree fwt,fwt2;

struct Duty{
	int w,l,r,a,b,bh;
	Duty() {}
	bool operator < (const Duty &rhs)const{
		if(w==rhs.w) return r<rhs.r;
		return w<rhs.w;
	}
};
Duty duty[maxm];
int A[maxn];
int ans1[maxm],ans2[maxm];

int main(){
	scanf("%d%d",&n,&m);
	int len=(int)sqrt(n);
	//int bnum=(n-1)/len+1;
	for(int i=0;i<n;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<=m;i++){
		duty[i].bh=i;
		scanf("%d%d%d%d",&duty[i].l,&duty[i].r,&duty[i].a,&duty[i].b);duty[i].l--;duty[i].r--;
		duty[i].w=duty[i].l/len;
	}
	sort(duty+1,duty+m+1);
	for(int i=1;i<=m;i++){
	//int ask1=0,ask2=0;
		fwt.init(n);fwt2.init(n);clear();
		for(int j=duty[i].l;j<=duty[i].r;j++){
			fwt.add(A[j],1);if(num[A[j]]==0) fwt2.add(A[j],1);num[A[j]]++;
		}
		ans1[duty[i].bh]=fwt.sum(duty[i].b)-fwt.sum(duty[i].a-1);ans2[duty[i].bh]=fwt2.sum(duty[i].b)-fwt2.sum(duty[i].a-1);
		for(;duty[i+1].w==duty[i].w;i++){
			for(int j=duty[i].r+1;j<=duty[i+1].r;j++){
				fwt.add(A[j],1);
				if(num[A[j]]==0) fwt2.add(A[j],1);
				num[A[j]]++;
			}
			if(duty[i+1].l<=duty[i].l){
				for(int j=duty[i+1].l;j<duty[i].l;j++){
						fwt.add(A[j],1);
						if(num[A[j]]==0) fwt2.add(A[j],1);
						num[A[j]]++;
				}
			}
			else{
				for(int j=duty[i].l;j<duty[i+1].l;j++){
					fwt.add(A[j],-1);
					num[A[j]]--;
					if(num[A[j]]==0) fwt2.add(A[j],-1);
				}
			}
			ans1[duty[i+1].bh]=fwt.sum(duty[i+1].b)-fwt.sum(duty[i+1].a-1);
			ans2[duty[i+1].bh]=fwt2.sum(duty[i+1].b)-fwt2.sum(duty[i+1].a-1);
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d %d\n",ans1[i],ans2[i]);
	return 0;
}
