#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
//   freopen("test.in","r",stdin);
    
    int n,a,g,T=0,f;
    for(scanf("%d",&g);g--;)
    {
    	printf("Case #%d: ",++T);
    	scanf("%d",&n);
    	f=1;
    	while(n--)
    	{
    		scanf("%d",&a);
    		if(a%3)f=0;
    	}
    	if(f)puts("Yes");
    	else puts("No");
    }

    return 0;
}
