# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=12;
int n,m;
char s[maxn][maxn];

struct State{
	
};

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%s",s[i]);
	printf("%d\n",rec(0,0,start));
	return 0;
}
