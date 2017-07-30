# include<stdio.h>
# include<algorithm>
using namespace std;
typedef int LL;
LL n;
void cut0(LL &A){
	while(A%10==0) A/=10;
}

int Bit(LL A){
	int t=0;
	while(A>0) A/=10,t++;
	return t;
}

int main()
{
	int Tcase;
	double Min,Max;
	LL L,R;
	bool ok;
	scanf("%d",&Tcase);
	while(Tcase--){
		ok=false;
		scanf("%d",&n);
		cut0(n);
		Min=(double)n*(double)0.95,Max=(double)n*(double)1.05;
		L=(LL)Min;R=(LL)Max;
		if(n%20) L++;
		cut0(L);cut0(R);
		if(Bit(L)<Bit(n)) ok=1;
		else if(Bit(R)<Bit(n)) ok=1;
		else if(R-R%10>n) ok=1;
		else if(L+10-L%10<n) ok=1;
		else if(n%10!=5&&n-n%10+5>=L&&n-n%10+5<=R) ok=1;
		if(ok) puts("absurd");
		else puts("not absurd");
	}
	return 0;
}
