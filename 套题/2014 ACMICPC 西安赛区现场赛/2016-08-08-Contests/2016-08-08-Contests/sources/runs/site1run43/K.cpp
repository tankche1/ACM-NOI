#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <map>
using namespace std;

typedef long long LL;
int num_case;
LL A, B, t, ans;
map <LL, bool> visit;

void solve(LL a, LL b)
{
    if (!visit[a])
    {
        visit[a] = 1;
        ans++;
    }
    if (!visit[b])
    {
        visit[b] = 1;
        ans++;
    }
    if (a == 0 || b == 0) return;
    solve(b, max(a - b, b - a));
}

int main()
{
    scanf("%d", &num_case);
    for (int icase = 1; icase <= num_case; icase++)
    {
        visit.clear();
        cin >> A >> B;
        ans = 0;
        if (!visit[A])
        {
            visit[A] = 1;
            ans++;
        }
        if (!visit[B])
        {
            visit[B] = 1;
            ans++;
        }
        if (A == 0 || B == 0)
        if (A > 4 * B)
        {
            t = A / B / 2 - 1;
            ans += t * 2 - 1;
            A = A - t * 2 * B;
        }
        if (B > 4 * A)
        {
            t = B / A / 2 - 1;
            ans += t * 2;
            B = B - (t * 2 + 1) * A;
        }
        solve(A, B);
        printf("Case #%d: %d\n", icase, ans);
    }
    return 0;
}
