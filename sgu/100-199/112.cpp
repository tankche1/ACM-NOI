# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int Bit=10000;
const int maxlen=4000;
struct Bin{
	int s[maxlen],len;
	Bin(){memset(s,0,sizeof(s));len=1;}
};

Bin operator * (Bin A,Bin B){
	Bin C;
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

Bin operator - (Bin A,Bin B){
	Bin C=A;
	for(int i=0;i<B.len;i++)
		C.s[i]-=B.s[i];
	for(int i=0;i<C.len;i++)
		if(C.s[i]<0) C.s[i]+=Bit,C.s[i+1]--;
	while(C.len>1&&C.s[C.len-1]==0) C.len--;
	return C;
}

Bin fast_pow(Bin A,int b){
	Bin m=A;
	Bin ans;ans.s[0]=1;
	while(b>0){
		if(b&1) ans=ans*m;
		m=m*m;
		b>>=1;
	}
	return ans;
}

bool operator < (Bin A,Bin B){
	if(A.len!=B.len) return A.len<B.len;
	for(int i=A.len-1;i>=0;i--)
		if(A.s[i]==B.s[i]) continue;
			else return A.s[i]<B.s[i];
	return false;
}

int a,b;
int main(){
	scanf("%d%d",&a,&b);
	Bin A,B;A.s[0]=a;B.s[0]=b;
	Bin C=fast_pow(A,b),D=fast_pow(B,a);
	bool fu=C<D?1:0;
	Bin ans=fu?D-C:C-D;
	if(fu) printf("-");
	printf("%d",ans.s[ans.len-1]);
	for(int i=ans.len-2;i>=0;i--)
		printf("%04d",ans.s[i]);puts("");
	//printf("%04d\n",1);
	return 0;
}
