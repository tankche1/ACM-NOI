# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxm=110;
const int maxn=10010;
char A[maxn],B[maxn],C[maxn],A2[maxn];
bool appear[400];
int n,m;
int len;
int f1[maxn],f2[maxn],f[maxn];

void make_f(char *s,int len){
	f[0]=0;f[1]=0;
	for(int i=2;i<=len;i++){
		int j=f[i-1];
		while(j&&s[j+1]!=s[i]) j=f[j];
		f[i]=s[i]==s[j+1]?j+1:0;// printf("f[%d]:%d\n",i,f[i]);
	}
	//for(int i=1;i<=len;i++) printf("f[%d]:%d\n",i,f[i]);
}

void cal_f(char *A,char *B,int len,int *f1){
	int j=1;
	for(int i=1;i<=n;i++,j++){
		j--;
		while(j&&B[j+1]!=A[i]) j=f[j];
		f1[i]=A[i]==B[j+1]?j+1:0;
		if(A[i]==B[j+1]) j++;
	}
	for(int i=2;i<=n;i++)
		f1[i]=max(f1[i-1],f1[i]);
}

int main(){
	//freopen("input1.txt","r",stdin);
	int ans=0;A[0]='a';
	scanf("%s",A+1);n=strlen(A)-1;
	for(int i=1;i<=n;i++) A2[i]=A[n-i+1];
	for(int i=1;i<=n;i++) appear[A[i]]=1;
	scanf("%d",&m);
	for(int jj=1;jj<=m;jj++){
	//	printf("ans:%d\n",ans);
		B[0]='a';
		scanf("%s",B+1);len=strlen(B)-1;
		if(len==1){
			//ans+=appear[B[1]];
			continue;
		}
		make_f(B,len);
		cal_f(A,B,len,f1);C[0]='a';
		for(int i=1;i<=len;i++)
			C[i]=B[len-i+1];C[len+1]='\0';
		make_f(C,len);
		cal_f(A2,C,len,f2);
		if(f1[n]>=len) {//puts("fuck");
			ans++;continue;}
		for(int i=1;i<=n-1;i++){
			if(f1[i]+f2[n+1-i-1]>=len) {//printf("i:%d\n",i);
				ans++;break;}
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*
AAAAAAAAAAAA
5
AAAAAAAAAAAAA
AAAAAAAAAAAA
AAAAAAAAAA
AAB
B
*/
