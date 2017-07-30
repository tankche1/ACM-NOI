# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int MAXN=100100;
char s[MAXN],t[MAXN];
int main()
{
    int i,len;
    while(scanf("%s",s)!=EOF)
    {
        len=strlen(s);
        for(i = 0; i < len; ++i)
        {
            if(s[i]=='['||s[i]==']')
                t[i] = '\0';
            else
                t[i] = s[i];
        }
        t[len]='\0';
        for(i = len - 1; i > -1; --i)
        {
            if(s[i]=='[')
                printf("%s",t+i+1);
        }
        if(!(s[0]=='['||s[0]==']'))
            printf("%s",t);
        for(i = 1; i < len; ++i){
            if(s[i]==']')
                printf("%s",t+i+1);
        }
        printf("\n");
    }
    return 0;
}
