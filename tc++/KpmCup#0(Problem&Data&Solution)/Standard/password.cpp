#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std ;

#define check( ch ) ( ch >= 'a' && ch <= 'z' )
#define MAXV 300010

struct saver {
	saver *next ;
	int t ;
};

struct node {
	int child[ 26 ] , fail ;
	saver *t ;
	node (  ) {
		t = NULL ; fail = 0 ;
		memset( child , 0 , sizeof( child ) ) ;
	}
} trie[ MAXV ] ;

int V = 0 , n , num[ MAXV ] ;
char s[ MAXV ] ;

int getstr(  ) {
	int ch , len = 0 ; for ( ch = getchar(  ) ; ! check( ch ) ; ch = getchar(  ) ) ;
	s[ len ++ ] = ch ;
	for ( ch = getchar(  ) ; check( ch ) ; ch = getchar(  ) ) s[ len ++ ] = ch ;
	return len ;
}

void Init(  ) {
	scanf( "%d" , &n ) ;
	for ( int i = 0 ; i ++ < n ; ) {
		int len = getstr(  ) , t = 0 ;
		for ( int j = 0 ; j < len ; j ++ ) {
			if ( ! trie[ t ].child[ s[ j ] - 'a' ] ) trie[ t ].child[ s[ j ] - 'a' ] = ++ V ;
			t = trie[ t ].child[ s[ j ] - 'a' ] ;
		}
		num[ i ] = t ;
		saver *p = new( saver ) ;
		p -> t = i , p -> next = trie[ t ].t ;
		trie[ t ].t = p ;
	}
}

queue < int > Q ;

void Build_fail(  ) {
	while ( ! Q.empty(  ) ) Q.pop(  ) ;
	for ( int i = 0 ; i < 26 ; i ++ ) if ( trie[ 0 ].child[ i ] ) {
		int x = trie[ 0 ].child[ i ] ; trie[ x ].fail = 0 ;
		Q.push( x ) ;
	}
	while ( ! Q.empty(  ) ) {
		int x = Q.front(  ) ; Q.pop(  ) ;
		for ( int i = 0 ; i < 26 ; i ++ ) if ( trie[ x ].child[ i ] ) {
			int t = trie[ x ].fail , y = trie[ x ].child[ i ] ;
			for ( ; t && ! trie[ t ].child[ i ] ; t = trie[ t ].fail ) ;
			trie[ y ].fail = trie[ t ].child[ i ] ? trie[ t ].child[ i ] : t ;
			Q.push( y ) ;
		}
	}
}

struct edge {
	edge *next ;
	int t ;
} *head[ MAXV ] ;

void AddEdge( int s , int t ) {
	edge *p = new( edge ) ;
	p -> t = t , p -> next = head[ s ] ;
	head[ s ] = p ;
}

void fail_tree(  ) {
	memset( head , 0 , sizeof( head ) ) ;
	for ( int i = 0 ; i ++ < V ; ) AddEdge( trie[ i ].fail , i ) ;
}

int dfn[ MAXV * 2 ] , cnt = 0 , in[ MAXV ] , out[ MAXV ] ;

void dfs( int v ) {
	dfn[ in[ v ] = ++ cnt ] = v ;
	for ( edge *p = head[ v ] ; p ; p = p -> next ) dfs( p -> t ) ;
	dfn[ out[ v ] = ++ cnt ] = v ;
}

struct sgt_node {
	sgt_node *left , *right ;
	int cnt ;
	sgt_node(  ) {
		left = right = NULL ;
		cnt = 0 ;
	}
} *sgt[ MAXV ] , *blank = new( sgt_node ) ;

void Add( int l , int r , int x , sgt_node *u , sgt_node* &t ) {
	if ( t == blank ) {
		t = new( sgt_node ) ;
		t -> left = t -> right = blank ;
	}
	t -> cnt = u -> cnt + 1 ;
	if ( l == r ) return ;
	int mid = ( l + r ) >> 1 ;
	if ( x <= mid ) {
		t -> right = u -> right ;
		Add( l , mid , x , u -> left , t -> left ) ;
	} else {
		t -> left = u -> left ;
		Add( mid + 1 , r , x , u -> right , t -> right ) ;
	}
}

void build_sgt(  ) {
	blank -> left = blank -> right = blank , blank -> cnt = 0 ;
	sgt[ 0 ] = blank ;
	for ( int i = 0 ; i ++ < cnt ; ) {
		sgt[ i ] = sgt[ i - 1 ] ;
		if ( i == in[ dfn[ i ] ] ) {
			for ( saver *p = trie[ dfn[ i ] ].t ; p ; p = p -> next ) {
				sgt_node *u = blank ;
				Add( 1 , n , p -> t , sgt[ i ] , u ) ;
				sgt[ i ] = u ;
			}
		}
	}
}

void Solve(  ) {
	for ( int i = 0 ; i ++ < n ; ) {
		int k ; scanf( "%d" , &k ) ;
		int d = num[ i ] ;
		if ( sgt[ out[ d ] ] -> cnt - sgt[ in[ d ] - 1 ] -> cnt < k ) {
			printf( "-1\n" ) ; 
		} else {
			int l = 1 , r = n ;
			sgt_node *t0 = sgt[ out[ d ] ] , *t1 = sgt[ in[ d ] - 1 ] ;
			while ( l < r ) {
				int sum = t0 -> left -> cnt - t1 -> left -> cnt ;
				int mid = ( l + r ) >> 1 ;
				if ( k <= sum ) {
					r = mid ;
					t0 = t0 -> left , t1 = t1 -> left ;
				} else {
					k -= sum , l = mid + 1 ;
					t0 = t0 -> right , t1 = t1 -> right ;
				}
			}
			printf( "%d\n" , l ) ;
		}
	}
}

int main(  ) {
	Init(  ) ;
	Build_fail(  ) ;
	fail_tree(  ) ;
	dfs( 0 ) ;
	build_sgt(  ) ;
	Solve(  ) ;
	return 0 ;
}
