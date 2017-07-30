# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int b,w;
char s[2]={'@','.'};
char a[6][10010];
int main(){
    freopen("black.in","r",stdin);
    freopen("black.out","w",stdout);
    scanf("%d%d",&b,&w);if(b<w) swap(s[0],s[1]),swap(b,w);
    int n=0;
    if(b==w){
        printf("%d %d\n",1,2*b);
        for(int i=1;i<=2*b;i++)
            if(i&1) printf("%c",s[0]);else printf("%c",s[1]);puts("");
        return 0;
    }
    for(int i=1;i<=10000;i++){
        a[1][i]=a[2][i]=a[3][i]=a[4][i]=a[5][i]=s[1];
    }
    n=4*(w-1);
    for(int i=1;i<=(w-1);i++){
        a[4][4*(i-1)+1]=a[4][4*(i-1)+2]=a[4][4*(i-1)+3]=s[0];
        a[5][4*(i-1)+1]=a[5][4*(i-1)+3]=s[0];
        a[5][4*(i-1)+2]=s[1];
        a[5][4*(i-1)+4]=a[4][4*(i-1)+4]=s[1];
    }
    n=max(n,2*(b-(w-1)));
    for(int i=1;i<=b-(w-1);i++){
        a[2][2*i-1]=s[0];a[2][2*i]=s[1];
    }
    printf("%d %d\n",4,n);
    for(int i=2;i<=5;i++){
        for(int j=1;j<=n;j++){
            printf("%c",a[i][j]);
        }puts("");
    }
    return 0;
}
