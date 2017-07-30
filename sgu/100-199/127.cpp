#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int k, n, num[10], ans = 2;
    char line[5];
    memset(num, 0, sizeof(num));
    cin >> k >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> line;
        num[line[0] - '0']++;
    }
    for (int i = 1; i < 10; ++i)
    {
        if (i == 8 || num[i] == 0)
            continue;
        ans += num[i] / k;
        if (num[i] % k) ans++;
    }
    cout << ans << endl;
    return 0;
}