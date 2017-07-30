# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100000;
int main(){
	srand(time(NULL));
	//s[2]=
	int T=5;
	puts("5");
	while(T--){
	int n=1000;
	printf("%d\n",n);;
	for(int i=1;i<=n;i++) printf("%d %d\n",i,rand()%360);
	}
	return 0;
}

