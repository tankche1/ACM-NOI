#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std ;

#define MAXN 100010

struct edge {
	int t , d ;
	edge *next ;
} *head[ MAXN ] ;

void AddEdge( int s , int t , int d ) {
	edge *p = new( edge ) ;
	p -> t = t , p -> d = d , p -> next = head[ s ] ; 
	head[ s ] = p ;
}

int n , m ; 

int dist[ MAXN ] , cnt[ MAXN ] ;
bool f[ MAXN ] ;
stack < int > S ;

bool spfa(  ) {
	for ( int i = 0 ; i ++ < n ; ) {
		S.push( i ) , cnt[ i ] = 1 , f[ i ] = true , dist[ i ] = 0 ;
	}
	while ( ! S.empty(  ) ) {
		int v = S.top(  ) ; S.pop(  ) , f[ v ] = false ;
		for ( edge *p = head[ v ] ; p ; p = p -> next ) if ( dist[ p -> t ] > dist[ v ] + p -> d ) {
			dist[ p -> t ] = dist[ v ] + p -> d ;
			if ( ( ++ cnt[ p -> t ] ) > n ) return false ;
			if ( ! f[ p -> t ] ) S.push( p -> t ) ;
		}
	}
	return true ;
}

int main(  ) {
	scanf( "%d%d" , &n , &m ) ;
	memset( head , 0 , sizeof( head ) ) ;
	while ( m -- ) {
		int x , a , b , c ; scanf( "%d" , &x ) ;
		if ( x == 1 ) {
			scanf( "%d%d%d" , &a , &b , &c ) ; 
			AddEdge( a , b , - c ) ;
		} else if ( x == 2 ) {
			scanf( "%d%d%d" , &a , &b , &c ) ;
			AddEdge( b , a , c ) ;
		} else {
			scanf( "%d%d" , &a , &b ) ;
			AddEdge( a , b , 0 ) , AddEdge( b , a , 0 ) ;
		}
	}
	printf( spfa(  ) ? "Yes\n" : "No\n" ) ;
	return 0 ; 
}
