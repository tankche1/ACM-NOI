# include <iostream>
# include <cstdio>
using namespace std;
const int maxn=250010;
int N, p, stack[maxn], top=0, ans=0;

int main()
{
    scanf("%d",&N);
    for (int i=0; i<N; i++)
    {
        scanf("%d%d",&p,&p);
        while (top>0 && stack[top]>p) top--;
        if ((!top) || stack[top]!=p)
            ans++, stack[++top]=p;
    }
    printf("%d\n",ans);
    return 0;
}
