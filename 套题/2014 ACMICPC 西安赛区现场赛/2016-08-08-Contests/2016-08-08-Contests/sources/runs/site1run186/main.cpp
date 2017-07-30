#include <cstdio>
#include <algorithm>

int main() {
    int T;
    long long a,b,ans,aa,bb;
    scanf("%d", &T);
    for (int kiss = 1 ; kiss <= T; kiss ++ ) {
        scanf("%lld%lld", &a,&b);
        ans = 1;
        while (b != 0) {
            ans += a/b;
            aa = a, bb = b;
            a = bb;
            b = aa%bb;
        }
        printf("Case #%d: %lld\n",kiss,ans);
    }
    return 0;
}
