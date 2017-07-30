/*
KMP
poj2406
2015.7.11
求最小循环节
*/
# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=5000010;
char s[maxn];
char p[maxn];
int next[maxn];
int num[maxn];
bool del[maxn];
int l[maxn],r[maxn];

void getnext(char *s,int n){
	int i=0,j=-1;
	next[0]=-1;
	while(i<n){
		if(s[i]==s[j]||j==-1){
			i++;j++;
			next[i]=j;
		}
		else j=next[j];
	}
}

void dele(int t){
    l[r[t]]=l[t];r[l[t]]=r[t];
}

int main()
{
	int n;
	while(scanf("%s",s)!=EOF){
		n=strlen(s);
		getnext(s,n);
		scanf("%s",p+1);p[0]='#';
		int m=strlen(p);
		int j=0;
		num[0]=0;memset(del,0,sizeof(del));

		l[0]=0;r[m]=n;
		for(int i=1;i<=m;i++) l[i]=i-1;
		for(int i=0;i<m;i++) r[i]=i+1;

		for(int i=0;i<m;i++){
            while(j!=-1&&p[i]!=s[j]) {
                j=next[j];
            }
            num[i]=++j;
            if(num[i]==n){
                int pos=i;
                for(int k=n;k>=1;k--) {del[pos]=1;dele(pos);pos=l[pos];}
                j=num[pos];
            }
		}
		for(int i=1;i<m;i++){
            if(!del[i]) printf("%c",p[i]);//puts("");
		}puts("");
	}
	return 0;
}
/*
abc
aaabcbc
b
bbb
abc
ab
*/
