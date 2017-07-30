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
    //cout << a << " " << b << endl;
    //while (1);
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
    if (a > 4 * b)
    {
        t = a / b / 2 - 1;
        ans += t * 2 - 1;
        a = a - t * 2 * b;
    }
    if (b > 4 * a)
    {
        t = b / a / 2 - 1;
        ans += t * 2;
        b = b - (t * 2 + 1) * a;
    }
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
        printf("Case #%d: ", icase);
        solve(A, B);
        cout << ans << endl;
    }
    return 0;
}
