#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;
#define MAXw 605
#define MAXl 305

int W, L;
int ans[MAXl][MAXl], f[MAXl][30] ;
char s[MAXl], s1[30];
int main()
{
	int i, j, k, l, k1, k2, cnt;
	scanf("%d%d",&W,&L);
	scanf("%s",s+1);
	for( i = L ; i ; --i )
		for( j = i ; j <= L ; ++j )
			ans[i][j] = j - i + 1 ;
	for( i = 0 ; i < W ; ++i )
	{
		scanf("%s",s1+1);
		for( l = strlen(s1+1) , j = 0 ; j <= max( L, l ) ; ++j )
			f[j][0] = f[0][j] = 0 ;
		for( j = 1 ; j <= L ; ++j )
		{
			for( k = 1 ; k <= l ; ++k )
			{
				if( s[j] == s1[k] )
					f[j][k] = f[j-1][k-1] + 1 ;	
				else
					f[j][k] = max( f[j-1][k] , f[j][k-1] ) ;
			}
			if( f[j][l] == l )
			{
				for( k1 = j , k2 = cnt = l ; ; )
				{
					if( s[k1] == s1[k2] ) 	
					{
						--cnt ; 
						if( !cnt ) break;
						--k1 ; --k2 ; 
					}
					else if( f[k1][k2] == f[k1][k2-1] ) --k2 ;
					else --k1 ;	
				}
				for( ; k1 ; --k1 )
					ans[k1][j] = min( ans[k1][j] , j - k1 + 1 - l ) ; 
			}
		}
	}
	for( i = L ; i ; --i )
		for( j = i ; j <= L ; ++j )
			for( k = i ; k <= j ; ++k )
				ans[i][j] = min( ans[i][j] , ans[i][k] + ans[k+1][j] ) ;
	printf("%d\n",ans[1][L]);
	return 0;
}
