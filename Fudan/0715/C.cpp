# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int n;
char s[1000100];

const int Bit=100000000;
const int maxlen=720;
struct Bin{
	LL s[maxlen];int len;
	Bin(){memset(s,0,sizeof(s));len=1;}
	
	
	
	/*void operator *=(Bin B){
		C.len=1;memset(C.s,0,sizeof(C.s));
		for(int i=0;i<len;i++)
			for(int j=0;j<B.len;j++)
				C.s[i+j]+=s[i]*B.s[j];
		C.len=len+B.len-1;
		for(int i=0;i<C.len;i++){
			C.s[i+1]+=C.s[i]/Bit;
			C.s[i]%=Bit;
		}
		while(C.s[C.len]>0){
			C.s[C.len+1]+=C.s[C.len]/Bit;
			C.s[C.len]%=Bit;
			C.len++;
		}
		len=C.len;for(int i=0;i<=4000;i++) s[i]=C.s[i];
	}*/
	
	void print(){
		printf("%I64d",s[len-1]);
		for(int i=len-2;i>=0;i--){
			//if(s[i]<100000000) printf("0");
			if(s[i]<10000000) printf("0");
			if(s[i]<1000000) printf("0");
			if(s[i]<100000) printf("0");
			if(s[i]<10000) printf("0");
			if(s[i]<1000) printf("0");
			if(s[i]<100) printf("0");
			if(s[i]<10) printf("0");
			printf("%I64d",s[i]);
		}puts("");
	}
};
Bin C;

Bin operator +(Bin A,Bin B){
		C.len=1;memset(C.s,0,sizeof(C.s));
		int m=max(A.len,B.len);
		for(int i=0;i<m;i++)
			C.s[i]=A.s[i]+B.s[i];
		for(int i=0;i<m;i++){
			while(C.s[i]>=Bit) C.s[i+1]++,C.s[i]-=Bit;
		}
		while(C.s[m]>0) {while(C.s[m]>=Bit) C.s[m+1]++,C.s[m]-=Bit;m++;}
	C.len=m;
	return C;
}
	
Bin operator * (Bin A,Bin B){
	C.len=1;memset(C.s,0,sizeof(C.s));
	for(int i=0;i<A.len;i++)
		for(int j=0;j<B.len;j++)
			C.s[i+j]+=A.s[i]*B.s[j];
	C.len=A.len+B.len-1;
	for(int i=0;i<C.len;i++){
		C.s[i+1]+=C.s[i]/Bit;
		C.s[i]%=Bit;
	}
	while(C.s[C.len]>0){
		C.s[C.len+1]+=C.s[C.len]/Bit;
		C.s[C.len]%=Bit;
		C.len++;
	}
	return C;
}

Bin a[13];
int main(){
	//freopen("in.txt","r",stdin);
	int n,pos;
	for(int i=1;i<=10;i++) a[i].s[0]=1;
		while(scanf("%s",s)!=EOF){
			n=strlen(s);
			for(int i=0;i<n;i++) if(s[i]=='=') {pos=i;break;}
			if(s[pos-1]=='+'){
				a[s[pos-2]-'A'+1]=a[s[pos-2]-'A'+1]+a[s[pos+1]-'A'+1];
			}
			else if(s[pos-1]=='*'){
				a[s[pos-2]-'A'+1]=a[s[pos-2]-'A'+1]*a[s[pos+1]-'A'+1];
			}
			else a[s[pos-1]-'A'+1]=a[s[pos+1]-'A'+1];
		}
		for(int i=1;i<=10;i++) a[i].print();
	return 0;
}
