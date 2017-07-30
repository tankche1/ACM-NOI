# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxL=1005;
const int maxn=105;
const int bit=10000;
struct Bign{
	int len;
	int A[maxL];
	Bign() {len=1;memset(A,0,sizeof(A));}
	void operator +=(const int val){
		A[0]=A[0]+val;
		int i=0;
		while(A[i]>=bit){
			A[i+1]+=A[i]/bit;A[i]%=bit;
		}
		if(i+1>len) len=i+1;
	}
	
	void operator -=(const Bign rhs){
		for(int i=0;i<rhs.len;i++)
			A[i]-=rhs.A[i];int i;
		for(i=0;i<rhs.len;i++){
			if(A[i]<0) A[i]+=bit,A[i+1]--;
		}
		while(A[i]<0)
			A[i]+=bit,A[++i]--;
		while(len>1&&A[len-1]<0) len--;
	}
	
	void operator *=(int val){
		for(int i=0;i<len;i++)
			A[i]*=val;
		for(int i=0;i<len-1;i++)
			A[i+1]+=A[i]/bit,A[i]%=bit;
		while(A[len-1]>=bit)
			A[len]+=A[len-1]/bit,A[len-1]%=bit,len++;
	}
	
};
Bign f[maxn],help;
int n;bool first=true;

void print(int x){
	if(first) {printf("%d",x),first=false;return;}
	if(x<1000) printf("0");
		if(x<100) printf("0");
			if(x<10) printf("0");
				printf("%d",x);
}


int main(){
	scanf("%d",&n);
	f[1].A[0]=1;f[2].A[0]=5;
	for(int i=3;i<=n;i++){
		memcpy(help.A,f[i-1].A,sizeof(f[i-1].A));help.len=f[i-1].len;
			/*for(int i=help.len-1;i>=0;i--){
		print(help.A[i]);
	}puts("");*/
		help*=3;/*for(int i=help.len-1;i>=0;i--){
		print(help.A[i]);
	}puts("");*/
		memcpy(f[i].A,help.A,sizeof(help.A));f[i].len=help.len;
		f[i]-=f[i-2];f[i]+=2;
	}
	for(int i=f[n].len-1;i>=0;i--){
		print(f[n].A[i]);
	}puts("");
	return 0;
}
