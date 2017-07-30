#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int n;
char s[1000];
int num[3];
int main(){
	scanf("%d",&n);
	scanf("%s",s);
	for(int i=0;i<n;i++)
		if(s[i]=='x') num[1]++;else num[2]++;
	int op=num[1]>num[2]?1:2;
	if(op==1) num[0]=num[1]-n/2;
		else num[0]=num[2]-n/2;
	printf("%d\n",num[0]);num[1]=num[2]=0;
	for(int i=0;i<n;i++){
		if(s[i]=='x'&&op==1&&num[op]<num[0]) printf("X"),num[op]++;
		else if(s[i]=='X'&&op==2&&num[op]<num[0]) printf("x"),num[op]++;
		else printf("%c",s[i]);
	}puts("");
	return 0;
}
