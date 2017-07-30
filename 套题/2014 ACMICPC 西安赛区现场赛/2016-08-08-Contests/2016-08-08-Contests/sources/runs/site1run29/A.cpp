#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n = 0,a[1000];
int main() {
    int T = 0; scanf("%d",&T);
    for(int k = 1;k <= T;++ k) {
        bool flag = true;
        scanf("%d",&n);
        for(int i = 1;i <= n;++ i) {
            scanf("%d",&a[i]);
            if(a[i] % 3 != 0) flag = false;
        }
        printf("Case #%d: ",k);
        if(flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
