# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=2000010;
int n;
char s[maxn];

int MCP(int n,char *s){
	int i=0,j=1,count=0,x,y;
	while(i<n&&j<n&&count<n){
		x=i+count;y=j+count;
		if(x>=n) x-=n;if(y>=n) y-=n;
		if(s[x]==s[y]) {count++;continue;}
		else if(s[x]>s[y]){
			i=i+count+1;j=i+1;
		}
		else
			j=j+count+1;
		count=0;
	}
	return i;
}

void getExtendNext (char *t, int *next)
{
	int lt = strlen(t);
	for (int i = 1, j = -1, a, p; i < lt; i++, j--)
		if (j < 0 || i + next[i - a] >= p)
		{
			if (j < 0)	j = 0, p = i;
			while (p < lt && t[j] == t[p])	j++, p++;
			next[i] = j, a = i;
		}
		else	next[i] = next[i - a];
}

void Getextand(int *next,char *str,char *mode,int *extand){//str母串 mode子串
	int strLen=strlen(str);
	int modeLen=strlen(mode);
	int i,a,p,j=-1;
	for(i=0;i<strLen;++i,--j){
		if(j<0||i+next[i-a]>=p){
			if(j<0) j=0,p=i;
			while(p<strLen&&j<modeLen&&str[p]==mode[j]) ++p,++j;
			extand[i]=j;a=i;
		}
		else extand[i]=next[i-a];
	}
}

int lenA,lenB,len;
char A[maxn],B[maxn],C[maxn];
int extand1[maxn],exnext1[maxn],extand2[maxn],exnext2[maxn];

bool check(int pos){//以pos为起点的A能不能和完整的B匹配
	if(extand1[pos]>=lenB) return true;//pos+lenB-1
	int t=extand1[pos]+1+extand2[lenA-1-(pos+lenB-1)];
	if(t>=lenB) return true;
	return false;
}

int main()
{
	scanf("%d%d",&lenA,&lenB);len=lenA;
	scanf("%s%s",A,B);//puts(A);
	for(int i=lenA;i<lenA+lenA;i++)
		A[i]=A[i-lenA];
	lenA*=2;A[lenA]='\0';
	//prob 1
	int t=MCP(lenB,B);
	for(int i=0;i<lenB;i++){
		C[i]=B[t];
		t++;
		if(t==lenB) t=0;
	}
	for(int i=0;i<lenB;i++) B[i]=C[i];B[lenB]='\0';
	puts(B);
	//prob 2
	getExtendNext(B,exnext1);
	Getextand(exnext1,A,B,extand1);
	for(int i=0;i<lenA-1-i;i++)
		swap(A[i],A[lenA-1-i]);
	for(int i=0;i<lenB-1-i;i++)
		swap(B[i],B[lenB-1-i]);
	getExtendNext(B,exnext2);
	Getextand(exnext2,A,B,extand2);
	int ans;
	for(int i=0;i<len;i++){
		if(check(i)) ans=i;
		if(check((len-i-1))) ans=len-i-1;
	}
	//printf("pos:%d\n",ans);puts(A);
	for(int i=0;i<len;i++)
		printf("%c",A[lenA-1-ans-i]);
	puts("");
	return 0;
}
