# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int n;
int num[28];
char s[10010];
int main(){
    freopen("arrange.in","r",stdin);
    freopen("arrange.out","w",stdout);
    memset(num,0,sizeof(num));
    scanf("%d",&n);getchar();
    for(int i=1;i<=n;i++){
        gets(s);
        if(s[0]>='A'&&s[0]<='Z') num[s[0]-'A'+1]++;
    }
    int ans=0;
    for(int i=1;i<=26;i++){
        if(num[i]>0) ans++;
    else break;
    }
    printf("%d\n",ans);
    return 0;
}
