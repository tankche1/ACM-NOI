# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
int main(){
	srand(time(NULL));
	int m=300,n=300,t=rand()%1000000000+1,tp=rand()%100+1,tu=rand()%100+1,td=rand()%100+1;
	printf("%d %d %d %d %d %d\n",m,n,t,tp,tu,td);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)
			printf("%d ",rand()%10000+1);puts("");
	}
	return 0;
}

