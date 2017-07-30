# include<stdio.h>
# include<string.h>
# include<stdlib.h>
# include<time.h>
# include<algorithm>
using namespace std;

int main()
{
	freopen("input.txt","w",stdout);
	int Tcase,n,m,k;
	srand(time(0));
	Tcase=1;
	printf("%d\n",Tcase);
	while(Tcase--){
		n=1000;m=100;k=2;
		printf("%d %d %d\n",n,m,k);
		for(int i=1;i<=n;i++)
			printf("%c",'a');puts("");
	}
	return 0;
}
