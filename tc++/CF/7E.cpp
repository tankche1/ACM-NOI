#include<stdio.h>
#include<string.h>
# include<string>
# include<map>
#include<algorithm>
using namespace std;
const int maxn=1010;
map<string,int> dp;
string S,T;
int n;
char s[maxn];
int hash[maxn];

int Dp(int L,int R){
	while(s[L]==' ') L++;while(s[R]==' ') R--;
	int num=0;
	//printf("L:%d R:%d\n",L,R);//int dd;scanf("%d",&dd);
	for(int i=R;i>=L;i--){
		num+=hash[s[i]];
		if(num==0&&(s[i]=='+'||s[i]=='-')){
			int t1=Dp(L,i-1),t2=Dp(i+1,R);
			if(t1==2||t2==2) return 2;
			if(t2==3&&s[i]=='-') return 2;
			return 3;
		}
	}
	
	for(int i=R;i>=L;i--){
		num+=hash[s[i]];
		if(num==0&&(s[i]=='*'||s[i]=='/')){
			//puts("a");printf("s[%d]:%c\n",i,s[i]);
			int t1=Dp(L,i-1),t2=Dp(i+1,R);
			//printf("t1:%d t2:%d\n",t1,t2);
			if(t1==2||t2==2) return 2;
			if(t1==3||t2==3) return 2;
			if(t2==4&&s[i]=='/') return 2;
			return 4;
		}
	}
	if(s[L]=='(') return Dp(L+1,R-1)==2?2:1;
	//puts("fuck");
	T="";for(int i=L;i<=R;i++) if(s[i]!=' ') T+=s[i];
	return dp.count(T)?dp[T]:1;
}

int main(){
	memset(hash,0,sizeof(hash));hash[')']=-1;hash['(']=1;
	scanf("%d",&n);gets(s);
	for(int i=1;i<=n;i++){
		scanf("%s ",s);
		if(s[0]=='#'&&s[1]!='d') scanf("%s");
		scanf("%s ",s);
		S=s;
		gets(s);
		//puts(s);
		int len=strlen(s);
		dp[S]=Dp(0,len-1);
		//printf("%d\n",dp[S]);
	}
	gets(s);
	//puts(s);
	int ans=Dp(0,strlen(s)-1);
	if(ans==2) puts("Suspicious");
	else puts("OK");
	return 0;
}
