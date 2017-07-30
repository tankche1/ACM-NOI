#include <cmath>
#include <cstdio>

typedef double LD;
const LD eps = 1e-8, PI = acos(-1.0);
const int M = 1e3+7;
int sgn( LD x ){if( x < -eps ) return -1;if( x > eps ) return 1;return 0;}
struct point{
    LD x, y;
    point(){}
    point(LD x, LD y):x(x),y(y){}
    void in(){scanf("%lf %lf",&x ,&y);}
    void e(){LD tmp = sqrt(x*x+y*y);x/=tmp;y/=tmp;}
    void out(bool flag){printf("%.3f %.3f%c" , x , y , flag?'\n':' ');}
};
struct order{
    int p, t, alpha;
    void in(){scanf("%d %d %d" , &p, &t, &alpha );}
};
point operator + ( const point &a , const point &b ){return point( a.x + b.x, a.y + b.y );}
point operator - ( const point &a , const point &b ){return point( a.x - b.x, a.y - b.y );}
point operator * ( const point &a , const LD    &b ){return point( a.x * b  , a.y * b   );}
point operator / ( const point &a , const LD    &b ){return point( a.x / b  , a.y / b   );}
point rotate     ( const point &a , const LD    &b ){return point( a.x * cos(b) - a.y * sin(b) , a.x * sin(b) + a.y * cos(b) );}
LD dot  ( const point &a, const point &b ){return a.x * b.x + a.y * b.y;}
LD det  ( const point &a, const point &b ){return sgn( a.x * b.y - a.y * b.x );}
LD dist2( const point &a, const point &b ){return dot(a-b,a-b);}

int cas, n, m, vis[M], dt, cnt1, cnt2, tmp, ret;
LD theta, r;
point pos, d, v, stu[M], dl, dr, speed, vl, vr, polygon[5];
order ord[M];
void kill(){
    for( int i = 1 ; i <= n ; i ++ ){
        if( !vis[i] || sgn( dist2( stu[i] , pos ) - r * r ) > 0 ) continue;
        if( det( stu[i] - pos , dl ) >= 0 && det( stu[i] - pos , dr ) <= 0 ) vis[i] = 0;
    }
}
bool inpolygon( const point &a , const point &x ){
    ret = 0;
    for( int j = 0 ; j < 4 ; j ++ ){
        tmp = det( polygon[j+1] - polygon[j] , x - polygon[j] );
        if( tmp == 0 ){
            if( sgn( dot( polygon[j+1] - x , polygon[j] - x ) ) <= 0 ) return true;
            return false;
        }
        if( ret == 0 ) ret = tmp;
        if( ret != tmp ) return false;
    }
    return true;
}
void check( const point &a ){
    polygon[0] = polygon[4] = pos;
    polygon[1] = pos + a * r;
    polygon[2] = pos + a * r + speed * ( 1.0 * dt );
    polygon[3] = pos + speed * ( 1.0 * dt );
    for( int i = 1 ; i <= n ; i ++ ){
        if( !vis[i] ) continue;
        if( inpolygon( a , stu[i] ) ) vis[i] = 0;
    }
}
int main(){
//  freopen( "E.in" , "r" , stdin );
//  freopen( "E.out" , "w" , stdout );
    scanf( "%d" , &cas );
    for( int T = 1 ; T <= cas ; T ++ ){
//      scanf( "%d" , &T );
        scanf( "%d %d %lf %lf" , &n, &m, &theta, &r );
        pos.in(); d.in(); v.in(); cnt1 = cnt2 = 0;
        speed = v; speed.e();
        dl = rotate( d , + theta / 360.0 * PI ); dl.e();
        dr = rotate( d , - theta / 360.0 * PI ); dr.e();
        for( int i = 1 ; i <= n ; i ++ ){vis[i] = 1;stu[i].in();}
        for( int i = 1 ; i <= m ; i ++ ){ord[i].in();}
        kill();
        for( int i = 1 ; i <= m ; i ++ ){
            dt = ord[i].t - ord[i-1].t;
            if( dt > 0 ){
                vl = rotate( speed , PI / 2.0 ); vl.e();
                vr = rotate( speed ,-PI / 2.0 ); vr.e();
                if( det( dl , speed ) != 0 ) check( dl );
                if( det( dr , speed ) != 0 ) check( dr );
                if( det( vl , dl ) >= 0 && det( vl , dr ) <= 0 ) check( vl );
                if( det( vr , dl ) >= 0 && det( vr , dr ) <= 0 ) check( vr );
                pos = pos + speed * ( 1.0 * dt );
            }
            if( ord[i].p == 2 ){
                cnt2 = ( cnt2 + ord[i].alpha ) % 360;
                speed = rotate( v , - ( cnt2 / 180.0 * PI ) );
                speed.e();
            }else{
                cnt1 = ( cnt1 + ord[i].alpha ) % 360;
                dr = rotate( d , ( - theta / 2.0 - cnt1 ) / 180.0 * PI ); dr.e();
                if( sgn( theta + ord[i].alpha - 180 ) >= 0 ){
                    for( int i = 1 ; i <= n ; i ++ ){
                        if( !vis[i] || sgn( dist2( stu[i] , pos ) - r * r ) > 0 ) continue;
                        if( det( stu[i] - pos , dl ) >= 0 || det( stu[i] - pos , dr ) <= 0 ) vis[i] = 0;
                    }
                }else kill();
                dl = rotate( d , ( + theta / 2.0 - cnt1 ) / 180.0 * PI ); dl.e();
            }
            kill();
//          pos.out(0); speed.out(0); dl.out(0); dr.out(1);
        }
        printf( "Case #%d: " , T );
        for( int i = 1 ; i <= n ; i ++ ) printf( "%d" , vis[i] );
        putchar( '\n' );
    }
    return 0;
}
