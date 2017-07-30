# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
char s[1010];
int num[27];
int n,Max,ans,d;
int main()
{
	int Tcase,tt;
	scanf("%d\n",&Tcase);
	while(Tcase--){
		Max=0;
		gets(s);//puts(s);
		memset(num,0,sizeof(num));n=strlen(s);
		for(int i=0;i<n;i++){
			num[s[i]-'A']++;
		}
		for(int i=0;i<26;i++)
			if(num[i]>Max) Max=num[i],ans=i;
		tt=0;for(int i=0;i<26;i++)
			if(num[i]==Max) tt++;
		if(tt>1){
			puts("NOT POSSIBLE");continue;
		}
		d=(ans+26-4)%26;
		printf("%d ",d);
		for(int i=0;i<n;i++){
			if(s[i]==' ') printf(" ");
			else
			printf("%c",'A'+(((s[i]-'A')-d+26)%26));
		}puts("");
	}
	return 0;
}
