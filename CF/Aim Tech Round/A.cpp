# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=510;
int du[maxn];
int n,m;
int g[maxn][maxn];
char s[maxn];
int main(){
    int a,b;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);du[a]++;du[b]++;
        g[a][b]=g[b][a]=1;
    }
    for(int i=1;i<=n;i++){
        if(du[i]==n-1) s[i]='b';
        else s[i]='c';
    }
    for(int i=1;i<=n;i++)
        if(s[i]!='b'){
            s[i]='a';
            for(int j=1;j<=n;j++) if(g[i][j]&&i!=j&&s[j]!='b') s[j]='a';
            break;
        }
    bool ok=true;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(g[i][j]&&((s[i]=='a'&&s[j]=='c')||((s[i]=='c')&&(s[j]=='a')))){
                ok=false;
            }
            if(!g[i][j]){
                if(s[i]==s[j]||s[i]=='b'||s[j]=='b') ok=false;
            }
        }
    }
    if(!ok) {puts("No");return 0;}
    puts("Yes");
    for(int i=1;i<=n;i++) printf("%c",s[i]);puts("");
    return 0;
}
