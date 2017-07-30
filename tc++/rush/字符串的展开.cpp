# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxnlen=26*8*100;
int p1,p2,p3;
char s[110];
char ans[maxnlen];
int main(){
	scanf("%d%d%d",&p1,&p2,&p3);//swap(p1,p2);
	scanf("%s",s);
	int len=strlen(s);
	int p=0;
	for(int i=0;i<len;i++){
		if(s[i]!='-'||i==len-1) {ans[p++]=s[i];continue;}
		if(s[i+1]>s[i-1]&&((s[i-1]>='a'&&s[i-1]<='z'&&s[i+1]>='a'&&s[i+1]<='z')||(s[i-1]>='0'&&s[i-1]<='9'&&s[i+1]>='0'&&s[i+1]<='9'))){
			if(p1==3){
				for(char c=s[i-1]+1;c<s[i+1];c++){
					for(int j=1;j<=p2;j++) ans[p++]='*';
				}continue;
			}
			if(s[i-1]>='0'&&s[i-1]<='9'){
				if(p3==1)
				for(char c=s[i-1]+1;c<s[i+1];c++){
					for(int j=1;j<=p2;j++) ans[p++]=c;
				}
				else{
					for(char c=s[i+1]-1;c>s[i-1];c--){
					for(int j=1;j<=p2;j++) ans[p++]=c;
				}
				}
				continue;
			}
			char mul=s[i-1]>='a'&&s[i-1]<='z'?'a':'A';char base=p1==1?'a':'A';
			if(p3==1)
				for(char c=s[i-1]+1;c<s[i+1];c++){
					for(int j=1;j<=p2;j++) ans[p++]=c-mul+base;
			}
				else{
					for(char c=s[i+1]-1;c>s[i-1];c--){
					for(int j=1;j<=p2;j++) ans[p++]=c-mul+base;
				}
			}
		}
		else ans[p++]=s[i];
	}
	ans[p]='\0';
	puts(ans);
	return 0;
}
