# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
char s[110];
int n,big;
int a[110];
int main(){
	int tcase,num,pos;
	scanf("%d\n",&tcase);
	while(tcase--){
		scanf("%d ",&num);
		scanf("%s",s);
		n=strlen(s);
		for(int i=0;i<n;i++){a[i]=s[i]-'0';
		}
		printf("%d ",num);
		if(!next_permutation(a,a+n)) printf("BIGGEST");
		else for(int i=0;i<n;i++){printf("%d",a[i]);
		}
		puts("");
	}
	return 0;
}
