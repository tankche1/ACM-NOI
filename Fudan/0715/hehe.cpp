#include<iostream>
#include<cstdlib>
#include<stdio.h>
typedef long long LL;
using namespace std;
int main()
{
    int t=1,Tcase,n;
    scanf("%d",&Tcase);
    while(Tcase--)
    {
        scanf("%d",&n);
        LL x,y;
        LL alice=0,bob=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%I64d%I64d",&x,&y);
            while(x>1&&y>1)
            {
                x>>=1;y>>=1;
                alice++;bob++;
            }
            if(x==1) bob+=y-1;
            else alice+=x-1;
        }
        printf("Case %d: ",t++);
        if(alice>bob) puts("Alice");
        else puts("Bob");
    }
}
