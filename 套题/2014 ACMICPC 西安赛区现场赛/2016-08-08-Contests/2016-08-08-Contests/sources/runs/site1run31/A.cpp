#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main()
{
	int T,n,a;
	int id,i; bool flg;
	
	scanf("%d",&T);
	for(id=1;id<=T;id++)
	{
		printf("Case #%d: ",id);
		scanf("%d",&n); flg = true;
		for(i=1;i<=n;i++)
		{
			scanf("%d",&a);
			if(a%3!=0) flg = false;
		}
		if(flg) printf("Yes\n");
		else printf("No\n");
	}
	
	return 0;
}

