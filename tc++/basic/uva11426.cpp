# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=4000000;

int phi[maxn+10];

void Getphi(){
	memset(phi,0,sizeof(phi));
	phi[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!phi[i]){ //素数
		for(int j=i;j<=maxn;j+=i){
			if(!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);//小心溢出
		}
	}
	}
}

long long f[maxn+10],S[maxn+10];

int main(){
	//freopen("in.txt","r",stdin);
	Getphi();
	memset(f,0,sizeof(f));
	for(int i=1;i<=maxn;i++){
		for(int j=i*2;j<=maxn;j+=i)
			f[j]+=i*phi[j/i];
	}
	S[0]=0;
	for(int i=1;i<=maxn;i++)
		S[i]=S[i-1]+f[i];
	
	int n;
	while((scanf("%d",&n)!=EOF)&&n){
		printf("%lld\n",S[n]);
	}
	return 0;
}
