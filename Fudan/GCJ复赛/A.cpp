# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
int tcase;
char s[maxn<<1];
char ans[maxn<<1];
int front,tail;
int n,now;
int main(){
    freopen("A-large.in","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&tcase);
    for(int Tcase=1;Tcase<=tcase;Tcase++){
        scanf("%s",s);
        n=strlen(s);
        printf("Case #%d: ",Tcase);
        now=0;front=maxn;tail=maxn-1;
        for(int i=0;i<n;i++){
            if(s[i]-'A'>=now) ans[--front]=s[i],now=s[i]-'A';
            else ans[++tail]=s[i];
        }
        for(int i=front;i<=tail;i++) printf("%c",ans[i]);puts("");
    }
    return 0;
}
