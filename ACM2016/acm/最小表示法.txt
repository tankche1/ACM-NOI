/*
zoj1729
2015.7.11
找出一个字符串中字典序最小的开头
*/

# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
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
		//if(i==j) j++;
		count=0;
	}
	return i;
}

int main()
{
	int Tcase;
	scanf("%d",&Tcase);
	while(Tcase--){
		scanf("%d",&n);
		scanf("%s",s);
		printf("%d\n",MCP(n,s));
	}
	return 0;
}
