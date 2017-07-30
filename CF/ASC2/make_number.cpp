# include<stdio.h>
# include<string.h>
# include<stdlib.h>
# include<time.h>
# include<algorithm>
using namespace std;
int n=1,m=4;
int main()
{
	freopen("input.txt","w",stdout);
	srand(time(0));
	n=n+rand()%64;
	m=m+rand()%62;
	printf("%d %d\n",n,m);
	return 0;
}
