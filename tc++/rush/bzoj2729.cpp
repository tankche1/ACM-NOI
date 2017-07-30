#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=2010;
const int Bit=1e+6;

struct Bign{
	int A[maxn<<2],len;
	
	Bign(){len=1;memset(A,0,sizeof(A));}
	void operator *= (int x){
		for(int i=0;i<len;i++)
			A[i]*=x;
		for(int i=0;i<len;i++)
			A[i+1]+=A[i]/Bit,A[i]%=Bit;
		while(A[len]>0){
			A[len+1]+=A[len]/Bit;
			A[len]%=Bit;
			len++;
		}
	}
	
	void operator -= (Bign &B){
		for(int i=0;i<B.len;i++)
			A[i]-=B.A[i];
		for(int i=0;i<B.len||A[i]<0;i++){
			if(A[i]<0) A[i]+=Bit,A[i+1]--;
		}
		while(len>0&&A[len-1]==0) len--;
	}
};
Bign A,B;
int n,m;

int main(){
	scanf("%d%d",&n,&m);
	A.A[0]=1;
	for(int x=n+3;x>=n+3-m+1;x--)
		A*=x;
	for(int x=1;x<=n+2;x++)
		A*=x;
	B.A[0]=2;
	for(int x=1;x<=n+1;x++)
		B*=x;
	for(int x=n+2;x>=n+2-m+1;x--)
		B*=x;
	A-=B;
	printf("%d",A.A[A.len-1]);
	for(int i=A.len-2;i>=0;i--)
		printf("%06d",A.A[i]);puts("");
	return 0;
}
