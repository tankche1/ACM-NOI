# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int n=26,tot=0;
int main(){
    freopen("in.txt","w",stdout);
    printf("2\n628\naa\naz\n");
    for(int i=2;i<=n;i++)
        for(int j=1;j<=n;j++){
            if(i<n&&j==n) continue;
            printf("%c%c\n",'a'+i-1,'a'+j-1),tot++;
        }tot+=2;
    printf("2\naa\nbb\n");
    return 0;
}
