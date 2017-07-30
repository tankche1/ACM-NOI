/*
sgu 111
高精度开方
*/

# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int bit=10000000;
const int bit_num=7;

struct Big{
	LL a[150];
	int len;
	void init() {len=1;memset(a,0,sizeof(a));}
	void get(char *s){
		len=0;
		int n=strlen(s),tmp;
		for(int i=n-1;i>=0;i-=bit_num){
			tmp=0;
			for(int j=max(0,i-bit_num+1);j<=i;j++)
				tmp=tmp*10+s[j]-'0';
			a[len++]=tmp;
		}
	}
	
	void print(){
		printf("%lld",a[len-1]);
		for(int i=len-2;i>=0;i--)
			printf("%07lld",a[i]);puts("");
	}
};

Big C;
Big operator + (Big A, Big B){
	int n=max(A.len,B.len);
	C.init();
	for(int i=0;i<n;i++)
		C.a[i]=A.a[i]+B.a[i];
	for(int i=0;i<n;i++)
		if(C.a[i]>=bit) C.a[i]-=bit,C.a[i+1]++;
	C.len=n;
	if(C.a[C.len]) C.len++;
	return C;
}

Big operator / (Big A,int b){
	int n=A.len;LL tmp=0;
	for(int i=n-1;i>=0;i--){
		tmp=tmp*bit+A.a[i];
		C.a[i]=tmp/b;tmp=tmp-C.a[i]*b;
	}
	for(C.len=n;C.len>1&&C.a[C.len-1]==0;C.len--);
	return C;
}

Big operator * (Big A,Big B){
	C.init();
	for(int i=0;i<A.len;i++)
		for(int j=0;j<B.len;j++){
			C.a[i+j]+=A.a[i]*B.a[j];
		}
	for(int i=0;i<A.len+B.len-1;i++)
		C.a[i+1]+=C.a[i]/bit,C.a[i]%=bit;
	C.len=A.len+B.len-1;
	while(C.a[C.len]>0){
		C.a[C.len+1]+=C.a[C.len]/bit;C.a[C.len]%=bit;C.len++;
	}
	return C;
}

Big operator - (Big A,int b){
	C.init();
	C.len=A.len;for(int i=0;i<A.len;i++) C.a[i]=A.a[i];
	int t;
	C.a[0]-=b;
	for(int i=0;C.a[i]<0;i++){
		t=(-C.a[i]+bit-1)/bit;
		C.a[i]+=t*bit,C.a[i+1]-=t;
	}
	while(C.len>1&&C.a[C.len-1]==0) C.len--;
		return C;
}

bool operator <= (Big A,Big B){
	if(B.len>A.len) return true;
	if(A.len>B.len) return false;
	for(int i=A.len-1;i>=0;i--){
		if(A.a[i]>B.a[i]) return false;
		else if(A.a[i]<B.a[i]) return true;
	}
	return true;
}

Big L,R,M,num,T,one;
char s[2010];

int main(){
	L.init();
	scanf("%s",s);
	num.get(s);//R.print();
	L.a[0]=1;R=num;one.init();one.a[0]=1;
	while(L<=R){
		//printf("L:");L.print();printf("R:");R.print();
		M=L+R;//printf("M:");M.print();
		M=M/2;//printf("M:");M.print();
		T=M*M;//printf("T:");T.print();//printf("TR:");R.print();
		if(T<=num) L=M+one;//printf("small L:");L.print();M.print();}
		else //printf("RR:"),R.print(),
			R=M-1;//,printf("big R:"),R.print(),M.print();
			//int  aa;scanf("%d",&aa);
	}
	L=L-1;
	L.print();
	return 0;
}
