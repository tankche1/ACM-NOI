#include <bits/stdc++.h>
using namespace std;

const int MAXL=100005;

char s[MAXL];

void solve()
{
    int n;
    scanf("%d%s",&n,s);
    int sum=0;
    for (int i=0;i<n;i++)
        if (s[i]=='(')
            sum++;
        else sum--;
    if (sum)
    {
        puts("No");
        return;
    }
    if (n==2&&s[0]=='(')
    {
        puts("No");
        return;
    }
    sum=0;
    int p=-1;
    for (int i=0;i<n;i++)
    {
        if (s[i]=='(') sum++;
        else sum--;
        if (sum<0)
        {
            p=i;
            break;
        }
    }
    if (p!=-1)
        for (int i=n-1;i>=0;i--)
            if (s[i]=='(')
            {
                swap(s[i],s[p]);
                break;
            }
    sum=0;
    for (int i=0;i<n;i++)
    {
        if (s[i]=='(') sum++;
        else sum--;
        if (sum<0)
        {
            puts("No");
            return;
        }
    }
    puts("Yes");
}

int main()
{
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
