#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=205;
inline int lowbit(int x) {return (x&(-x));}
int Two[maxn];

int log(int x){
	//printf("x:%d\n",x);int d;scanf("%d",&d);char ab[20];
	//scanf("%s",ab);
	if(x==1) return 0;
	return log(x/2)+1;
}

int sg(int x,int y){
	if(x*y==0){int a=x+y+1;
		//printf("%d %d %d\n",x+y+1,lowbit(x+y+1),lowbit(a));
		return log(lowbit(a));
	}
	return x+y;
}
int tcase,n,m;
char t;
int main(){
	scanf("%d\n",&tcase);
	while(tcase--){
		scanf("%d %d\n",&n,&m);
		memset(Two,0,sizeof(Two));
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				while((t=getchar())&&t!='T'&&t!='H');
				if(t=='T') Two[sg(i,j)]^=1;
			}
		bool ok=false;
		for(int i=0;i<maxn;i++)
			if(Two[i]) {ok=true;break;}
		if(ok) puts("-_-");
			else puts("=_=");
	}
	return 0;
}
/*


3

2 3

HHH

HHH

2 3

HHH

TTH

2 1

T

H
*/
