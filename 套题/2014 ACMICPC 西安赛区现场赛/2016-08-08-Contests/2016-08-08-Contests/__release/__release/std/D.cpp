#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#define pb push_back
#define Maxn 402013
#define ld long double
#define eps 0.000000001
#define it vector<int>::iterator


using namespace std;

int N, length, rlength, tlength, T;
bool found, nfound;
vector<int> V, R, E[Maxn];
queue<int> Q;
int dfs[Maxn], bfs[Maxn], pos[Maxn], depth[Maxn], father[Maxn];
ld f[Maxn];
int d[Maxn], fa[Maxn];
bool used[Maxn], key[Maxn];

//------------tree--------------------

const ld pi = acos(-1);

struct Complex
{
	long double X,Y;
	Complex()
	{
		X = Y = 0;
	}
	Complex( long double X, long double Y ):X(X),Y(Y){}
	Complex operator*( Complex p )
	{
		return Complex( X*p.X - Y*p.Y, X*p.Y + Y*p.X );
	}
	Complex operator+( Complex p )
	{
		return Complex( X + p.X, Y + p.Y );
	}
	Complex operator-( Complex p )
	{
		return Complex( X - p.X, Y - p.Y );
	}
};

struct ComplexArray
{
	Complex f[Maxn];
	int len;
	inline Complex&operator[]( int x )
	{
		return f[x];
	}
	inline void clear(){
		len = 0;
		memset(f, 0, sizeof(f));
	}
} a, b, c;

struct FFT
{
	Complex e[Maxn];
	Complex v[Maxn];
	void fft( Complex *a, int s, int t, int size )
	{
		if ( (size>>t) == 1 ) return;
		fft( a, s, t+1, size );
		fft( a, s+(1<<t), t+1, size );
		if ( t == 1 )
			int bp = 1;
		Complex w = e[0];
		for ( int i = 0; i < (size>>1); i += (1<<t) )
		{
			Complex d = w * a[s+(i<<1) + (1<<t)];
			v[s+i] = a[s+(i<<1)] + d;
			v[s+i+(size>>1)] = a[s+(i<<1)] - d;
			w = w * e[1<<t];
		}
		for ( int i = 0; i < size; i += (1<<t) )
		a[s+i] = v[s+i];
	}
	void cal( ComplexArray &a, ComplexArray &b )
	{
		int len = a.len + b.len + 1;
		int size = 1;
		while ( size < len ) size <<= 1;
		for ( int i = 0; i < size; ++i )
		e[i] = Complex( cos(2*pi*i/size), sin(2*pi*i/size) );
		fft( a.f, 0, 0, size );
		if ( &b != &a )
		fft( b.f, 0, 0, size );
		for ( int i = 0; i < size; ++i )
		a[i] = a[i] * b[i];
		for ( int i = 0; i < size; ++i )
		e[i].Y = -e[i].Y;
		fft( a.f, 0, 0, size );
		for ( int i = size - 1; i > a.len + b.len; --i )
		if ( abs(a[i].X) > eps )
		{
			a[i] = Complex( 0, 0 );
		}
		a.len = a.len + b.len;
		for ( int i = a.len; i >= 0; --i )
		{
			a[i].X /= size;
			a[i].Y = 0;
		}		
		if ( &b != &a )
		{
			for ( int i = 0; i < size; ++i )
			b[i] = Complex( 0, 0 );
			b.len = 0;
		}
	}
} Cal;
//------------fft--------------------

void POW( int N, ComplexArray &a )
{
	if ( N == 1 ) 
		return;
	else 
	{
		POW( N>>1, a );
		Cal.cal( a, a );
		
		if ( N&1 )
		{
			for ( int i = N; i; --i )
			a[i].X = a[i].X + a[i-1].X;
			a.len++;
		}
	}
}

void C( int N, ComplexArray &a )
{
	a.len = 1;
	for ( int i = 0; i < 2*N; ++i ) a[i] = Complex(0,0);
	a[0] = Complex( 1, 0 );
	a[1] = Complex( 1, 0 );
	POW( N, a );
}


