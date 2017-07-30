#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
char s[maxn];
int n;
int f[maxn];
//int sum[maxn];
int main(){
	s[0]='a';
	scanf("%s",s+1);
	n=strlen(s)-1;
	f[0]=0;
	int last=0;
	/*sum[0]=0;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+s[i]-'0';*/
	for(int i=1;i<=n;i++){
		if(s[i]!='0'){
			if(i!=2)
				f[i]=f[i-1]+1;
				else f[i]=s[i]>s[i-1]?1:2;
					last=i;
		}
		else{
			//printf("last:%d %d %d %d\n",last,(i-last+1),last-1,f[last-1]+1);
			if((i-last+1)!=(last-1))
			{f[i]=i-last+1>last-1?1:f[last-1]+1;continue;}
			//bool ok=true;
			if(s[1]<s[last]) f[i]=1;
			else if(s[i]>s[last]) f[i]=f[last-1]+1;
			else {
					f[i]=f[last-1]+1;
			}
		}
		//printf("f[%d]:%d\n",i,f[i]);
	}
	printf("%d\n",f[n]);
	return 0;
}

