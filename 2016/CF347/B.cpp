# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
typedef long long LL;

char s[1010];

LL st[10]={1990,1991,1992,1993,1994,1995,1996,1997,1998,1989};
LL ten[15];
int main(){
    ten[0]=1;
    for(int i=1;i<=12;i++) ten[i]=ten[i-1]*10;
    int Tcase;
    scanf("%d",&Tcase);
    for(int T=1;T<=Tcase;T++){
        scanf("%s",s);
        LL n=strlen(s);
        LL pos=n-2,last=st[s[n-1]-'0'],bit=2,now=s[n-1]-'0',tmp;
        while(s[pos]>='0'&&s[pos]<='9'){
            now=now+(s[pos]-'0')*ten[bit-1];tmp=now;
            while(tmp<=last){
                tmp+=ten[bit];
            }
            last=tmp;pos--,bit++;
        }
        printf("%I64d\n",last);
    }
    return 0;
}
