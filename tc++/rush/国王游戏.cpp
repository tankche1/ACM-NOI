# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxl=4*1000/4+20;
typedef long long LL;
struct Bin{
	LL A[maxl];
	int len;
	Bin() {memset(A,0,sizeof(A));len=1;}
	
	void init(Bin &C){
		len=C.len;
		for(int i=0;i<len;i++) A[i]=C.A[i];
	}
	
	void operator *=(LL &B){
		/*	for(int ii=len-1;ii>=0;ii--)
		printf("%lld",A[ii]);
	puts("");
			printf("B:%lld\n",B);*/
		Bin C;
		for(int i=0;i<len;i++)
				C.A[i]=A[i]*B;
		C.len=len;
		for(int i=0;i<C.len;i++)
			C.A[i+1]+=C.A[i]/10000,C.A[i]%=10000;
		while(C.A[C.len]>0){
			C.A[C.len+1]+=C.A[C.len]/10000;C.A[C.len]%=10000;
			C.len++;
		}
		init(C);
	/*	for(int ii=len-1;ii>=0;ii--)
		printf("%lld",A[ii]);
	puts("");
		int fuck;scanf("%d",&fuck);*/
	}
	
	void operator /=(LL B){
		Bin C;
		/*	for(int ii=len-1;ii>=0;ii--)
		printf("%lld",A[ii]);
	puts("");
			printf("B:%lld\n",B);*/
		LL last=0;
		for(int i=len-1;i>=0;i--){
			C.A[i]=(A[i]+last)/B;
			last=(A[i]+last-C.A[i]*B)*10000;
		}
		C.len=len;
		while(C.len>1&&C.A[C.len-1]==0)
			C.len--;
		init(C);
		/*for(int ii=len-1;ii>=0;ii--)
		printf("%lld",A[ii]);
	puts("");*/
	}
	
};
Bin A,B;

bool operator < (const Bin &A,const Bin &B){
	if(A.len<B.len) return true;
	else if(A.len>B.len) return false;
	for(int i=A.len-1;i>=0;i--){
		if(A.A[i]<B.A[i]) return true;
			else if(A.A[i]>B.A[i]) return false;
	}
	return false;
}

int n,a,b;

struct Monkey{
	LL a,b;
	bool operator < (Monkey rhs)const{
		return (a*b)<(rhs.a*rhs.b);
	}
};
Monkey monkey[1010];

int main(){
	Bin now;
	Bin ans;
	bool first=true;
	scanf("%d",&n);
	scanf("%d%d",&a,&b);
	now.A[0]=a;
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&monkey[i].a,&monkey[i].b);
	sort(monkey+1,monkey+n+1);
	for(int i=1;i<=n;i++){
	/*for(int ii=now.len-1;ii>=0;ii--)
		printf("%lld",now.A[ii]);
	puts("");*/
		Bin x=now;
		x/=monkey[i].b;
		if(first||ans<x){
			ans=x;first=false;
		}
		now*=monkey[i].a;
		//printf("monkey:%lld\n",monkey[i].a);
	}

	printf("%lld",ans.A[ans.len-1]);
	for(int i=ans.len-2;i>=0;i--){
		if(ans.A[i]<1000) printf("0");
		if(ans.A[i]<100) printf("0");
		if(ans.A[i]<10) printf("0");
		printf("%lld",ans.A[i]);
	}
	puts("");
}
