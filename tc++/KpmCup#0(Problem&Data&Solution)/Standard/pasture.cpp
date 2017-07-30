#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std ;

#define MAXN 1000010
#define X( x ) sum1[ x ]
#define Y( x ) ( f[ x ] + sum2[ x ] )
#define G( i , j ) ( f[ j ] + i * ( sum1[ i ] - sum1[ j ] ) - ( sum2[ i ] - sum2[ j ] ) )
#define K( i , j ) ( double( Y( i ) - Y( j ) ) / double( X( i ) - X( j ) ) )
#define ll long long 

ll f[ MAXN ] , a[ MAXN ] , b[ MAXN ] , n , sum1[ MAXN ] , sum2[ MAXN ] , Q[ MAXN ] , head , tail ;

int main(  ) {
	scanf( "%lld" , &n ) ; for ( int i = 0 ; i ++ < n ; ) scanf( "%lld" , &a[ i ] ) ;
	for ( ll i = 0 ; i ++ < n ; ) scanf( "%lld" , &b[ i ] ) ;
	sum1[ 0 ] = sum2[ 0 ] = 0 ;
	for ( ll i = 0 ; i ++ < n ; ) sum1[ i ] = sum1[ i - 1 ] + b[ i ] , sum2[ i ] = sum2[ i - 1 ] + i * b[ i ] ;
	f[ 0 ] = 0 , Q[ head = tail = 1 ] = 0 ;
	for ( ll i = 0 ; i ++ < n ; ) {
		for ( ; head < tail && G( i , Q[ head ] ) >= G( i , Q[ head + 1 ] ) ; ) ++ head ;
		f[ i ] = G( i , Q[ head ] ) + a[ i ] ;
		for ( ; head < tail && K( i , Q[ tail ] ) <= K( Q[ tail ] , Q[ tail - 1 ] ) ; ) -- tail ;
		Q[ ++ tail ] = i ;
	}
	printf( "%lld\n" , f[ n ] ) ;
	return 0 ;
}
