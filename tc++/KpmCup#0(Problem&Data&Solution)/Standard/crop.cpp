#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std ;

#define MAXN 4010
#define inf 0x7fffffff
#define MAXV 20010

struct network {
       
    struct edge {
        edge *next , *pair ;
        int t , f ;
    } *head[ MAXV ] ;
       
    void Add( int s , int t , int f ) {
        edge *p = new( edge ) ;
        p -> t = t , p -> f = f , p -> next = head[ s ] ;
        head[ s ] = p ;
    }
       
    void AddEdge( int s , int t , int f ) {
        Add( s , t , f ) , Add( t , s , 0 ) ;
        head[ s ] -> pair = head[ t ] , head[ t ] -> pair = head[ s ] ;
    }
       
    int S , T ;
       
    network(  ) {
        memset( head , 0 , sizeof( head ) ) ;
    }
       
    int h[ MAXV ] , gap[ MAXV ] ;
    edge *d[ MAXV ] ;
       
    int sap( int v , int flow ) {
        if ( v == T ) return flow ;
        int rec = 0 ;
        for ( edge *p = d[ v ] ; p ; p = p -> next ) if ( p -> f && h[ v ] == h[ p -> t ] + 1 ) {
            int ret = sap( p -> t , min( flow - rec , p -> f ) ) ;
            p -> f -= ret , p -> pair -> f += ret , d[ v ] = p ;
            if ( ( rec += ret ) == flow ) return flow ;
        }
        if ( ! ( -- gap[ h[ v ] ] ) ) h[ S ] = T ;
        gap[ ++ h[ v ] ] ++ , d[ v ] = head[ v ] ;
        return rec ;
    }
       
    int maxflow(  ) {
        int flow = 0 ; 
        memset( h , 0 , sizeof( h ) ) ;
        memset( gap , 0 , sizeof( gap ) ) ;
        for ( int i = 0 ; i ++ < T ; ) d[ i ] = head[ i ] ;
        gap[ S ] = T ;
        while ( h[ S ] < T ) flow += sap( S , inf ) ;
        return flow ;
    }
       
} net ;

int n , a[ MAXN ] , b[ MAXN ] , m , sum = 0 , V ;

int main(  ) {
	scanf( "%d" , &n ) ;
	for ( int i = 0 ; i ++ < n ; ) scanf( "%d" , &a[ i ] ) , sum += a[ i ] ;
	for ( int i = 0 ; i ++ < n ; ) scanf( "%d" , &b[ i ] ) , sum += b[ i ] ;
	scanf( "%d" , &m ) ;
	net.S = n + m * 2 + 1 ; net.T = net.S + 1 ; V = n ;
	while ( m -- ) {
		int k , c1 , c2 ; scanf( "%d%d%d" , &k , &c1 , &c2 ) ; 
		++ V ; net.AddEdge( net.S , V , c1 ) ;
		++ V ; net.AddEdge( V , net.T , c2 ) ;
		sum += ( c1 + c2 ) ;
		while ( k -- ) {
			int x ; scanf( "%d" , &x ) ;
			net.AddEdge( V - 1 , x , inf ) , net.AddEdge( x , V , inf ) ;
		}
	}
	for ( int i = 0 ; i ++ < n ; ) net.AddEdge( net.S , i , a[ i ] ) , net.AddEdge( i , net.T , b[ i ] ) ;
	printf( "%d\n" , sum - net.maxflow(  ) ) ;
	return 0 ; 
}