void init()
{
		
	N = length = rlength = tlength = 0;
	scanf( "%d", &N );
	found = nfound = 0;
	V.erase(V.begin(), V.end()); R.erase(V.begin(),V.end());
	for(int i = 0; i <= N; ++i)
		E[i].erase(E[i].begin(), E[i].end());
	while (Q.size())
		Q.pop();
	memset(dfs,0,sizeof(dfs[0])*(N+10)); memset(bfs,0,sizeof(bfs[0])*(N+10)); 
	memset(pos,0,sizeof(pos[0])*(N+10)); memset(depth,0,sizeof(depth[0])*(N+10));
	memset(father,0,sizeof(father[0])*(N+10));
	memset(f,0,sizeof(f[0])*(N+10)); memset(d,0,sizeof(d[0])*(N+10)); memset(fa,0,sizeof(fa[0])*(N+10));
	memset(used,0,sizeof(used[0])*(N+10)); memset(key,0,sizeof(key[0])*(N+10));
	a.clear(); b.clear(); c.clear();
	for ( int i = 1; i <= N; ++i ) 
	{
		scanf( "%d", dfs + i );
	}
	for ( int i = 1; i <= N; ++i ) 
	{
		int x;
		scanf( "%d", &x );
		bfs[x] = i;
	}
	for ( int i = 1; i <= N; ++i ) 
	{
		dfs[i] = bfs[dfs[i]];
		pos[dfs[i]] = i;
	}
	
	int ED = 1, OP = 1, MINED = 1;
	V.pb( 1 );
	while ( OP <= N )
	{
		ED = N;
		for ( int x = OP; x <= ED; ++x )
		{
			if ( dfs[pos[x]+1] > x&& dfs[pos[x]+1] - 1 >= MINED )
			{
				ED = min( ED, dfs[pos[x]+1] - 1 );
				break;
			}
		}
		for ( int x = OP; x <= ED; ++x )
		{
			fa[x] = OP;
			if ( dfs[pos[x]+1] > x&& dfs[pos[x]+1] >= MINED )
			MINED = dfs[pos[x]+1];
		}
		OP = ED + 1;
	}
}

void work()
{
	f[1] = 1; f[2] = 2;
	V.pb( 1 ); V.pb( 2 );
	for ( int i = 3; i <= N; ++i )
	{
		if ( dfs[i] < V.back() )
		{
			while ( V.back() > dfs[i] )
			V.pop_back();
		}
		if ( dfs[i] == V.back() + 1 )
		{
			if ( fa[dfs[i]] == fa[V.back()] )
			{
				f[dfs[i]] = f[V.back()];
				used[dfs[i]] = used[fa[dfs[i]]];
				V.pop_back();
			}
			else
			{
				f[dfs[i]] = f[V.back()] + 0.5;
				used[dfs[i]] = 1;
				used[fa[dfs[i]]] = 1;
			}
		}
		else if ( dfs[i] > V.back() + 1 )
		{
			f[dfs[i]] = f[V.back()] + 1;
		}
		father[dfs[i]] = V.back();
		V.pb( dfs[i] );
	}
}
void check()
{
	for ( int i = 1; i <= N; ++i )
	if ( used[i] && !key[i])
	int bp = 1;	
}


void travel( int x )
{
	if ( x == N ) key[x] = 1;
		
	for ( it i = E[x].begin(); i != E[x].end(); ++i )
	{
		travel( *i );
		if ( !key[*i] )depth[x] = max( depth[x], depth[*i] + 1);
		else key[x] = 1;
	}
	
	//if ( !key[x] ) depth[x]++;
}

void solve()
{
	for ( int i = 1; i <= N; ++i )
	E[father[i]].pb( i );
	E[1].pb( 2 );
	/*for ( int i = 1; i <= N; ++i )
	{
		printf( "%d    ", i );
		for ( it j = E[i].begin(); j != E[i].end(); ++j )
		printf( "%d ", *j );
		puts( "" );
	}*/	 // print son
	travel( 1 );
	
	//for ( int i = 1; i <= N; ++i ) if ( key[i] ) printf( "%d ", i );
	//keyroad--
	
	a[0].X = 1; a.len = 0;
	int last = 0;
	length = depth[1];
	for ( int i = 2; i <= N; ++i )
	if ( key[dfs[i]] )
	{
		if ( used[dfs[i]]&& dfs[i] != 3 )
		{
			++tlength;
		}
		else 
		{
			++length;
		}
		
		if ( depth[last] > 0&& depth[last] + 1 > length )
		{
			int len = depth[last] + 1 - length;
			length = depth[last] + 1;
			if ( tlength >= 1 )
			{
				C(tlength,b);
				Cal.cal(a,b);
				tlength = 0;
			}
			if ( len < a.len )
			{
				for ( int j = 0; j < len; ++j )
				a[len].X += a[j].X;
				for ( int j = len; j <= a.len; ++j )
				a[j-len].X = a[j].X;
				for ( int j = a.len - len + 1; j <= a.len; ++j )
				a[j].X = 0;
				a.len = a.len - len;
			}
			else
			{
				for ( int i = 0; i <= a.len; ++i ) a[i] = Complex( 0, 0 );
				a.len = 0;
				a[0] = Complex( 1, 0 );
			}
		}
		
		last = dfs[i];
	}
	if ( tlength >= 1 )
	{
		C(tlength,b);
		Cal.cal(a,b);
		tlength = 0;
	}
	ld ans = length, sum = 0;;
	for ( int i = 0; i <= a.len; ++i ) sum += a[i].X;
	for ( int i = 0; i <= a.len; ++i ) ans += a[i].X/sum*i;
	printf( "%.3f\n", (double)ans );
}

int main()
{
	//freopen( "tree.in", "r", stdin ); freopen( "tree_p.out", "w", stdout );

	scanf("%d", &T);
	for (int i = 1; i <= T; ++i){
		printf("Case #%d: ", i);
		init();	
		work();
		solve();
		check();
	}

	
	//fclose( stdin ); fclose( stdout );
	return 0;
}
