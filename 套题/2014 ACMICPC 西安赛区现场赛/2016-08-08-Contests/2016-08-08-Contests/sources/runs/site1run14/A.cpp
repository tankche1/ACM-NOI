#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int maxn = 10086;
int num_case, n, num[maxn];
bool flag;

int main()
{
    scanf("%d", &num_case);
    for (int icase = 1; icase <= num_case; icase++)
    {
        flag = 1;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &num[i]);
            flag &= (num[i] % 3 == 0);
        }
        printf("Case #%d: ", icase);
        if (flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
