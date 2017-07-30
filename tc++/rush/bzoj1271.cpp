#include <stdio.h>
#define N 200010
#define INF 2147483647
#define int long long
typedef struct Q{int s, e, d ;}Q ;
int T, n, sum, ss[N] ;
Q q[N] ;
int cal (int nu, int a, int b)
{
    if (b < q[nu].s) return 0 ;
    if (a < q[nu].s) a = q[nu].s ;
    if (b > q[nu].e) b = q[nu].e ;
    a = q[nu].s + q[nu].d * ((a - q[nu].s + q[nu].d - 1) / q[nu].d) ;
    b = q[nu].s + q[nu].d * ((b - q[nu].s) / q[nu].d) ;
    if (a > b) return 0 ;
    return (b - a) / q[nu].d + 1 ;
}
int calsum (int a, int b, int st, int ed)
{
    int i, t = 0 ;
    for (i = st; i <= ed; i ++ ) t += cal (ss[i], a, b) ;
    return t ;
}
int ydiv1 (int p, int r)
{
    int i = p - 1, j = r + 1, x = q[ss[(p + r) >> 1]].s, t ;
    while (1){
        do j -- ; while (q[ss[j]].s > x) ;
        do i ++ ; while (q[ss[i]].s < x) ;
        if (i < j) t = ss[i], ss[i] = ss[j], ss[j] = t ;
        else return j;}
}
void ysort1 (int p, int r)
{
    int k ;
    if (p < r){
        k = ydiv1 (p, r) ;
        ysort1 (p, k) ;
        ysort1 (k + 1, r) ;}
}
int search (int a, int b, int st, int ed)
{
    int i, t, mid ;
    if (a == b){
        sum = calsum (a, b, st, ed) ;
        return a ;}
    mid = (a + b) >> 1 ;
    t = ed ;
    while (t > st && q[ss[t]].s > mid) t -- ;
    if(calsum (a, mid, st, t) & 1) return search (a, mid, st, t) ;
    else return search (mid + 1, b, st, ed) ;
}
main ()
{
    int i, j, t, min, max ;
    scanf ("%I64d", &T) ;
    while (T -- ){
        scanf ("%I64d", &n) ;
        for (i = 1, t = 0, min = INF, max = -1; i <= n; i ++ ){
            ss[i] = i ;
            scanf ("%lld%lld%lld", &q[i].s, &q[i].e, &q[i].d) ;
            if (min > q[i].s) min = q[i].s ;
            if (max < q[i].e) max = q[i].e ;
            t += cal (i, q[i].s, q[i].e) ;}
        if (!(t & 1)){
            printf ("Poor QIN Teng:(\n") ;
            continue ;}
        ysort1 (1, n) ;
        t = search (min, max, 1, n) ;
        printf ("%lld %lld\n", t, sum) ;}
    return 0 ;
}
