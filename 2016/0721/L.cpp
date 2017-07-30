# include<stdio.h>
# include<string.h>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=5010;
int n,m;
char s[maxn],p[maxm];

bitset<maxm> now[3],last[3];
bitset<maxm> pos[26];
char ans[maxn];

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        scanf("%s%s",s+1,p+1);

        for(int i=0;i<26;i++) pos[i].reset(),pos[i][0]=1;
        for(int i=1;i<=m;i++){
            pos[p[i]-'a'][i]=1;
        }

        last[0].reset();last[1].reset();last[2].reset();
        last[1][0]=1;

        for(int i=1;i<=n;i++){
            ans[i]='0';
            now[0]=last[2]<<1;
            now[1]=(last[1]|last[0])<<1;
            now[2]=now[1];
            now[1][0]=1;

            now[0]&=pos[s[i-1]-'a'];
            now[1]&=pos[s[i]-'a'];
            now[2]&=pos[s[i+1]-'a'];

            last[0]=now[0];last[1]=now[1];last[2]=now[2];

            if(now[0][m]|now[1][m]) ans[i-m+1]='1';
            //else ans[i-m+1]=
        }
        ans[n+1]='\0';
        //for(int i=1;i<=n;i++) printf("%d",ans[i]);puts("");
        printf("%s\n",ans+1);
    }
    return 0;
}
