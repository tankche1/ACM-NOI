# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
int n,len;
char s[maxn];
int main(){
    freopen("energy.in","r",stdin);
    freopen("energy.out","w",stdout);
    scanf("%d",&n);getchar();
    gets(s);len=strlen(s);
    LL ans=0;
    int nows=0,nowlen=0,t,two=0;
    for(int i=0;i<len;i++){
        t=s[i]-'0';
        if(nowlen+t<=n){
            nowlen+=t;nows++;
            if(t==2) two++;
        }
        else if(t==1){
            if(two>0){
                two--;nowlen--;
            }
        }
        ans+=nows;
    }
    printf("%I64d\n",ans);
    return 0;
}
