#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
 
using namespace std;
#define Maxl 195
#define lim 10000
#define Maxn 35 
#define rep( i, j, k ) for( i = j ; i <= k ; ++i )
 
class bignum 
{
        public :
                int n[Maxl], l ; 
        bignum () { memset( n, 0, sizeof n ), l = 0 ; }
        inline void clear() { memset( n, 0, sizeof n ) ; l = 0 ; }
        inline bignum operator * ( bignum & mul ) 
        {
                int i, j ; 
                bignum re ;
                re.clear() ;    
                re.l = l + mul.l - 1 ; 
                rep( i, 1, l ) 
                        rep( j, 1, mul.l ) 
                                re.n[i+j-1] += n[i] * mul.n[j] ; 
                rep( i, 1, re.l ) 
                        if( re.n[i] > lim ) 
                        {
                                re.n[i+1] += re.n[i] / lim ;    
                                re.n[i] %= lim ;
                        }
                for( ; re.n[re.l+1] ; ++ re.l, re.n[re.l+1] = re.n[re.l] / lim, re.n[re.l] %= lim ) ; 
                return re ; 
        }
        inline bignum operator - ( bignum & dec ) 
        {
                int i ;
                bignum re ;
                re.clear() ;
                re.l = l;
                rep( i, 1, re.l ) 
                {
                        re.n[i] = n[i] - dec.n[i] ;
                        if( re.n[i] < 0 )
                        {
                                -- n[i+1] ;
                                re.n[i] += lim ; 
                        }
                }       
                for( ; ! re.n[re.l] && re.l > 1 ; --re.l ) ; 
                return re ; 
        }       
}f[Maxn], ans, now, power ; 
int n, D ;
 
inline void Power( int p )
{
        power.clear() ; 
        power.n[++power.l] = 1 ; 
        while( p ) 
        {
                if( p & 1 ) power = power * now ;
                now = now * now ; 
                p >>= 1 ;
        }
}
 
inline void add( int i )
{
        int p = 1 ;
        ++ f[i].n[1] ;
        for( ; f[i].n[p] > lim ; f[i].n[p+1] += f[i].n[p] / lim, f[i].n[p] %= lim, ++p ) ;      
}
 
inline void count( int i )
{
        now = f[i-1] ; 
        Power( n ) ;
        f[i] = power ; 
        add( i ) ;      
}
 
int main()
{
        int i ;
        scanf("%d%d",&n,&D) ; 
        if( D < 2 ) 
                printf("1\n");
        else 
        {
                f[0].n[++f[0].l] = 1 ;
                f[1].n[++f[1].l] = 2 ; 
                rep( i, 2, D ) 
                        count( i ) ; 
                ans = f[D] - f[D-1] ; 
                printf("%d",ans.n[ans.l]) ;
                for( i = ans.l - 1 ; i ; --i )
                        printf("%04d",ans.n[i]) ; 
                printf("\n");
        }
        return 0 ;
}