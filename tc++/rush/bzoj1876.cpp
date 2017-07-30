# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const LL bit=100000000;
const int maxl=1400;
char s[11000];
struct Bign{
	LL A[maxl];
	int len;
	Bign() {len=1;memset(A,0,sizeof(A));}
	void input(){
		scanf("%s",s);
		int n=strlen(s);LL power=1;
		for(int i=n-1;i>=0;i--){
			A[len-1]+=(s[i]-'0')*power;
			power*=10;
			if(power==bit) power=1,len++;
		}
		if(power==1) len--;
		//	for(int i=0;i<len;i++) printf("%d",A[i]);puts("");
	}
	
	void divide(){
		LL last=0;
		for(int i=len-1;i>=0;i--){
			A[i]+=last;if(A[i]&1) last=bit;else last=0;
			A[i]>>=1;
		}
		while(len>1&&A[len-1]==0) len--;
	}
	
	void operator *=(const LL val){
		for(int i=0;i<len;i++)
			A[i]*=val;
		for(int i=0;i<len-1;i++){
			A[i+1]+=A[i]/bit;A[i]%=bit;
		}
		while(A[len-1]>=bit){
			A[len]+=A[len-1]/bit;A[len-1]%=bit;len++;
		}
	}
	
	void operator -=(const Bign &rhs){
		for(int i=0;i<len;i++){
			A[i]-=rhs.A[i];if(A[i]<0) A[i]+=bit,A[i+1]--;
		}
		while(len>1&&A[len-1]==0) len--;
	}
	
	bool operator < (const Bign &rhs)const{
		if(rhs.len!=len) return len<rhs.len;
		for(int i=len-1;i>=0;i--)
			if(A[i]!=rhs.A[i])
				return A[i]<rhs.A[i];
			return false;
	}
	
	bool isZero(){
		return len==1&&A[0]==0;
	}
	
};
Bign C[2];
bool first=true;

/*void print(LL x){
	int num=0;LL xx=x;
	while(x) x/=10,num++;
		if(!first)
	for(int i=1;i<9-num;i++) printf("0");
		printf("%lld",xx);first=false;
}*/

int main(){
	C[0].input();C[1].input();
	int a=0,b=1,c=0;
	while(1){
		if(C[b]<C[a]) swap(a,b);
		if(C[a].isZero()){
			while(c>=16) C[b]*=1<<16,c-=16;
			while(c>0) C[b]*=2,c--;
			break;
		}
		if(C[a].A[0]%2==0&&C[b].A[0]%2==0){
			c++;
			C[a].divide();C[b].divide();
		}
		else if(C[a].A[0]%2==0||C[b].A[0]%2==0){
			int d=C[a].A[0]%2==0?a:b;
			C[d].divide();
		}
		else{
			C[b]-=C[a];
		}
	}
	printf("%I64d",C[b].A[C[b].len-1]);
	for(int i=C[b].len-2;i>=0;i--)
		printf("%08I64d",C[b].A[i]);
	return 0;
}
/*
50688939130
11040050942514
*/
