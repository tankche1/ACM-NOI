#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int Bit=10000;
const int maxn=100;
typedef long long LL;
int K;
char s[210];
int n;
struct Bign{
	int len,A[maxn];
	Bign() {len=1;A[0]=0;}
	void operator += (Bign C){
		for(int i=0;i<C.len;i++)
			A[i]=A[i]+C.A[i];
		for(int i=0;i<len;i++)
			if(A[i]>Bit) A[i+1]+=A[i]/Bit,A[i]%=Bit;
		while(A[len]>0){
			A[len+1]+=A[len]/Bit;
			A[len]%=Bit;
			len++;
		}
		//return *this;
	}
};
Bign ans,Two[maxn];

int dfs(int L,int k){
	if(L>=n) return 0;
	//	printf("L:%d k:%d\n",L,k);
	int now=L;
	if(s[now]!='2') {
	if(s[now]=='0') {ans+=Two[k+k];}//printf("%d\n",1<<(k+k));}
	return now;
}
	now++;
	for(int i=0;i<4;i++){
		now=dfs(now,k-1)+1;
	}
	return now-1;
}

int main(){
	scanf("%d\n",&K);
	Two[0].A[0]=1;
	for(int i=1;i<=K+K;i++){
		Two[i]=Two[i-1];
		Two[i]+=Two[i];
	}
	scanf("%s",s);
	//puts(s);
	n=strlen(s);
	dfs(0,K);
	printf("%d",ans.A[ans.len-1]);
	for(int i=ans.len-2;i>=0;i--)
		printf("%04d",ans.A[i]);puts("");
	return 0;
}
