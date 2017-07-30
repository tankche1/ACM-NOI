#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 100010;

int a[maxn], x[maxn], y[maxn], len;
int W, H, N, M;

inline int cal( int dis )
{
    if( dis < M )
        return 0;
    return dis - M + 1;
}

struct tt
{
    //ld,rd分别是区间最左和最右的空块长度,cnt表示区间可以装多少个m
    int ll, rr, ld, rd, cnt;
} p[maxn*4];

struct seg
{
    int x, y1, y2, st;
} sx[maxn], sy[maxn];

void build( int s, int e, int num )
{
    p[num].ll = s;
    p[num].rr = e;
    p[num].ld = p[num].rd = a[e+1] - a[s];
    p[num].cnt = cal(p[num].rd);

    if( s - e )
    {
        int m = (s+e)/2;
        build(s, m, num*2+1);
        build(m+1, e, num*2+2);
    }
}

void update( int s, int e, int num, int st )
{
    if( p[num].ll == s && p[num].rr == e )
    {
        if( st )
            p[num].ld = p[num].rd = a[p[num].rr+1]-a[p[num].ll];
        else
            p[num].ld = p[num].rd  = 0;
        p[num].cnt = cal(p[num].rd);

        return;
    }

    int m = (p[num].ll + p[num].rr)/2;
    if( m >= e )
        update(s, e, num*2+1, st);
    else if( m < s )
        update(s, e, num*2+2, st);
    else
    {
        update(s, m, num*2+1, st);
        update(m+1, e, num*2+2, st);
    }

    p[num].ld = p[num*2+1].ld;
    if( p[num*2+1].ld == a[p[num*2+1].rr+1] - a[p[num*2+1].ll] )
        p[num].ld += p[num*2+2].ld;
    p[num].rd = p[num*2+2].rd;
    if( p[num*2+2].rd == a[p[num*2+2].rr+1] - a[p[num*2+2].ll] )
        p[num].rd += p[num*2+1].rd;
    p[num].cnt = p[num*2+1].cnt + p[num*2+2].cnt - cal(p[num*2+1].rd) - cal(p[num*2+2].ld) + cal(p[num*2+1].rd+p[num*2+2].ld);
}

int cmp( seg aa, seg bb )
{
    if( aa.x == bb.x )
        return aa.st > bb.st;
    return aa.x < bb.x;
}

void init( int* arr )
{
    int i;

    sort(arr, arr+2*N);
    len = 1;    a[0] = arr[0];
    for( i = 1; i < 2*N; ++i )    if( arr[i] - arr[i-1] )
        a[len++] = arr[i];
}

int bin( int x )
{
    int ll = 0, rr = len, mid;

    while( rr - ll > 1 )
    {
        mid = (ll+rr)/2;
        if( a[mid] > x )
            rr = mid;
        else
            ll = mid;
    }

    return ll;
}

int main()
{
    int i, j, k;
    int x1, x2, y1, y2;
    long long ans, tx1, ty1, tx2, ty2;

    while( scanf("%d %d %d %d", &W, &H, &N, &M) != EOF )
    {
        if( M == 1 )
        {
            //这里忘用强制转换，debug了2h- -
            ans = (long long)W*H;
            for( i = 0; i < N; ++i )
            {
                scanf("%lld %lld %lld %lld", &tx1, &ty1, &tx2, &ty2);
                ans -= (tx2-tx1+1)*(ty2-ty1+1);
            }
            printf("%lld\n", ans);
            continue;
        }

        k = 0;
        for( i = 0; i < N; ++i )
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x1--;    y1--;
            sx[k].x = x1;    sx[k].y1 = y1;    sx[k].y2 = y2;    sx[k].st = 0;
            sy[k].x = y1;    sy[k].y1 = x1;    sy[k].y2 = x2;    sy[k].st = 0;
            x[k] = x1;    y[k++] = y1;
            sx[k].x = x2;    sx[k].y1 = y1;    sx[k].y2 = y2;    sx[k].st = 1;
            sy[k].x = y2;    sy[k].y1 = x1;    sy[k].y2 = x2;    sy[k].st = 1;
            x[k] = x2;    y[k++] = y2;
        }

        ++N;
        sx[k].x = 0;    sx[k].y1 = 0;    sx[k].y2 = H;    sx[k].st = 1;
        sy[k].x = 0;    sy[k].y1 = 0;    sy[k].y2 = W;    sy[k].st = 1;
        x[k] = 0;    y[k++] = 0;
        sx[k].x = W;    sx[k].y1 = 0;    sx[k].y2 = H;    sx[k].st = 0;
        sy[k].x = H;    sy[k].y1 = 0;    sy[k].y2 = W;    sy[k].st = 0;
        x[k] = W;    y[k++] = H;

        sort(sx, sx+k, cmp);
        sort(sy, sy+k, cmp);
        ans = 0;

        init(x);
        build(0, len-2, 0);
        update(bin(sy[0].y1), bin(sy[0].y2)-1, 0, sy[0].st);
        for( i = 1; i < k; ++i )
        {
            ans += (long long)p[0].cnt*(sy[i].x-sy[i-1].x);
            update(bin(sy[i].y1), bin(sy[i].y2)-1, 0, sy[i].st);
        }


        init(y);
        build(0, len-2, 0);
        update(bin(sx[0].y1), bin(sx[0].y2)-1, 0, sx[0].st);
        for( i = 1; i < k; ++i )
        {
            ans += (long long)p[0].cnt*(sx[i].x-sx[i-1].x);
            update(bin(sx[i].y1), bin(sx[i].y2)-1, 0, sx[i].st);
        }

        printf("%lld\n", ans);
    }

    return 0;
}