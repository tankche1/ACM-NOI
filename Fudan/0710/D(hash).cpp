# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=2000010;
int lenA,lenB;
unsigned long long hashA[maxn],hashB[maxn],p[maxn];
char A[maxn],B[maxn],C[maxn];
int mod=997;
int pos;

int Lcp(unsigned long long *hash1,int len1,int x,unsigned long long *hash2,int len2,int y){
	int L=1,R=min(len1-x,len2-y),M;unsigned long long t1,t2;
	//printf("x:%d y:%d\n",x,y);
	while(L<=R){
		M=(L+R)>>1;
		t1=hash1[x+M-1];if(x) t1-=hash1[x-1];t1*=p[pos-(x+M-1)];
		t2=hash2[y+M-1];if(y) t2-=hash2[y-1];t2*=p[pos-(y+M-1)];
		//printf("M:%d t1:%I64u t2:%I64u\n",M,t1,t2);
		if(t1==t2) L=M+1;
		else R=M-1;
	}
	return L-1;
}

int main()
{
	p[0]=1;
	scanf("%d %d",&lenA,&lenB);pos=2*lenA+5;
	scanf("%s%s",A,B);
	for(int i=1;i<lenA*2+8;i++)
		p[i]=p[i-1]*mod;
	//prob1
	for(int i=lenB;i<lenB+lenB;i++)
		B[i]=B[i-lenB];
	B[lenB*2]='\0';
	hashB[0]=B[0];
	for(int i=1;i<lenB+lenB;i++)
		hashB[i]=hashB[i-1]+B[i]*p[i];
	int x=0,L;
	for(int i=1;i<lenB;i++){
		L=Lcp(hashB,lenB+lenB,x,hashB,lenB+lenB,i);
		//printf("x:%d i:%d L:%d\n",x,i,L);
		if(L>=lenB) continue;
		else if(B[i+L]<B[x+L]) x=i;
	}
	
	for(int i=x;i<x+lenB;i++)
		C[i-x]=B[i];
	for(int i=0;i<lenB;i++) B[i]=C[i];B[lenB]='\0';
	puts(B);
	
	//prob2
	hashB[0]=B[0];
	for(int i=1;i<lenB;i++)
		hashB[i]=hashB[i-1]+B[i]*p[i];
	for(int i=lenA;i<lenA+lenA;i++)
		A[i]=A[i-lenA];
	hashA[0]=A[0];
	for(int i=1;i<lenA+lenA;i++)
		hashA[i]=hashA[i-1]+A[i]*p[i];
	int L1,L2;
	int ans,st;
	for(int i=0;i<lenA-i;i++){
		st=i;
		L1=Lcp(hashA,lenA+lenA,st,hashB,lenB,0);
		if(L1>=lenB-1) {ans=st;break;}
		L2=Lcp(hashA,lenA+lenA,st+L1+1,hashB,lenB,L1+1);
		if(L1+L2+1>=lenB) {ans=st;break;}
		st=lenA-1-i;
		L1=Lcp(hashA,lenA+lenA,st,hashB,lenB,0);
		if(L1>=lenB-1) {ans=st;break;}
		L2=Lcp(hashA,lenA+lenA,st+L1+1,hashB,lenB,L1+1);
		if(L1+L2+1>=lenB) {ans=st;break;}
	}//printf("ans:%d\n",ans);
	for(int i=ans;i<ans+lenA;i++)
		printf("%c",A[i]);puts("");
	return 0;
}
