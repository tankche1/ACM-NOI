#include <fstream>
# include<iostream>
# include<algorithm>
using namespace std;
int main()  
{  
    typedef long long int64;  
    const int64 MOD = 20100403;  
    int64 n, m, ans;  
    cin >> n >> m;  
    int64 numer = n - m + 1;  
    for (int64 i = n + 2; i < n + m + 1; ++i)  
        (numer *= i) %= MOD;  
    int64 denom = 1;  
    for (int64 i = 2; i < m + 1; ++i)  
        (denom *= i) %= MOD;  
    for (ans = 0; ans < MOD; ++ans)  
        if ((denom * ans) % MOD == numer)  
            break;  
    cout << ans << std::endl;   
    return 0;  
}  