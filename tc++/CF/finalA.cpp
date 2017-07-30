#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

char s[100] = "AHIMOTUVWXY";
char t[1000100];

char in(char c)
{
    for(int i = 0; s[i]; i++)
        if(c == s[i])
            return true;

    return false;
}

bool solve()
{
    int len = strlen(t);
    for(int i = 0, j = len - 1; i < j; i++, j--)
        if(t[i] != t[j])
            return false;

    for(int i = 0; t[i]; i++)
        if(in(t[i]) == false)
            return false;

    return true;
}

int main()
{
    while(scanf("%s", t) != EOF)
    {
        if(solve()) puts("YES");
        else puts("NO");
    }
    return 0;
}
