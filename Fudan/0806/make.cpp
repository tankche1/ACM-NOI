#include <cstdio>
#include <ctime>
#include <cstring>
#include <iostream>
#include <algorithm>
int random(int l,int r){return rand()%(r-l+1)+l;}
int main(int argc,char *argv[])
{
	//freopen("e.in","w",stdout);
	srand(atoi(argv[1]));
	int test=3;
	printf("%d\n",test);
	while(test--)
	{
		int n=random(1,100);
		int m=random(0,n*(n-1)/2);
		printf("%d %d\n",n,m);
		for(int i=1;i<=m;i++)
		{
			int a=random(1,n),b=random(1,n);
			while(a==b)a=random(1,n),b=random(1,n);
			printf("%d %d\n",a,b);
		}
	}
}
