/*
扩展kmp
poj3461

*/

# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;

char A[maxn],B[maxn];//A母串 B子串
int lenA,lenB;

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

int exnext[maxn],extand[maxn];
int main()
{
	int Tcase;
	scanf("%d",&Tcase);
	while(Tcase--){
		scanf("%s%s",B,A);
		lenA=strlen(A);lenB=strlen(B);
		getExtendNext(B,exnext);
		Getextand(exnext,A,B,extand);
		int ans=0;
		for(int i=0;i<lenA;i++)
			if(extand[i]==lenB)
				ans++;
		printf("%d\n",ans);
	}
	return 0;
}
